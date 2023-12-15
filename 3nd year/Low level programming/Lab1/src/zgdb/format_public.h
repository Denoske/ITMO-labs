#ifndef _FORMAT_PUBLIC_H_
#define _FORMAT_PUBLIC_H_

/* Структура, представляющая открытый ZGDB файл в памяти. */
typedef struct zgdbFile zgdbFile;

/* Функция для загрузки существующего файла.
 * Возвращает NULL при неудаче. */
zgdbFile* loadFile(const char* filename);

/* Функция для создания нового файла.
 * Возвращает NULL при неудаче. */
zgdbFile* createFile(const char* filename);

/* Функция для закрытия файла. */
void closeFile(zgdbFile* file);

#endif