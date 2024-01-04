#ifndef BASIC_FILE_MANAGER_H
#define BASIC_FILE_MANAGER_H

#include <stdio.h>
#include <inttypes.h>

/**
 * Прочитать данные из файла
 * @param buffer контейнер, который надо заполнить из файла
 * @param file файл для чтения
 * @return статус чтения
 */
enum file_read_status read_from_file(FILE* file, void* buffer, size_t size);

/**
 * Записать данные в файл
 * @param buffer контейнер, который надо записать в файл
 * @param file файл для записи
 * @return статус записи
 */
enum file_write_status write_to_file(FILE* file, char* buffer, size_t size);

/**
 * Открытие файла
 * @param filename название файла
 * @param file контейнер в который будет записан файловый поток
 * @return статус открытия
 */
enum file_open_status open_exist_file(char* filename, FILE** file);

/**
 * Создание файла
 * @param filename название файла
 * @param file контейнер в который будет записан файловый поток
 * @return статус открытия
 */
enum file_open_status open_new_file(char* filename, FILE** file);

enum file_open_status open_file_anyway(FILE** file, char* filename);

/**
 * Закрытие файла
 * @param file файловый поток
 */

enum file_open_status open_empty_file(char* filename, FILE** file);
void close_file(FILE* file);

/**
 * Статус чтения файла
 */
enum file_read_status {
    READ_OK = 0,
    READ_END_OF_FILE,
    READ_INVALID
};

/**
 * Статус записи в файл
 */
enum file_write_status {
    WRITE_OK = 0,
    WRITE_WRONG_INTEGRITY,
    WRITE_INVALID
};

/**
 * Статус открытия файла
 */
enum file_open_status {
    OPEN_OK = 0,
    OPEN_FAILED
};

#endif