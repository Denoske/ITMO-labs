#ifndef _DOCUMENT_H_
#define _DOCUMENT_H_

#include <stdint.h>
#include <stdbool.h>

#include "document_public.h"
#include "element_public.h"
#include "iterator_public.h"
#include "query_public.h"
#include "../utils/optional.h"

/* Структура для id, привязанного к документу. */
typedef struct __attribute__((packed)) documentId {
    uint32_t timestamp; // время создания документа в секундах с эпохи UNIX
    int64_t offset; // смещение документа относительно начала файла на момент создания документа
} documentId;

/* Структура для заголовка документа. */
typedef struct __attribute__((packed)) documentHeader {
    uint64_t size : 40; // (5 байт) размер документа в байтах
    uint64_t indexNumber : 40; // (5 байт) номер индекса, прикрепленного к документу
    uint64_t lastChildIndexNumber : 40; // (5 байт) номер индекса, прикрепленного к последнему добавленному ребёнку
    uint64_t brotherIndexNumber : 40; // (5 байт) номер индекса, прикрепленного к следующему "брату" документа
    documentId id; // id, привязанный к документу
    char schemaName[13]; // имя схемы, по которой построен документ
} documentHeader;

struct document {
    documentHeader header; // заголовок документа
    documentSchema* schema; // указатель на схему документа
};

/* Функция для создания структуры, хранящей документ в оперативной памяти (не в файле!).
 * Возвращает NULL при неудаче. */
document* createDocument();

/* Функция для записи нового документа в файл.
 * ВАЖНО: Принимает brotherIndexNumber, за счёт которого прикрепляется к "списку братьев" в родителе.
 * Возвращает обёрнутый номер индекса записанного документа. */
opt_uint64_t writeDocument(zgdbFile* file, documentSchema* schema, uint64_t brotherIndexNumber);

/* Функция для чтения документа из файла в оперативную память.
 * Возвращает NULL при неудаче. */
document* readDocument(zgdbFile* file, uint64_t indexNumber);

/* Функция для рекурсивного вывода информации из заголовков документов в дереве. */
void printTree(zgdbFile* file, documentHeader header, uint64_t nestingLevel);

/* Функция для вставки документа в родителя. Предварительно вызывает writeDocument.
 * Возвращает false при неудаче. */
bool insertDocument(zgdbFile* file, uint64_t* parentIndexNumber, query* q);

/* Функция для обновления документа по его номеру индекса.
 * Возвращает false при неудаче. */
bool updateDocument(zgdbFile* file, uint64_t* indexNumber, query* q);

/* Функция для удаления документа (и всех вложенных в него документов) по его номеру индекса.
 * Возвращает false при неудаче. */
bool removeDocument(zgdbFile* file, uint64_t* indexNumber, query* q);

#endif