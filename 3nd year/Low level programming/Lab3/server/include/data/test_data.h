#ifndef LLP1_TEST_DATA_H
#define LLP1_TEST_DATA_H
#include "../interface/crud_interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <stdbool.h>
#include "../interface/configuration.h"
#include "../perf/wrapper.h"

void get_test_data(FILE* file, size_t tuple_count, size_t pattern_size, uint32_t* types);

void get_test_header(char*** pattern, uint32_t** types, size_t* pattern_size, size_t** sizes, size_t* tuple_count);

FILE* open_file();
//
//char* get_cur_line(FILE *df);

void init_header_param(char** cur_line, size_t* tuple_count, size_t* pattern_size);

void malloc_header_struct(const size_t* pattern_size, char*** pattern, uint32_t** types, size_t** sizes);

void check_input();

int get_string_count(size_t* pattern_size);

int get_type_from_string(char* str_type);

uint64_t get_real_tuple_attr(int type, char* attr);

int get_space_count(char* string);

uint64_t get_parent_id(char* string);

bool get_bool_attr(char* string);

#endif //LLP1_TEST_DATA_H