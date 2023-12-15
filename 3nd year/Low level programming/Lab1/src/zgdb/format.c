#include <malloc.h>

#include "format.h"
#include "document.h"
#include "element.h"

bool writeHeader(zgdbFile* file) {
    bool result;
    int64_t pos = ftello64(file->f);
    rewind(file->f);
    result = fwrite(&file->header, sizeof(zgdbHeader), 1, file->f);
    fseeko64(file->f, pos, SEEK_SET);
    return result;
}

bool writeNewIndexes(zgdbFile* file, uint64_t count) {
    zgdbIndex index = { INDEX_NEW, 0 };
    fseeko64(file->f, (int64_t) (sizeof(zgdbHeader) + sizeof(zgdbIndex) * file->header.indexCount), SEEK_SET);
    uint64_t written = 0;
    for (uint64_t i = 0; i < count; i++) {
        written += fwrite(&index, sizeof(zgdbIndex), 1, file->f);
        insertNode(&file->list, createNode(0, file->header.indexCount++));
    }
    return written == count;
}

zgdbIndex getIndex(zgdbFile* file, uint64_t i) {
    zgdbIndex index = { INDEX_NOT_EXIST, 0 };
    if (i < file->header.indexCount) {
        fseeko64(file->f, (int64_t) (sizeof(zgdbHeader) + sizeof(zgdbIndex) * i), SEEK_SET);
        fread(&index, sizeof(zgdbIndex), 1, file->f);
    }
    return index;
}

bool updateIndex(zgdbFile* file, uint64_t i, opt_uint8_t flag, opt_int64_t offset) {
    if (i < file->header.indexCount) {
        int64_t pos = ftello64(file->f);
        fseeko64(file->f, (int64_t) (sizeof(zgdbHeader) + sizeof(zgdbIndex) * i), SEEK_SET);
        uint64_t written = 0;
        if (flag.isPresent) {
            written += fwrite(&flag.value, sizeof(uint8_t), 1, file->f);
        } else {
            fseeko64(file->f, sizeof(uint8_t), SEEK_CUR);
        }
        if (offset.isPresent) {
            written += fwrite(&offset.value, sizeof(int64_t), 1, file->f);
        }
        fseeko64(file->f, pos, SEEK_SET);
        return (flag.isPresent == offset.isPresent) ? (written == 2) : (written == 1); // XOR
    }
    return false;
}

bool loadList(zgdbFile* file) {
    // ВНИМАНИЕ: предполагается, что в момент вызова функции хедер уже загружен, и fseek делать не надо
    int64_t pos = sizeof(zgdbHeader);
    for (uint64_t i = 0; i < file->header.indexCount; i++) {
        // Считываем индекс:
        pos += sizeof(zgdbIndex);
        zgdbIndex index;
        if (!fread(&index, sizeof(zgdbIndex), 1, file->f)) {
            return false;
        }
        // Заполняем список:
        if (index.flag == INDEX_NEW) {
            insertNode(&file->list, createNode(0, i));
        } else if (index.flag == INDEX_DEAD) {
            documentHeader header;
            fseeko64(file->f, index.offset, SEEK_SET);
            if (!fread(&header, sizeof(documentHeader), 1, file->f)) {
                return false;
            }
            insertNode(&file->list, createNode(header.size, i));
            fseeko64(file->f, pos, SEEK_SET); // не забываем вернуться к индексам
        }
    }
    return true;
}

zgdbFile* loadFile(const char* filename) {
    zgdbFile* file = malloc(sizeof(zgdbFile));
    if (file) {
        file->f = fopen(filename, "r+b");
        file->list = (sortedList) { NULL, NULL };
        if (file->f && fread(&file->header, sizeof(zgdbHeader), 1, file->f) && loadList(file)) {
            return file;
        }
    }
    closeFile(file);
    return NULL;
}

zgdbFile* createFile(const char* filename) {
    zgdbFile* file = malloc(sizeof(zgdbFile));
    if (file) {
        file->f = fopen(filename, "w+b");
        file->header = (zgdbHeader) { ZGDB_FILETYPE,
                                      sizeof(zgdbHeader) + sizeof(zgdbIndex) * ZGDB_DEFAULT_INDEX_CAPACITY, 0, 0,
                                      DOCUMENT_NOT_EXIST };
        file->list = (sortedList) { NULL, NULL };
        // ВНИМАНИЕ: заголовок записывается после индексов, поскольку writeNewIndexes изменяет indexCount в заголовке.
        if (file->f && writeNewIndexes(file, ZGDB_DEFAULT_INDEX_CAPACITY) && writeHeader(file)) {
            return file;
        }
    }
    closeFile(file);
    return NULL;
}

void closeFile(zgdbFile* file) {
    if (file) {
        if (file->f) {
            fclose(file->f);
        }
        destroyList(&file->list);
        free(file);
    }
}

bool moveData(zgdbFile* file, int64_t* oldPos, int64_t* newPos, uint64_t size) {
    while (size) {
        // Определяем размер буфера и аллоцируем его:
        int64_t bufSize;
        if (size > ZGDB_BUF_SIZE) {
            bufSize = ZGDB_BUF_SIZE;
        } else {
            bufSize = (int64_t) size;
        }
        size -= bufSize;
        uint8_t* buf = malloc(bufSize);

        // Перемещаемся на прошлый адрес и заполняем буфер:
        fseeko64(file->f, *oldPos, SEEK_SET);
        if (!fread(buf, bufSize, 1, file->f)) {
            free(buf);
            return false;
        }
        *oldPos += bufSize;

        // Перемещаемся на новый адрес и пишем из буфера:
        fseeko64(file->f, *newPos, SEEK_SET);
        if (!fwrite(buf, bufSize, 1, file->f)) {
            free(buf);
            return false;
        }
        *newPos += bufSize;
        free(buf);
    }
    return true;
}

bool moveFirstDocuments(zgdbFile* file) {
    // Смещаемся к началу документов:
    int64_t newPos;
    int64_t oldPos = (int64_t) (sizeof(zgdbHeader) + sizeof(zgdbIndex) * file->header.indexCount +
                                file->header.firstDocumentOffset);
    /* Перемещаем документы, пока места недостаточно. Изначально доступно file->header.firstDocumentOffset, поскольку
     * перед документами могут быть неиспользуемые байты: */
    int64_t neededSpace = sizeof(zgdbIndex) * ZGDB_DEFAULT_INDEX_CAPACITY;
    int64_t availableSpace = file->header.firstDocumentOffset;
    while (availableSpace < neededSpace) {
        // Считываем заголовок документа:
        fseeko64(file->f, oldPos, SEEK_SET);
        documentHeader header;
        if (!fread(&header, sizeof(documentHeader), 1, file->f)) {
            return false;
        }
        // Считываем индекс, привязанный к документу:
        uint64_t newHeaderSize = 0;
        zgdbIndex index = getIndex(file, header.indexNumber);
        if (index.flag == INDEX_DEAD) {
            // Если наш документ - дырка, удаляем его из списка индексов и делаем INDEX_NEW.
            if (!removeNodeByIndexNumber(&file->list, header.indexNumber) ||
                !updateIndex(file, header.indexNumber, wrap_uint8_t(INDEX_NEW), wrap_int64_t(0))) {
                return false;
            }
            insertNode(&file->list, createNode(0, header.indexNumber));
            oldPos += (int64_t) header.size;
        } else if (index.flag == INDEX_ALIVE) {
            /* Если документ живой, то его нужно переместить.
             * Если есть подходящая дырка, в которую можно переместить документ, то нужно сделать индекс дырки новым
             * (flag = INDEX_NEW, offset = 0), а прошлое смещение дырки записать в индекс переносимого блока.
             * Если подходящих дырок нет (или список пустой), то нужно перемещать документ в конец файла. */
            if (file->list.front && file->list.front->size >= header.size) {
                zgdbIndex gapIndex = getIndex(file, file->list.front->indexNumber);
                if (gapIndex.flag != INDEX_DEAD ||
                    !updateIndex(file, file->list.front->indexNumber, wrap_uint8_t(INDEX_NEW), wrap_int64_t(0))) {
                    return false;
                }
                newPos = gapIndex.offset;
                newHeaderSize = file->list.front->size;
                // Записываем дырку обратно в список, но уже с размером 0:
                listNode* node = popFront(&file->list);
                node->size = 0;
                insertNode(&file->list, node);
                // Если дырка больше, чем надо, записываем TYPE_NOT_EXIST в том месте, где будет заканчиваться документ:
                if (newHeaderSize > header.size) {
                    uint8_t startOfUnusedSpaceMark = TYPE_NOT_EXIST;
                    fseeko64(file->f, newPos + (int64_t) header.size, SEEK_SET);
                    if (!fwrite(&startOfUnusedSpaceMark, sizeof(uint8_t), 1, file->f)) {
                        return false;
                    }
                }
            } else {
                newPos = file->header.fileSize;
                // Обновляем размер файла:
                file->header.fileSize += (int64_t) header.size;
                if (!writeHeader(file)) {
                    return false;
                }
            }
            // Перемещаем документ, обновляем смещение в его индексе:
            if (!updateIndex(file, header.indexNumber, not_present_uint8_t(), wrap_int64_t(newPos)) ||
                !moveData(file, &oldPos, &newPos, header.size)) {
                return false;
            }
        } else {
            return false;
        }
        availableSpace += (int64_t) header.size; // возможно переполнение, если ZGDB_DEFAULT_INDEX_CAPACITY будет слишком большим!
        // Смещаемся к началу нового места документа и обновляем его заголовок, если он был перемещён в дырку:
        if (newHeaderSize) {
            fseeko64(file->f, newPos - (int64_t) header.size, SEEK_SET);
            header.size = newHeaderSize;
            if (!fwrite(&header, sizeof(documentHeader), 1, file->f)) {
                return false;
            }
        }
    }
    // Записываем новые индексы и сохраняем остаток места:
    file->header.firstDocumentOffset = availableSpace % sizeof(zgdbIndex);
    if (!writeNewIndexes(file, availableSpace / sizeof(zgdbIndex)) || !writeHeader(file)) {
        return false;
    }
    return true;
}