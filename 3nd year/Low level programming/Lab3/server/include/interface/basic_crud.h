#ifndef BASIC_CRUD_H
#define BASIC_CRUD_H

#include "../filetools/big_data_tools.h"
#include <string.h>

/**
 * ������� ��������� ������ �� �����
 * @param file ����
 * @param full_tuple_size ������ ������ ������� ������ � ����������
 * @return ������ ��������
 */
enum crud_operation_status delete_last_tuple(FILE* file, size_t full_tuple_size);

/**
 * ��������� �� ������� ������
 * @param file ����
 * @param pos_from ������ �����������
 * @param pos_to ���� �����������
 * @return ������ ��������
 */
enum crud_operation_status swap_tuple_to(FILE* file, uint64_t pos_from, uint64_t pos_to, size_t tuple_size);

/**
 * ��������� � ����� ����� ����� ������
 * @param file ����
 * @param tuple ������
 * @param full_tuple_size ������ ������ ������� ������ � ����������
 * @return ������ ��������
 */
enum crud_operation_status insert_new_tuple(FILE* file, struct tuple* tuple, size_t full_tuple_size, uint64_t* tuple_pos);

/**
 * ��������� � ����� ����� ����� ������ ������
 * @param file ����
 * @param string ������
 * @param str_pos
 * @return ������ ��������
 */
enum crud_operation_status insert_string_tuple(FILE* file, char* string, size_t tuple_size, uint64_t* str_pos);

/**
 * ���������� � ��������� ������� ���� ��������
 * @param file ����
 * @param types ��������� ��� �������� �����
 * @param size ������ ���������� �����
 */
void get_types(FILE* file, uint32_t** types, size_t* size);

/**
 * �������� � tree_header �����-�� ��������
 * @param file ����
 * @param parameter ���������� ��������
 * @param value ����� ��������
 * @return
 */
enum crud_operation_status change_parameter(FILE* file, enum tree_subheader_parameter parameter, uint64_t value);

/**
 * ���������� ����� ������ � id_sequence
 * @param file ����
 * @param offset �������� �� ��������� id link
 * @return
 */
size_t append_to_id_array(FILE* file, uint64_t offset);

/**
 * �������� ������ � id_sequence[id] � ��������� �������� �� 0
 * @param file ����
 * @param id link ������� ����� �������
 * @param offset
 * @return
 */
enum crud_operation_status remove_from_id_array(FILE* file, uint64_t id, uint64_t* offset);

/**
 * ����� �������������� tuple �� ��� id � id_sequence
 * @param file ����
 * @param id ������� tuple
 * @param offset ���������
 * @return
 */
enum crud_operation_status id_to_offset(FILE* file, uint64_t id, uint64_t* offset);

/**
 * �������� id � id_sequence �� ��� ��������
 * @param file ����
 * @param id ���������
 * @param offset ������ �������� �� tuple
 * @return
 */
enum crud_operation_status offset_to_id(FILE* file, uint64_t* id, uint64_t offset);


/**
 * ������ ������������ ������
 * @param file ����
 * @param offset
 * @param new_string ����� ������
 * @param size ������ ����� ������
 * @return
 */
enum crud_operation_status change_string_tuple(FILE* file, uint64_t offset, char* new_string, size_t size);

enum crud_operation_status link_strings_to_tuple(FILE* file, struct tuple* tpl, uint64_t tpl_offset);


/**
 * ������ ��������
 */
enum crud_operation_status {
    CRUD_OK = 0,
    CRUD_END_OF_FILE,
    CRUD_INVALID
};

#endif