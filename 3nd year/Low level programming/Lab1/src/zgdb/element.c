#include <malloc.h>
#include <string.h>

#include "format.h"
#include "document.h"
#include "element.h"

element* createElement(const char* key, element el) {
    if (key && strlen(key) <= 12) {
        element* ptr = malloc(sizeof(element));
        if (ptr) {
            *ptr = el;
            ptr->wasLoaded = false; // устанавливаем флаг
            memset(ptr->key, 0, 13);
            strncpy(ptr->key, key, 13);
            return ptr;
        }
    }
    return NULL;
}

element* intElement(const char* key, int32_t value) {
    return createElement(key, (element) { .type = TYPE_INT, .integerValue = value });
}

element* doubleElement(const char* key, double value) {
    return createElement(key, (element) { .type = TYPE_DOUBLE, .doubleValue = value });
}

element* booleanElement(const char* key, bool value) {
    return createElement(key, (element) { .type = TYPE_BOOLEAN, .booleanValue = (uint8_t) value });
}

element* stringElement(const char* key, char* value) {
    if (value) {
        return createElement(key, (element) { .type = TYPE_STRING, .stringValue = (str) { strlen(value) + 1, value }});
    }
    return NULL;
}

void destroyElement(element* el) {
    if (el) {
        // Если элемент был загружен из файла, то для stringValue.data был вызван malloc. Чистим:
        if (el->type == TYPE_STRING && el->stringValue.data && el->wasLoaded) {
            free(el->stringValue.data);
        }
        free(el);
    }
}

uint64_t writeElement(zgdbFile* file, element* el) {
    uint64_t bytesWritten = 0;
    bytesWritten += fwrite(&el->type, sizeof(uint8_t), 1, file->f);
    bytesWritten += fwrite(el->key, sizeof(char), 13, file->f) * sizeof(char);
    switch (el->type) {
        case TYPE_INT:
            bytesWritten += fwrite(&el->integerValue, sizeof(int32_t), 1, file->f) * sizeof(int32_t);
            break;
        case TYPE_DOUBLE:
            bytesWritten += fwrite(&el->doubleValue, sizeof(double), 1, file->f) * sizeof(double);
            break;
        case TYPE_BOOLEAN:
            bytesWritten += fwrite(&el->booleanValue, sizeof(uint8_t), 1, file->f);
            break;
        case TYPE_STRING:
            bytesWritten += fwrite(&el->stringValue.size, sizeof(uint32_t), 1, file->f) * sizeof(uint32_t);
            bytesWritten += fwrite(el->stringValue.data, sizeof(char), el->stringValue.size, file->f);
            break;
    }
    return bytesWritten;
}

uint64_t readElement(zgdbFile* file, element* el, bool skipStrings) {
    el->wasLoaded = true;
    if (fread(&el->type, sizeof(uint8_t), 1, file->f)) {
        if (el->type == TYPE_NOT_EXIST) {
            return sizeof(uint8_t);
        } else if (fread(&el->key, sizeof(char), 13, file->f) == 13) {
            uint64_t bytesRead = sizeof(uint8_t) + sizeof(char) * 13;
            switch (el->type) {
                case TYPE_NOT_EXIST:
                    return bytesRead;
                case TYPE_INT:
                    return fread(&el->integerValue, sizeof(int32_t), 1, file->f) ? bytesRead + sizeof(int32_t) : 0;
                case TYPE_DOUBLE:
                    return fread(&el->doubleValue, sizeof(double), 1, file->f) ? bytesRead + sizeof(double) : 0;
                case TYPE_BOOLEAN:
                    return fread(&el->booleanValue, sizeof(uint8_t), 1, file->f) ? bytesRead + sizeof(uint8_t) : 0;
                case TYPE_STRING:
                    if (fread(&el->stringValue.size, sizeof(uint32_t), 1, file->f)) {
                        // Если нужно пропустить строку (например, при поиске вложенных документов), то не загружаем её:
                        if (skipStrings) {
                            fseeko64(file->f, el->stringValue.size, SEEK_CUR);
                            return bytesRead + sizeof(uint32_t) + el->stringValue.size;
                        }
                        // Если пропускать не нужно, то выделяем память:
                        el->stringValue.data = malloc(sizeof(char) * el->stringValue.size);
                        if (el->stringValue.data) {
                            if (fread(el->stringValue.data, sizeof(char), el->stringValue.size, file->f) ==
                                el->stringValue.size) {
                                return bytesRead + sizeof(uint32_t) + el->stringValue.size;
                            }
                            free(el->stringValue.data);
                        }
                    }
                    return 0;
            }
        }
    }
    return 0;
}

void printElement(element* el) {
    if (el) {
        printf("%s = ", el->key);
        switch (el->type) {
            case TYPE_INT:
                printf("%d\n", el->integerValue);
                break;
            case TYPE_DOUBLE:
                printf("%f\n", el->doubleValue);
                break;
            case TYPE_BOOLEAN:
                printf("%s\n", el->booleanValue ? "true" : "false");
                break;
            case TYPE_STRING:
                printf("\"%s\"\n", el->stringValue.data);
                break;
        }
    } else {
        printf("Element doesn't exist!\n");
    }
}

bool updateString(zgdbFile* file, zgdbIndex* index, documentHeader* header, element* oldEl, element* newEl) {
    uint64_t newHeaderSize = 0;
    int64_t offsetOfElement = ftello64(file->f) - index->offset; // смещение строки относительно начала документа
    int64_t delta = (int64_t) newEl->stringValue.size - (int64_t) oldEl->stringValue.size; // изменение размера строки

    // Если строка стала больше, то ей нужно найти новое место:
    if (delta > 0) {
        // Если документ не в конце файла, ищем дырку и переносим его:
        if (index->offset + header->size != file->header.fileSize) {
            int64_t oldPos = index->offset;
            int64_t newPos;
            documentHeader gapHeader = *header;
            int64_t diff = file->list.front ? (int64_t) file->list.front->size - (int64_t) header->size - delta : -1;
            if (diff >= 0) {
                // Считываем индекс дырки и обновляем в нём смещение:
                zgdbIndex gapIndex = getIndex(file, file->list.front->indexNumber);
                if (gapIndex.flag != INDEX_DEAD ||
                    !updateIndex(file, file->list.front->indexNumber, not_present_uint8_t(),
                                 wrap_int64_t(index->offset))) {
                    return false;
                }
                gapHeader.indexNumber = file->list.front->indexNumber; // записываем в хедер для будущей дырки номер индекса текущей
                newPos = index->offset = gapIndex.offset;
                newHeaderSize = file->list.front->size;
                listNode* node = popFront(&file->list);
                node->size = header->size;
                insertNode(&file->list, node);
                // Если дырка больше, чем надо, записываем TYPE_NOT_EXIST в том месте, где будет заканчиваться документ:
                if (diff) {
                    uint8_t startOfUnusedSpaceMark = TYPE_NOT_EXIST;
                    fseeko64(file->f, newPos + (int64_t) header->size, SEEK_SET);
                    if (!fwrite(&startOfUnusedSpaceMark, sizeof(uint8_t), 1, file->f)) {
                        return false;
                    }
                }
            } else {
                // На предыдущем месте образуется дырка, следовательно, нужны индексы:
                if ((!file->list.back || file->list.back->size) && !moveFirstDocuments(file)) {
                    return false;
                }
                // Заново считываем индекс документа, поскольку он мог быть перемещён:
                *index = getIndex(file, header->indexNumber);
                if (index->flag != INDEX_ALIVE) {
                    return false;
                }
                // Если документ не переместился в конец, нужно его туда переместить:
                if (index->offset + header->size != file->header.fileSize) {
                    // Считываем INDEX_NEW индекс, делаем его INDEX_DEAD и записываем в него текущее смещение документа:
                    zgdbIndex gapIndex = getIndex(file, file->list.back->indexNumber);
                    if (gapIndex.flag != INDEX_NEW ||
                        !updateIndex(file, file->list.back->indexNumber, wrap_uint8_t(INDEX_DEAD),
                                     wrap_int64_t(index->offset))) {
                        return false;
                    }
                    gapHeader.indexNumber = file->list.back->indexNumber; // записываем в хедер для будущей дырки номер индекса текущей
                    listNode* node = popBack(&file->list);
                    node->size = header->size;
                    insertNode(&file->list, node);
                    oldPos = index->offset;
                    newPos = index->offset = file->header.fileSize;
                    file->header.fileSize += (int64_t) header->size + delta;
                } else {
                    newPos = oldPos; // условие для того, чтобы не перемещать документ
                    file->header.fileSize += delta;
                }
                // Обновляем fileSize:
                if (!writeHeader(file)) {
                    return false;
                }
            }
            // Перемещаем документ, если он не оказался в конце файла, обновляем смещение в его индексе и записываем на его месте хедер дырки:
            if (newPos != oldPos) {
                if (!updateIndex(file, header->indexNumber, not_present_uint8_t(), wrap_int64_t(newPos)) ||
                    !moveData(file, &oldPos, &newPos, header->size)) {
                    return false;
                }
                fseeko64(file->f, oldPos - (int64_t) header->size, SEEK_SET);
                if (!fwrite(&gapHeader, sizeof(documentHeader), 1, file->f)) {
                    return false;
                }
            }
        } else {
            file->header.fileSize += delta;
            if (!writeHeader(file)) {
                return false;
            }
        }
    }

    // Перемещаем кусок документа после строки, чтобы не перекрыть его новой строкой и чтобы не было дырок:
    int64_t oldPos = (int64_t) (index->offset + offsetOfElement + sizeof(oldEl->type) + sizeof(oldEl->key) +
                                sizeof(oldEl->stringValue.size) + oldEl->stringValue.size);
    int64_t newPos = oldPos + delta;
    if (!moveData(file, &oldPos, &newPos, index->offset + header->size - oldPos)) {
        return false;
    }
    // Перезаписываем размер документа:
    header->size = newHeaderSize ? newHeaderSize : header->size + delta;
    fseeko64(file->f, index->offset, SEEK_SET);
    if (!fwrite(header, sizeof(documentHeader), 1, file->f)) {
        return false;
    }
    // Возвращаемся к началу элемента, перезаписываем его:
    fseeko64(file->f, index->offset + offsetOfElement, SEEK_SET);
    if (!writeElement(file, newEl)) {
        return false;
    }
    return true;
}