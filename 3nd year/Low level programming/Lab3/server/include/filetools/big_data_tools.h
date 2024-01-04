#ifndef BIG_DATA_TOOLS_H
#define BIG_DATA_TOOLS_H
#include <stdlib.h>

#include "../interface/configuration.h"
#include "../interface/signatures.h"
#include "../generator/empty_generator.h"
#include "basic_file_manager.h"

/**
 * ��������� ��������� ������� ������� ������
 * @param pattern_size ������ ������� �������
 * @return ������ ���������� ������ �������
 */
size_t get_real_id_array_size(uint64_t pattern_size, uint64_t cur_id);

/**
 * ��������� ��������� ������� �������
 * @param pattern_size ������ ������� �������
 * @return ������ ���������� ������ �������
 */
size_t get_real_tuple_size(uint64_t pattern_size);

size_t get_id_array_size(uint64_t pattern_size, uint64_t cur_id);

/**
 * ��������� ������� ������
 * @param tuple ��������� ��� �������
 * @param file ����
 * @param tree_header ���������
 * @return ������ ������
 */


 /**
  * ��������� �������� ������
  * @param tuple ��������� ��� �������
  * @param file ����
  * @param tree_header ��������� ������
  * @return ������ ������
  */
enum file_read_status read_string_tuple(FILE* file, struct tuple** tuple, uint64_t pattern_size);

/**
 * �������� ������
 * @param string ��������� ��� ������
 * @param pattern_size ������ �������, � ������ �������� ������
 * @param offset ��������, ��� ��������� ������ ������
 * @return ������ ������
 */
enum file_read_status read_string_from_tuple(FILE* file, char** string, uint64_t pattern_size, uint64_t offset);

/**
 * �������� ��������� �����
 * @param file ����
 * @param header ��������� �����
 * @param pattern_size ������ ������� �������
 * @return ������ ������
 */
enum file_write_status write_tree_header(FILE* file, struct tree_header* header);

/**
 * ������� ���� � ������ ����������
 * @param file ����
 * @param pattern ������ ����� ��� �������
 * @param types ���� ����� �������
 * @param pattern_size ������ ������� �������
 * @param key_sizes ������� ����� �������
 * @return ������ ������
 */
enum file_write_status init_empty_file(FILE* file, char** pattern, uint32_t* types, size_t pattern_size, size_t* key_sizes);

/**
 * �������� ����� ��� ��� �������� � ������ ��� ����������
 * @param file ��������� ��� ��������� ������
 * @param filename ��� �����
 * @return ������ ��������
 */
enum file_open_status open_file_anyway(FILE** file, char* filename);

/**
 * ������ ������� � ����
 * @param file ����
 * @param tuple ������
 * @return ������ ������
 */
enum file_write_status write_tuple(FILE* file, struct tuple* tuple, size_t tuple_size);

enum file_read_status read_basic_tuple(FILE* file, struct tuple** tuple, uint64_t pattern_size);

static enum file_write_status write_pattern(FILE* file, struct key** pattern, size_t pattern_size);

void print_tree_header_from_file(FILE* file);
void print_tuple_array_from_file(FILE* file);

void free_test_tree_header(struct tree_header* header);

void free_test_tuple(struct tuple* tuple);

void* malloc_test(size_t size);

void free_test(void* ptr);

void print_ram();

enum file_read_status read_tree_header(struct tree_header* header, FILE* file);

#endif