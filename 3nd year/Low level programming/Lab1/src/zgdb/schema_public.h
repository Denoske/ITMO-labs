#ifndef _SCHEMA_PUBLIC_H_
#define _SCHEMA_PUBLIC_H_

#include <stdbool.h>

#include "element_public.h"

/* Структура для схемы данных. */
typedef struct documentSchema documentSchema;

/* Функция для создания схемы. Имя передавать обязательно!
 * Возвращает NULL при неудаче. */
documentSchema* createSchema(const char* name);

/* Функция для создания набора элементов схемы. Имя передавать необязательно.
 * Возвращает NULL при неудаче. */
documentSchema* createElements();

/* Функция для уничтожения схемы. */
void destroySchema(documentSchema* schema);

/* Функция для добавления элемента в схему.
 * Возвращает false при неудаче. */
bool addElementToSchema(documentSchema* schema, element* el);

#endif