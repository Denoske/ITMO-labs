#ifndef LLP_2_ADDER_H
#define LLP_2_ADDER_H

#include "printer.h"


struct element *add_int32_element(int32_t val);

struct element *add_bool_element(int val);

struct element *add_str_element(char *val);

struct element *add_double_element(double val);

void *test_malloc(size_t size_of);

void *print_ram();

#endif //LLP_2_ADDER_H
