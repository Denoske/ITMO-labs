#ifndef CRUD_INTERFACE_H
#define CRUD_INTERFACE_H

#include "basic_crud.h"

/**
 * ��������� �������� tuple
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
 * ���������� ������ tuple
 * @param file ����
 * @param fields ������ ����� �������� �������
 * @param parent_id ��� �������� ������� tuple
 * @return ������ ��������
 */
enum crud_operation_status add_tuple(FILE *file, uint64_t *fields, uint64_t parent_id);

/**
 * ������� tuple �� ��� id
 * @param file ����
 * @param id id tuple
 * @param str_flag 0 = default tuple, 1 = tuple contain string
 * @return ������ ��������
 */
enum crud_operation_status remove_tuple(FILE *file, uint64_t id, uint8_t str_flag);


/**
 * �������� ������� ��������� � ����������� tuple
 * @param file ����
 * @param pos_to ������ �����
 * @param tuple_size ������ ������� tuple
 * @return ������ ��������
 */
enum crud_operation_status swap_last_tuple_to(FILE *file, uint64_t pos_to, size_t tuple_size);

/**
 * �������� tuple �� id
 * @param file ����
 * @param fields ���������� ����
 * @param id id tuple
 * @return
 */
enum crud_operation_status get_tuple(FILE *file, struct tuple **tuple, uint64_t id);

/**
 *
 * @param file ����
 * @param field_number
 * @param condition
 * @param result
 * @return
 */
enum crud_operation_status
find_by_field(FILE *file, uint64_t field_number, uint64_t *condition, struct result_list_tuple **result);

enum crud_operation_status find_by_parent(FILE *file, uint64_t parent_id, struct result_list_tuple **result);

/**
 * �������� ���� �������� ���������
 * @param file ����
 * @param field_number ����� ���� ��������
 * @param new_value ����� ������ ��������
 * @param id tuple
 * @return
 */
enum crud_operation_status update_tuple(FILE *file, uint64_t field_number, uint64_t *new_value, uint64_t id);

#endif