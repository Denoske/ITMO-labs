#ifndef BASIC_CRUD_H
#define BASIC_CRUD_H

#include "../filetools/big_data_tools.h"
#include <string.h>

/**
 * Удаляет последний кортеж их файла
 * @param file файл
 * @param full_tuple_size размер одного кортежа вместе с заголовком
 * @return статус операции
 */
enum crud_operation_status delete_last_tuple(FILE* file, size_t full_tuple_size);

/**
 * Вставляет на позицию кортеж
 * @param file файл
 * @param pos_from откуда скопировать
 * @param pos_to куда скопировать
 * @return статус операции
 */
enum crud_operation_status swap_tuple_to(FILE* file, uint64_t pos_from, uint64_t pos_to, size_t tuple_size);

/**
 * Вставляет в конец файла новый кортеж
 * @param file файл
 * @param tuple кортеж
 * @param full_tuple_size размер одного кортежа вместе с заголовком
 * @return статус операции
 */
enum crud_operation_status insert_new_tuple(FILE* file, struct tuple* tuple, size_t full_tuple_size, uint64_t* tuple_pos);

/**
 * Вставляет в конец файла новый кортеж строки
 * @param file файл
 * @param string строка
 * @param str_pos
 * @return статус операции
 */
enum crud_operation_status insert_string_tuple(FILE* file, char* string, size_t tuple_size, uint64_t* str_pos);

/**
 * Записывает в контейнер текущие типы паттерна
 * @param file файл
 * @param types контейнер для упаковки типов
 * @param size размер полученных типов
 */
void get_types(FILE* file, uint32_t** types, size_t* size);

/**
 * Заменить в tree_header какой-то параметр
 * @param file файл
 * @param parameter изменяемый параметр
 * @param value новое значение
 * @return
 */
enum crud_operation_status change_parameter(FILE* file, enum tree_subheader_parameter parameter, uint64_t value);

/**
 * Добавление новой ссылки в id_sequence
 * @param file файл
 * @param offset смещение на последний id link
 * @return
 */
size_t append_to_id_array(FILE* file, uint64_t offset);

/**
 * Заменяет ссылку в id_sequence[id] с реального значения но 0
 * @param file файл
 * @param id link которую нужно удалить
 * @param offset
 * @return
 */
enum crud_operation_status remove_from_id_array(FILE* file, uint64_t id, uint64_t* offset);

/**
 * Узаем местоположение tuple по его id в id_sequence
 * @param file файл
 * @param id нужного tuple
 * @param offset результат
 * @return
 */
enum crud_operation_status id_to_offset(FILE* file, uint64_t id, uint64_t* offset);

/**
 * Получаем id в id_sequence по его значению
 * @param file файл
 * @param id результат
 * @param offset нужное смещение на tuple
 * @return
 */
enum crud_operation_status offset_to_id(FILE* file, uint64_t* id, uint64_t offset);


/**
 * Замена существующей строки
 * @param file файл
 * @param offset
 * @param new_string новая строка
 * @param size размер новой строки
 * @return
 */
enum crud_operation_status change_string_tuple(FILE* file, uint64_t offset, char* new_string, size_t size);

enum crud_operation_status link_strings_to_tuple(FILE* file, struct tuple* tpl, uint64_t tpl_offset);


/**
 * Статус операции
 */
enum crud_operation_status {
    CRUD_OK = 0,
    CRUD_END_OF_FILE,
    CRUD_INVALID
};

#endif