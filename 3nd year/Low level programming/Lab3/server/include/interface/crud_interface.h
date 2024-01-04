#ifndef CRUD_INTERFACE_H
#define CRUD_INTERFACE_H

#include "basic_crud.h"

/**
 * Структура хранящая tuple
 */
struct result_list_tuple {
    struct result_list_tuple *prev;
    struct tuple *value;
    uint64_t id;
};

//struct result_list_tuple_test {
//    struct tuple *value;
//    struct result_list_tuple *next;
//};

void print_result_list_tuple(struct result_list_tuple *result);

/**
 * Добавление нового tuple
 * @param file файл
 * @param fields массив полей согласно шаблону
 * @param parent_id кто родитель данного tuple
 * @return статус операции
 */
enum crud_operation_status add_tuple(FILE *file, uint64_t *fields, uint64_t parent_id);

/**
 * Удалить tuple по его id
 * @param file файл
 * @param id id tuple
 * @param str_flag 0 = default tuple, 1 = tuple contain string
 * @return статус операции
 */
enum crud_operation_status remove_tuple(FILE *file, uint64_t id, uint8_t str_flag);


/**
 * Поменять местами последний и запрошенный tuple
 * @param file файл
 * @param pos_to нужное место
 * @param tuple_size размер данного tuple
 * @return статус операции
 */
enum crud_operation_status swap_last_tuple_to(FILE *file, uint64_t pos_to, size_t tuple_size);

/**
 * Получить tuple по id
 * @param file файл
 * @param fields полученный поля
 * @param id id tuple
 * @return
 */
enum crud_operation_status get_tuple(FILE *file, struct tuple **tuple, uint64_t id);

/**
 *
 * @param file файл
 * @param field_number
 * @param condition
 * @param result
 * @return
 */
enum crud_operation_status
find_by_field(FILE *file, uint64_t field_number, uint64_t *condition, struct result_list_tuple **result);

enum crud_operation_status find_by_parent(FILE *file, uint64_t parent_id, struct result_list_tuple **result);

/**
 * Обновить одно значение параметра
 * @param file файл
 * @param field_number номер поля паттерна
 * @param new_value адрес нового значения
 * @param id tuple
 * @return
 */
enum crud_operation_status update_tuple(FILE *file, uint64_t field_number, uint64_t *new_value, uint64_t id);

#endif