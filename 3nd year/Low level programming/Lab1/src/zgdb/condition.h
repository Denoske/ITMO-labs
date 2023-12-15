#ifndef _CONDITION_H_
#define _CONDITION_H_

#include <stdint.h>
#include <stdbool.h>

#include "format_public.h"
#include "condition_public.h"
#include "schema_public.h"
#include "query_public.h"

/* Типы операций. Логические операции применимы ТОЛЬКО к условиям (чтобы делать, например, нечто вроде !cond1 | cond2) */
typedef enum operationType {
    OP_EQ, // операция "=="
    OP_NEQ, // операция "!="
    OP_GT, // операция ">"
    OP_GTE, // операция ">="
    OP_LE, // операция "<"
    OP_LEE, // операция "<="
    OP_AND, // операция "&"
    OP_OR, // операция "|"
    OP_NOT, // операция "!"
} operationType;

struct condition {
    bool isMet;
    operationType opType; // тип операции
    union {
        element* el; // элемент для сравнения (если операция - НЕ логическая)
        condition* cond1; // первое условие (если операция - логическая)
    };
    condition* cond2; // второе условие (если операция - логическая и НЕ "!")
};

/* Функция для создания условия.
 * Возвращает NULL при неудаче. */
condition* createCondition(operationType type, void* operand1, void* operand2);

/* Функция для проверки того, что элемент соответствует условию. Если условие логическое, то оно "пробрасывает" элемент
 * дальше рекурсивно.
 * Возвращает false при неудаче. */
bool checkCondition(element* el, condition* cond);

/* Функция для сброса cond.isMet во всех условиях в цепочке условий. */
void resetCondition(condition* cond);

/* Функция для проверки документа с определенным номером индекса. Проверяется соответствие условию и схеме (в случае,
 * когда документ обновляется, нужно понять, возможно ли вставить в него новые элементы, или в его схеме элементы с такими
 * ключами отсутствуют).
 * ВНИМАНИЕ: После вызова обязательно нужен resetCondition, чтобы сбросить cond.isMet во всех условиях в цепочке.
 * Возвращает false при неудаче. */
bool checkDocument(zgdbFile* file, uint64_t indexNumber, query* q);

/* Функция для сравнения двух элементов.
 * Возвращает:
 *  x > 0, если el1.value > el2.value
 *  x = 0, если el1.value == el2.value
 *  x < 0, если el1.value < el2.value */
int32_t compare(element* el1, element* el2);

#endif