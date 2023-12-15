#include <string.h>
#include <malloc.h>

#include "format.h"
#include "query.h"
#include "condition.h"
#include "element.h"
#include "iterator.h"
#include "schema.h"

query* createQuery(queryType type, const char* schemaName, documentSchema* newValues, condition* cond) {
    query* q = malloc(sizeof(query));
    if (q) {
        q->type = type;
        q->schemaName = schemaName;
        q->newValues = newValues;
        q->cond = cond;
        q->nestedQueries = NULL;
        q->length = 0;
        return q;
    }
    return NULL;
}

query* createSelectQuery(const char* schemaName, condition* cond) {
    if (schemaName && strlen(schemaName) <= 12) {
        return createQuery(SELECT_QUERY, schemaName, NULL, cond);
    }
    return NULL;
}

query* createInsertQuery(const char* schemaName, documentSchema* newValues, condition* cond) {
    /* Если сам query (а не его будущие вложенные query) должен добавить новый документ, то добавление должно произойти
     * без условий, ну и должна быть передана схема документа: */
    if (!schemaName && (!newValues || cond)) {
        return NULL;
    }
    /* Если сам query используется для навигации по дереву, то в него нельзя передать схему и его имя не должно быть
     * длиннее 12 символов: */
    if (schemaName && (newValues || strlen(schemaName) > 12)) {
        return NULL;
    }
    return createQuery(INSERT_QUERY, schemaName, newValues, cond);
}

query* createUpdateQuery(const char* schemaName, documentSchema* newValues, condition* cond) {
    if (schemaName && strlen(schemaName) <= 12) {
        return createQuery(UPDATE_QUERY, schemaName, newValues, cond);
    }
    return NULL;
}

query* createDeleteQuery(const char* schemaName, condition* cond) {
    if (schemaName && strlen(schemaName) <= 12) {
        return createQuery(DELETE_QUERY, schemaName, NULL, cond);
    }
    return NULL;
}

void destroyQuery(query* q) {
    if (q) {
        if (q->nestedQueries) {
            for (uint64_t i = 0; i < q->length; i++) {
                destroyQuery(q->nestedQueries[i]);
            }
            free(q->nestedQueries);
        }
        free(q);
    }
}

bool addNestedQuery(query* q, query* nq) {
    if (q && nq && q->type == nq->type) {
        /* В случае, если мы добавляем insert/update запрос, который находится на самом нижнем уровне, и не передаём туда
         * значения для записи, то это ошибка: */
        if ((nq->type == INSERT_QUERY || nq->type == UPDATE_QUERY) && !nq->newValues && !nq->nestedQueries) {
            return false;
        }
        query** tmp = realloc(q->nestedQueries, sizeof(query*) * (q->length + 1));
        if (tmp) {
            q->nestedQueries = tmp;
            q->nestedQueries[q->length++] = nq;
            return true;
        }
    }
    return false;
}

bool executeSelect(zgdbFile* file, bool* error, iterator** it, query* q) {
    if (q && q->type == SELECT_QUERY) {
        *it = createIterator();
        if (*it) {
            uint64_t indexOfRoot = file->header.indexOfRoot;
            return findAndMutate(file, error, *it, &indexOfRoot, q, NULL);
        }
    }
    *error = true;
    return false;
}

bool executeInsert(zgdbFile* file, bool* error, query* q) {
    // Помимо обычных проверок, проверяем, что не создаём второй корень:
    if (q && q->type == INSERT_QUERY && (q->schemaName || file->header.indexOfRoot == DOCUMENT_NOT_EXIST)) {
        uint64_t indexOfRoot = file->header.indexOfRoot;
        return findAndMutate(file, error, NULL, &indexOfRoot, q, &insertDocument);
    }
    *error = true;
    return false;
}

bool executeUpdate(zgdbFile* file, bool* error, query* q) {
    if (q && q->type == UPDATE_QUERY) {
        uint64_t indexOfRoot = file->header.indexOfRoot;
        return findAndMutate(file, error, NULL, &indexOfRoot, q, &updateDocument);
    }
    *error = true;
    return false;
}

bool executeDelete(zgdbFile* file, bool* error, query* q) {
    if (q && q->type == DELETE_QUERY) {
        uint64_t indexOfRoot = file->header.indexOfRoot;
        return findAndMutate(file, error, NULL, &indexOfRoot, q, &removeDocument);
    }
    *error = true;
    return false;
}

bool findAndMutate(zgdbFile* file, bool* error, iterator* it, uint64_t* indexNumber, query* q,
                   bool (* mutate)(zgdbFile*, uint64_t*, query*)) {
    bool match = checkDocument(file, *indexNumber, q);
    resetCondition(q->cond); // сброс cond.met
    if (match && (q->type == SELECT_QUERY || mutate(file, indexNumber, q))) {
        // Если есть вложенные query, продолжаем рекурсию; иначе - добавляем в итератор текущий индекс (в случае select):
        if (q->nestedQueries) {
            // Сначала надо считать хедер родителя:
            zgdbIndex index = getIndex(file, *indexNumber);
            if (index.flag != INDEX_ALIVE) {
                *error = true;
                return false;
            }
            fseeko64(file->f, index.offset, SEEK_SET);
            documentHeader header;
            if (!fread(&header, sizeof(documentHeader), 1, file->f)) {
                *error = true;
                return false;
            }
            // Потом выполняем вложенные запросы для каждого из детей:
            for (uint64_t i = 0; i < q->length; i++) {
                // В случае вставки в только что созданный документ, его детей проверять не надо. Просто вызываем рекурсию:
                if (q->type == INSERT_QUERY && q->nestedQueries[i]->newValues) {
                    uint64_t parentIndexNumber = *indexNumber;
                    if (!findAndMutate(file, error, it, &parentIndexNumber, q->nestedQueries[i], mutate)) {
                        return false;
                    }
                } else {
                    bool atLeastOneFound = false;
                    uint64_t childIndexNumber = header.lastChildIndexNumber;
                    while (childIndexNumber != DOCUMENT_NOT_EXIST) {
                        // Выбираем следующего ребёнка (заранее, поскольку текущий ребёнок может удалиться):
                        zgdbIndex childIndex = getIndex(file, childIndexNumber);
                        if (childIndex.flag != INDEX_ALIVE) {
                            *error = true;
                            return false;
                        }
                        fseeko64(file->f, childIndex.offset, SEEK_SET);
                        documentHeader childHeader;
                        if (!fread(&childHeader, sizeof(documentHeader), 1, file->f)) {
                            *error = true;
                            return false;
                        }
                        // Выполняем запрос:
                        atLeastOneFound |= findAndMutate(file, error, it, &childIndexNumber, q->nestedQueries[i],
                                                         mutate);
                        if (*error) {
                            return false;
                        }
                        /* При успешном вызове removeDocument в childIndexNumber передаётся DOCUMENT_NOT_EXIST.
                         * В этом случае надо перезаписать заголовок родителя: */
                        if (q->type == DELETE_QUERY && childIndexNumber == DOCUMENT_NOT_EXIST) {
                            header.lastChildIndexNumber = childHeader.brotherIndexNumber;
                            fseeko64(file->f, index.offset, SEEK_SET);
                            if (!fwrite(&header, sizeof(documentHeader), 1, file->f)) {
                                *error = true;
                                return false;
                            }
                        }
                        // Берём следующего ребёнка (т.е. брата текущего):
                        childIndexNumber = childHeader.brotherIndexNumber;
                    }
                    // Если ни один из детей не подошёл, то возвращаем false:
                    if (!atLeastOneFound) {
                        return false;
                    }
                }
            }
            return true;
        } else if (q->type == SELECT_QUERY) {
            return addRef(it, *indexNumber);
        }
        return true;
    }
    return false;
}