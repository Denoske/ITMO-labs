#ifndef _CONDITION_PUBLIC_H_
#define _CONDITION_PUBLIC_H_

#include "element_public.h"

/* Структура для условия. */
typedef struct condition condition;

/* Функция для создания условия типа "==".
 * Возвращает NULL при неудаче. */
condition* condEqual(element* el);

/* Функция для создания условия типа "!=".
 * Возвращает NULL при неудаче. */
condition* condNotEqual(element* el);

/* Функция для создания условия типа ">".
 * Возвращает NULL при неудаче. */
condition* condGreater(element* el);

/* Функция для создания условия типа ">=".
 * Возвращает NULL при неудаче. */
condition* condGreaterOrEqual(element* el);

/* Функция для создания условия типа "<".
 * Возвращает NULL при неудаче. */
condition* condLess(element* el);

/* Функция для создания условия типа "<=".
 * Возвращает NULL при неудаче. */
condition* condLessOrEqual(element* el);

/* Функция для создания условия типа "&".
 * Возвращает NULL при неудаче. */
condition* condAnd(condition* cond1, condition* cond2);

/* Функция для создания условия типа "|".
 * Возвращает NULL при неудаче. */
condition* condOr(condition* cond1, condition* cond2);

/* Функция для создания условия типа "!".
 * Возвращает NULL при неудаче. */
condition* condNot(condition* cond);

/* Функция для уничтожения условия.
 * ВНИМАНИЕ: все вложенные условия (и элементы в них) тоже уничтожаются! Сделано так для того, чтобы память не текла в ситуациях, когда
 * в конструктор условия передаётся другой конструктор условия. */
void destroyCondition(condition* cond);

#endif