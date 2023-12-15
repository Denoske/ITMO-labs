#ifndef _DOCUMENT_PUBLIC_H_
#define _DOCUMENT_PUBLIC_H_

/* Максимальное возможное число индексов - (2^40-1), т.е. максимальный номер индекса - (2^40-2). Тогда можно использовать
 * число (2^40-1) в качестве специального номера индекса, обозначающего, что документ не существует: */
#define DOCUMENT_NOT_EXIST 0xFFFFFFFFFF

#include "format_public.h"
#include "schema_public.h"
#include "element_public.h"

/* Структура для загруженного в оперативную память документа. */
typedef struct document document;

/* Структура для уничтожения документа в оперативной памяти. С документом в файле ничего не делает! */
void destroyDocument(document* doc);

/* Функция для обычного вывода документа. Выводит поля и их значения. */
void printDocument(document* doc);

/* Функция для вывода документа как дерева. Выводит вложенные документы. */
void printDocumentAsTree(zgdbFile* file, document* doc);

/* Функция для получения элемента из документа по ключу.
 * Возвращает NULL при неудаче. */
element* getElementFromDocument(document* doc, const char* key);

/* Функция для получения схемы из документа.
 * Возвращает NULL при неудаче. */
documentSchema* getSchemaFromDocument(document* doc);

#endif