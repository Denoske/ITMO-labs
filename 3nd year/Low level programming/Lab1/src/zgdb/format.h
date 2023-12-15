#ifndef _FORMAT_H_
#define _FORMAT_H_

#define ZGDB_FILETYPE 0x4244475A
#define ZGDB_DEFAULT_INDEX_CAPACITY 10000
#define ZGDB_BUF_SIZE 500000000 // при перемещении большие документы будут перемещаться кусками по 500Мб

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "format_public.h"
#include "list.h"
#include "../utils/optional.h"

/* Структура для заголовка ZGDB файла. */
typedef struct __attribute__((packed)) zgdbHeader {
    uint32_t fileType; // должны быть записаны 4 буквы в UTF-8: ZGDB
    int64_t fileSize; // размер файла
    uint8_t firstDocumentOffset; // смещение первого документа относительно конца индексов; остаток от деления на 9, поэтому не больше 8
    uint64_t indexCount : 40; // (5 байт) количество всех индексов файла
    uint64_t indexOfRoot : 40;
} zgdbHeader;

struct zgdbFile {
    FILE* f; // указатель на FILE
    zgdbHeader header; // заголовок
    sortedList list; // отсортированный список индексов свободных мест в файле
};

/* Флаги для индексов. */
typedef enum {
    INDEX_NOT_EXIST = 0, // флаг, сигнализирующий об ошибке
    INDEX_NEW = 1, // индекс только что создан и ещё не привязан к блоку
    INDEX_ALIVE = 2, // индекс привязан к использующемуся ("живому") блоку
    INDEX_DEAD = 3 // индекс привязан к неиспользующемуся ("мертвому") блоку
} indexFlag;

/* Структура для индекса в ZGDB файле. */
typedef struct __attribute__((packed)) zgdbIndex {
    uint8_t flag; // флаги (т.е. мета-информация об индексе)
    int64_t offset; // смещение блока относительно начала файла
} zgdbIndex;

/* Функция для записи заголовка в файл.
 * Возвращает false при неудаче. */
bool writeHeader(zgdbFile* file);

/* Функция для записи новых (INDEX_NEW) индексов в файл.
 * ВНИМАНИЕ: После вызова, обязательно вызвать writeHeader, поскольку сама функция хедер файла не обновляет!
 * Возвращает false при неудаче. */
bool writeNewIndexes(zgdbFile* file, uint64_t count);

/* Функция для получения индекса по его порядковому номеру.
 * Возвращает индекс с флагом INDEX_NOT_EXIST при неудаче. */
zgdbIndex getIndex(zgdbFile* file, uint64_t i);

/* Функция, меняющая флаг и (или) offset в индексе по его порядковому номеру.
 * Возвращает false при неудаче. */
bool updateIndex(zgdbFile* file, uint64_t i, opt_uint8_t flag, opt_int64_t offset);

/* Функция, перемещающая данные с одного место в другое с использованием буфера. При этом oldPos и newPos обновляются.
 * Максимальный размер буфера - ZGDB_BUF_SIZE.
 * Возвращает false при неудаче. */
bool moveData(zgdbFile* file, int64_t* oldPos, int64_t* newPos, uint64_t size);

/* Функция для перемещения документов, идущих в файле сразу после индексов, в новое место (в конец файла или дырку).
 * Продлевает массив индексов, используя освобождённое место. Если освободившееся место не делится нацело на размер
 * индекса, то остаток сохраняется в заголовке файла в firstDocumentOffset.
 * Возвращает false при неудаче. */
bool moveFirstDocuments(zgdbFile* file);

#endif