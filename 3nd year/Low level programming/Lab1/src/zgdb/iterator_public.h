#ifndef _ITERATOR_PUBLIC_H_
#define _ITERATOR_PUBLIC_H_

#include <stdbool.h>

#include "format_public.h"
#include "document_public.h"

/* Структура "итератор" для навигации по набору документов. */
typedef struct iterator iterator;

/* Функция для уничтожения итератора. */
void destroyIterator(iterator* it);

/* Функция для проверки того, что в наборе документов есть следующий документ.
 * Возвращает false, если документы закончились. */
bool hasNext(iterator* it);

/* Функция для получения следующего документа из набора.
 * Возвращает NULL, если документы закончились. */
document* next(zgdbFile* file, iterator* it);

#endif