#ifndef _QUERY_PUBLIC_H_
#define _QUERY_PUBLIC_H_

#include <stdbool.h>

#include "format_public.h"
#include "condition_public.h"
#include "iterator_public.h"
#include "schema_public.h"

/* Структура для запроса. */
typedef struct query query;

/* Функция для создания запроса SELECT. Условие опционально, имя - обязательно.
 * Возвращает NULL при неудаче. */
query* createSelectQuery(const char* schemaName, condition* cond);

/* Функция для создания запроса INSERT. Условие опционально. Если сам данные не добавляет (нужен только для того, чтобы
 * дойти до места вставки), то обязательно имя, иначе - новые значения.
 * ВНИМАНИЕ: Одновременно передать и schemaName, и newValues нельзя, поскольку тогда это уже не INSERT, а UPDATE!
 * ВНИМАНИЕ: Если не передан schemaName, то cond передавать нельзя!
 * Возвращает NULL при неудаче. */
query* createInsertQuery(const char* schemaName, documentSchema* newValues, condition* cond);

/* Функция для создания запроса UPDATE. Условие и новые значения опциональны, а вот имя - обязательно.
 * ВНИМАНИЕ: Не передать schemaName, передав newValues, нельзя, поскольку тогда это уже не UPDATE, а INSERT!
 * Возвращает NULL при неудаче. */
query* createUpdateQuery(const char* schemaName, documentSchema* newValues, condition* cond);

/* Функция для создания запроса DELETE. Условие опционально, имя - обязательно.
 * Возвращает NULL при неудаче. */
query* createDeleteQuery(const char* schemaName, condition* cond);

/* Функция для уничтожения запроса.
 * ВНИМАНИЕ: Уничтожает и все подзапросы! */
void destroyQuery(query* q);

/* Функция для добавления подзапроса nq в запрос q.
 * ВНИМАНИЕ: Если добавляется INSERT/UPDATE подзапрос самого нижнего уровня (т.е. в нём нет подзапросов), то у него
 * обязательно должны быть новые значения. Иначе запрос теряет смысл, мы просто дойдём до низа дерева и ничего не сделаем!
 * Возвращает false при неудаче. */
bool addNestedQuery(query* q, query* nq);

/* Функция для выполнения запроса SELECT. Передаёт в it итератор над набором данных, которые были выбраны.
 * Если произошла ошибка, устанавливает error = true.
 * Возвращает false, если какая-то часть запроса не была выполнена или произошла ошибка. */
bool executeSelect(zgdbFile* file, bool* error, iterator** it, query* q);

/* Функция для выполнения запроса INSERT. Если произошла ошибка, устанавливает error = true.
 * Возвращает false, если какая-то часть запроса не была выполнена или произошла ошибка. */
bool executeInsert(zgdbFile* file, bool* error, query* q);

/* Функция для выполнения запроса UPDATE. Если произошла ошибка, устанавливает error = true.
 * Возвращает false, если какая-то часть запроса не была выполнена или произошла ошибка. */
bool executeUpdate(zgdbFile* file, bool* error, query* q);

/* Функция для выполнения запроса DELETE. Если произошла ошибка, устанавливает error = true.
 * Возвращает false, если какая-то часть запроса не была выполнена или произошла ошибка. */
bool executeDelete(zgdbFile* file, bool* error, query* q);

#endif