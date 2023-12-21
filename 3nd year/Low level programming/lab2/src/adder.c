#include "adder.h"

struct element *add_int32_element(int32_t val) {
    struct element *el = test_malloc(sizeof(struct element));
    if (el == NULL) return NULL;
    el->num = val;
    el->element_type = 0;
    return el;
}

struct element *add_double_element(double val) {
    struct element *el = test_malloc(sizeof(struct element));
    if (el == NULL) return NULL;
    el->double_num = val;
    el->element_type = 1;
    return el;
}

struct element *add_str_element(char *val) {
    struct element *el = test_malloc(sizeof(struct element));
    if (el == NULL) return NULL;
    strcpy(el->string_val, val);
    el->element_type = 2;
    return el;
}

struct element *add_bool_element(int val) {
    struct element *el = test_malloc(sizeof(struct element));
    if (el == NULL) return NULL;
    if (val == 1) el->boolean = true;
    else el->boolean = false;
    el->element_type = 3;
    return el;
}

size_t size = 0;

void *test_malloc(size_t size_of){
    size += size_of;
    return malloc(size_of);
}

void *print_ram(){
    printf("%zu\n", size);
}
