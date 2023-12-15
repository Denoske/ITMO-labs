#ifndef _QUERY_H_
#define _QUERY_H_

#include <stdint.h>
#include <stdbool.h>

#include "query_public.h"

/* Тип запроса. */
typedef enum queryType {
    SELECT_QUERY,
    INSERT_QUERY,
    UPDATE_QUERY,
    DELETE_QUERY
} queryType;

struct query {
    queryType type; // тип запроса
    const char* schemaName; // имя требуемой схемы
    documentSchema* newValues;  // указатель на схему, в которой хранятся новые значения
    condition* cond; // условие
    query** nestedQueries; // массив указателей на вложенные запросы
    uint64_t length; // длина массива вложенных запросов
};

/* Функция для создания запроса. */
query* createQuery(queryType type, const char* schemaName, documentSchema* newValues, condition* cond);

/* Функция для рекурсивного поиска и изменения документов по запросу. */
bool findAndMutate(zgdbFile* file, bool* error, iterator* it, uint64_t* indexNumber, query* q,
                   bool (* mutate)(zgdbFile*, uint64_t*, query*));

#endif