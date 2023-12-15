#ifndef _LIST_H_
#define _LIST_H_

#include <stdint.h>
#include <stdbool.h>

/* Структура для узла списка. */
typedef struct listNode {
    uint64_t size : 40; // размер документа
    uint64_t indexNumber : 40; // номер индекса
    struct listNode* prev; // указатель на предыдущий элемент списка
    struct listNode* next; // указатель на следующий элемент списка
} listNode;

/* Структура для отсортированного списка индексов свободных мест в файле. */
typedef struct sortedList {
    listNode* front; // указатель на первый элемент списка
    listNode* back; // указатель на последний элемент списка
} sortedList;

/* Функция для создания узла. */
listNode* createNode(uint64_t size, uint64_t indexNumber);

/* Функция для уничтожения списка. */
void destroyList(sortedList* list);

/* Функция для вставки узла. */
void insertNode(sortedList* list, listNode* node);

/* Функция для извлечения первого узла из списка. */
listNode* popFront(sortedList* list);

/* Функция для извлечения последнего узла из списка. */
listNode* popBack(sortedList* list);

/* Функция для удаления из списка узла, привязанного к определённому документу. */
bool removeNodeByIndexNumber(sortedList* list, uint64_t indexNumber);

#endif