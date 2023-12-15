#ifndef _SCHEMA_H_
#define _SCHEMA_H_

#include <stdint.h>

#include "schema_public.h"
#include "element_public.h"

struct documentSchema {
    element** elements; // указатель на массив указателей на элементы
    uint64_t length; // длина массива
    char name[13]; // имя схемы
};

/* Функция для расчёта размера будущего документа по схеме.
 * Возвращает будущее количество байт. */
uint64_t calcDocumentSize(documentSchema* schema);

/* Функция для получения элемента их схемы по ключу.
 * Возвращает NULL при неудаче. */
element* getElementFromSchema(documentSchema* schema, const char* key);

#endif