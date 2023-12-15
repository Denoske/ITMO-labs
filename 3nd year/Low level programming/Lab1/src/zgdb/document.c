#include <malloc.h>
#include <time.h>
#include <string.h>

#include "format.h"
#include "document.h"
#include "schema.h"
#include "element.h"
#include "query.h"

document* createDocument() {
    documentSchema* schema = malloc(sizeof(documentSchema));
    if (schema) {
        *schema = (documentSchema) { 0 };
        document* doc = malloc(sizeof(document));
        if (doc) {
            doc->schema = schema;
            return doc;
        }
        free(schema);
    }
    return NULL;
}

void destroyDocument(document* doc) {
    if (doc) {
        if (doc->schema) {
            destroySchema(doc->schema);
        }
        free(doc);
    }
}

opt_uint64_t writeDocument(zgdbFile* file, documentSchema* schema, uint64_t brotherIndexNumber) {
    if (!schema) {
        return not_present_uint64_t();
    }
    int64_t pos = ftello64(file->f); // сохраняем текущую позицию, чтобы вернуться в неё после записи
    documentHeader header;
    header.size = calcDocumentSize(schema);
    header.brotherIndexNumber = brotherIndexNumber;
    header.lastChildIndexNumber = DOCUMENT_NOT_EXIST;
    memset(header.schemaName, 0, 13);
    strcpy(header.schemaName, schema->name);

    // Сразу выделяем индексы, если список пустой:
    if (!file->list.front && !moveFirstDocuments(file)) {
        return not_present_uint64_t();
    }
    // Если есть подходящая дырка, то пишем документ туда:
    uint64_t newSize = 0;
    int64_t diff = (int64_t) file->list.front->size - (int64_t) header.size;
    if (diff >= 0) {
        // Считываем индекс дырки и обновляем его (делаем INDEX_ALIVE):
        zgdbIndex index = getIndex(file, file->list.front->indexNumber);
        if (index.flag != INDEX_DEAD ||
            !updateIndex(file, file->list.front->indexNumber, wrap_uint8_t(INDEX_ALIVE), not_present_int64_t())) {
            return not_present_uint64_t();
        }
        // Заполняем заголовок документа:
        header.indexNumber = file->list.front->indexNumber;
        header.id.offset = index.offset;
        // Если дырка больше, чем надо, записываем TYPE_NOT_EXIST в том месте, где будет заканчиваться документ:
        if (diff) {
            uint8_t startOfUnusedSpaceMark = TYPE_NOT_EXIST;
            fseeko64(file->f, index.offset + (int64_t) header.size, SEEK_SET);
            if (!fwrite(&startOfUnusedSpaceMark, sizeof(uint8_t), 1, file->f)) {
                return not_present_uint64_t();
            }
            newSize = file->list.front->size;
        }
        free(popFront(&file->list));
    } else {
        // В любом случае будем писать в конец файла, но, возможно, надо выделить новые индексы. Затем обновляем индекс дырки:
        if (file->list.back->size != 0 && !moveFirstDocuments(file) ||
            !updateIndex(file, file->list.back->indexNumber, wrap_uint8_t(INDEX_ALIVE),
                         wrap_int64_t(file->header.fileSize))) {
            return not_present_uint64_t();
        }
        // Заполняем заголовок документа:
        header.indexNumber = file->list.back->indexNumber;
        header.id.offset = file->header.fileSize;
        free(popBack(&file->list));
        // Обновляем размер файла
        file->header.fileSize += (int64_t) header.size;
        if (!writeHeader(file)) {
            return not_present_uint64_t();
        }
    }

    // Пропускаем заголовок и записываем сначала основную часть документа:
    uint64_t bytesLeft = header.size;
    fseeko64(file->f, header.id.offset + (int64_t) sizeof(documentHeader), SEEK_SET);
    for (uint64_t i = 0; i < schema->length; i++) {
        bytesLeft -= writeElement(file, schema->elements[i]);
    }
    // Обновляем размер документа (если надо) и записываем время создания документа в заголовок:
    if (newSize) {
        header.size = newSize;
    }
    header.id.timestamp = (uint32_t) time(NULL);
    // Перемещаемся к началу и записываем заголовок:
    fseeko64(file->f, header.id.offset, SEEK_SET);
    bytesLeft -= fwrite(&header, sizeof(documentHeader), 1, file->f) * sizeof(documentHeader);
    if (bytesLeft) {
        return not_present_uint64_t();
    }
    // Если созданный документ - корень, добавляем запись о его индексе в заголовок файла:
    if (file->header.indexOfRoot == DOCUMENT_NOT_EXIST) {
        file->header.indexOfRoot = header.indexNumber;
        if (!writeHeader(file)) {
            return not_present_uint64_t();
        }
    }
    fseeko64(file->f, pos, SEEK_SET);
    return wrap_uint64_t(header.indexNumber);
}

document* readDocument(zgdbFile* file, uint64_t indexNumber) {
    zgdbIndex index = getIndex(file, indexNumber);
    if (index.flag == INDEX_ALIVE) {
        fseeko64(file->f, index.offset, SEEK_SET); // спуск в документ по смещению
        documentHeader header;
        if (fread(&header, sizeof(documentHeader), 1, file->f)) {
            document* doc = createDocument();
            if (doc) {
                doc->header = header;
                strcpy(doc->schema->name, doc->header.schemaName);
                uint64_t bytesRead = sizeof(documentHeader);
                while (bytesRead < header.size) {
                    element* el = malloc(sizeof(element));
                    if (!el) {
                        destroyDocument(doc);
                        return NULL;
                    }
                    uint64_t tmp = readElement(file, el, false);
                    if (!tmp) {
                        free(el);
                        destroyDocument(doc);
                        return NULL;
                    }
                    // Если элемент не существует, то выходим из цикла. Иначе - пробуем добавить элемент в схему:
                    if (el->type == TYPE_NOT_EXIST) {
                        bytesRead = header.size;
                    } else {
                        bytesRead += tmp;
                        if (!addElementToSchema(doc->schema, el)) {
                            free(el);
                            destroyDocument(doc);
                            return NULL;
                        }
                    }
                }
                return doc;
            }
        }
    }
    return NULL;
}

void printDocument(document* doc) {
    if (doc) {
        printf("%s#%08X%016X {\n", doc->header.schemaName, doc->header.id.timestamp, doc->header.id.offset);
        for (uint64_t i = 0; i < doc->schema->length; i++) {
            printf("\t");
            printElement(doc->schema->elements[i]);
        }
        printf("}\n");
    } else {
        printf("Document doesn't exist!\n");
    }
}

void printTree(zgdbFile* file, documentHeader header, uint64_t nestingLevel) {
    printf("%*s%s#%08X%016X", nestingLevel, "", header.schemaName, header.id.timestamp, header.id.offset);
    if (header.lastChildIndexNumber != DOCUMENT_NOT_EXIST) {
        printf(" {\n");
        uint64_t childIndexNumber = header.lastChildIndexNumber;
        do {
            zgdbIndex childIndex = getIndex(file, childIndexNumber);
            if (childIndex.flag == INDEX_ALIVE) {
                fseeko64(file->f, childIndex.offset, SEEK_SET);
                documentHeader childHeader;
                if (fread(&childHeader, sizeof(documentHeader), 1, file->f)) {
                    printTree(file, childHeader, nestingLevel + 4);
                    childIndexNumber = childHeader.brotherIndexNumber;
                    continue;
                }
            }
            printf("%*sAn error occurred!\n", nestingLevel, "");
            break;
        } while (childIndexNumber != DOCUMENT_NOT_EXIST);
        printf("%*s}\n", nestingLevel, "");
    } else {
        printf("\n");
    }
}

void printDocumentAsTree(zgdbFile* file, document* doc) {
    if (doc) {
        printTree(file, doc->header, 0);
    } else {
        printf("Document doesn't exist!\n");
    }
}

bool insertDocument(zgdbFile* file, uint64_t* parentIndexNumber, query* q) {
    // Если вставлять документ не надо (newValues == null), то, если вложенные запросы есть, вернём true, иначе - ошибка:
    if (!q->newValues) {
        return q->nestedQueries;
    }
    // Записываем документ:
    opt_uint64_t ref;
    if (*parentIndexNumber != DOCUMENT_NOT_EXIST) {
        // Считываем заголовок родителя:
        zgdbIndex parentIndex = getIndex(file, *parentIndexNumber);
        documentHeader parentHeader;
        if (parentIndex.flag != INDEX_ALIVE) {
            return false;
        }
        fseeko64(file->f, parentIndex.offset, SEEK_SET);
        if (!fread(&parentHeader, sizeof(documentHeader), 1, file->f)) {
            return false;
        }
        // Записываем документ:
        ref = writeDocument(file, q->newValues, parentHeader.lastChildIndexNumber);
        if (!ref.isPresent) {
            return false;
        }
        // Считываем индекс заново, поскольку родитель мог переместиться:
        parentIndex = getIndex(file, *parentIndexNumber);
        if (parentIndex.flag != INDEX_ALIVE) {
            return false;
        }
        // Перезаписываем последнего ребёнка в заголовке родителя:
        parentHeader.lastChildIndexNumber = ref.value;
        fseeko64(file->f, parentIndex.offset, SEEK_SET);
        if (!fwrite(&parentHeader, sizeof(documentHeader), 1, file->f)) {
            return false;
        }
    } else {
        // Если не указан родитель, то сразу добавляем:
        ref = writeDocument(file, q->newValues, DOCUMENT_NOT_EXIST);
        if (!ref.isPresent) {
            return false;
        }
    }
    *parentIndexNumber = ref.value; // передаём номер индекса для того, чтобы потом добавить детей
    return true;
}

bool updateDocument(zgdbFile* file, uint64_t* indexNumber, query* q) {
    // Если обновлять документ не надо (newValues == null), то, если вложенные запросы есть, вернём true, иначе - ошибка:
    if (!q->newValues) {
        return q->nestedQueries;
    }
    // Обновляем документ:
    zgdbIndex index = getIndex(file, *indexNumber);
    if (index.flag == INDEX_ALIVE) {
        fseeko64(file->f, index.offset, SEEK_SET);
        documentHeader header;
        if (fread(&header, sizeof(documentHeader), 1, file->f)) {
            uint64_t bytesLeft = header.size - sizeof(documentHeader);
            while (bytesLeft > 0) {
                element oldEl;
                uint64_t tmp = readElement(file, &oldEl, true);
                if (!tmp) {
                    return false;
                }
                // Если элемент не существует, то выходим из цикла. Иначе - обновляем элемент:
                if (oldEl.type == TYPE_NOT_EXIST) {
                    bytesLeft = 0;
                } else {
                    bytesLeft -= tmp;
                    element* newEl = getElementFromSchema(q->newValues, oldEl.key);
                    if (newEl) {
                        // Смещаемся к началу только что считанного элемента:
                        fseeko64(file->f, (int64_t) -tmp, SEEK_CUR);
                        if (newEl->type == TYPE_STRING) {
                            if (!updateString(file, &index, &header, &oldEl, newEl)) {
                                free(newEl);
                                return false;
                            }
                        } else if (!writeElement(file, newEl)) {
                            free(newEl);
                            return false;
                        }
                        fseeko64(file->f, 0, SEEK_CUR); // этот вызов нужен для того, чтобы можно было сделать fread
                    }
                }
            }
            return true;
        }
    }
    return false;
}

bool removeDocument(zgdbFile* file, uint64_t* indexNumber, query* q) {
    // Если не дошли до самого конца в дереве запросов, то вызывать удаление - рано!
    if (q && q->nestedQueries) {
        return true;
    }
    zgdbIndex index = getIndex(file, *indexNumber);
    if (index.flag == INDEX_ALIVE) {
        fseeko64(file->f, index.offset, SEEK_SET);
        documentHeader header;
        if (fread(&header, sizeof(documentHeader), 1, file->f)) {
            // Удаляем детей:
            uint64_t childIndexNumber = header.lastChildIndexNumber;
            if (childIndexNumber != DOCUMENT_NOT_EXIST && !removeDocument(file, &childIndexNumber, NULL)) {
                return false;
            }
            // Удаляем брата, если эта функция вызвана другой removeDocument:
            if (!q) {
                uint64_t brotherIndexNumber = header.brotherIndexNumber;
                if (brotherIndexNumber != DOCUMENT_NOT_EXIST && !removeDocument(file, &brotherIndexNumber, NULL)) {
                    return false;
                }
            }
            // Добавляем дырку в список:
            insertNode(&file->list, createNode(header.size, *indexNumber));
            // Если являлись корнем, то обновляем заголовок файла:
            if (file->header.indexOfRoot == *indexNumber) {
                file->header.indexOfRoot = DOCUMENT_NOT_EXIST;
                if (!writeHeader(file)) {
                    return false;
                }
            }
            // Обновляем индекс:
            if (!updateIndex(file, *indexNumber, wrap_uint8_t(INDEX_DEAD), not_present_int64_t())) {
                return false;
            }
            *indexNumber = DOCUMENT_NOT_EXIST;
            return true;
        }
    }
    return false;
}

element* getElementFromDocument(document* doc, const char* key) {
    return doc ? getElementFromSchema(doc->schema, key) : NULL;
}

documentSchema* getSchemaFromDocument(document* doc) {
    return doc ? doc->schema : NULL;
}