#ifndef _ITERATOR_H_
#define _ITERATOR_H_

#include <stdint.h>

#include "iterator_public.h"

struct iterator {
    uint64_t* refs; // массив номеров индексов документов, которые попали в выборку
    uint64_t length; // длина массива
    int64_t curr; // текущий элемент, на котором находится итератор
};

/* Функция для создания итератора.
 * Возвращает NULL при неудаче. */
iterator* createIterator();

/* Функция для добавления номера документа в набор.
 * Возвращает false при неудаче. */
bool addRef(iterator* dest, uint64_t ref);

#endif