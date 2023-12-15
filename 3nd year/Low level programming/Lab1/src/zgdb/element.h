#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include "element_public.h"
#include "format.h"
#include "document.h"

/* Тип элемента (а точнее, тип значения элемента). */
typedef enum elementType {
    TYPE_NOT_EXIST = 0, // тип для несуществующего элемента
    TYPE_INT = 1, // для int32_t
    TYPE_DOUBLE = 2, // для double
    TYPE_BOOLEAN = 3, // для boolean (uint8_t)
    TYPE_STRING = 4, // для строки
} elementType;

/* Структура для строки. */
typedef struct str {
    uint32_t size; // размер строки с учётом терминатора ("Hello" -> 6)
    char* data; // данные
} str;

struct element {
    uint8_t type; // тип элемента
    char key[13]; // ключ элемента
    union {
        int32_t integerValue;
        double doubleValue;
        uint8_t booleanValue;
        str stringValue;
    };
    bool wasLoaded; // служебный флаг, чтобы понять, нужно ли вызывать free(stringValue.data) при освобождении памяти
};

/* Функция для создания элемента на куче. Проверяет ключ, выделяет место и копирует туда el.
 * Возвращает NULL при неудаче. */
element* createElement(const char* key, element el);

/* Функция для записи элемента в файл.
 * ВНИМАНИЕ: Предполагается, что к моменту вызова функции fseek уже сделан.
 * Возвращает количество записанных байт. */
uint64_t writeElement(zgdbFile* file, element* el);

/* Функция для чтения элемента из файла.
 * ВНИМАНИЕ: Предполагается, что к моменту вызова функции fseek уже сделан.
 * Если skipStrings == true, то пропускает строку (загружается только размер строки, но сама строка пропускается fseek).
 * Возвращает количество прочитанных байт. */
uint64_t readElement(zgdbFile* file, element* el, bool skipStrings);

/* Функция для обновления строки.
 * ВНИМАНИЕ: Если строка стала больше, вызывает перемещение документа!
 * ВНИМАНИЕ: Если строка стала меньше, содержимое документа перемещается так, чтобы "дырка" оказалась в его конце.
 * Возвращает false при неудаче. */
bool updateString(zgdbFile* file, zgdbIndex* index, documentHeader* header, element* oldEl, element* newEl);

#endif