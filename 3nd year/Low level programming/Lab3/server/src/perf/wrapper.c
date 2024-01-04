#include "../../include/perf/wrapper.h"

void time_add_wrapper(FILE* file, uint64_t* fields, uint64_t parent_id) {
    clock_t cl = clock();
    add_tuple(file, fields, parent_id);
    printf("%f\n", (double) (clock() - cl) / CLOCKS_PER_SEC);
}

void time_add_get_wrapper(FILE* file, uint64_t* fields, uint64_t parent_id, uint64_t id) {
    add_tuple(file, fields, parent_id);
    clock_t cl = clock();
    get_tuple(file, &fields, id);
    printf("%f\n", (double)(clock() - cl) / CLOCKS_PER_SEC);
}

void time_add_get_cond_wrapper(FILE* file, uint64_t* fields, uint64_t parent_id) {
    add_tuple(file, fields, parent_id);
    uint64_t c = 30;
    struct result_list_tuple* res;
    clock_t cl = clock();
    find_by_field(file, 1, &c, &res);
    printf("%f\n", (double)(clock() - cl) / CLOCKS_PER_SEC);
}

void time_add_update_wrapper(FILE* file, uint64_t* fields, uint64_t parent_id, uint64_t id) {
    add_tuple(file, fields, parent_id);
    uint64_t c = 1111;
    clock_t cl = clock();
    update_tuple(file, 1, &c, id);
    printf("%f\n", (double)(clock() - cl) / CLOCKS_PER_SEC);
}

void time_add_remove_wrapper(FILE* file, uint64_t* fields, uint64_t parent_id, uint64_t id) {
    add_tuple(file, fields, parent_id);
    clock_t cl = clock();
    remove_tuple(file, id, 0);
    printf("%f\n", (double)(clock() - cl) / CLOCKS_PER_SEC);
}

void time_add_get_by_parent_wrapper(FILE* file, uint64_t* fields, uint64_t parent_id) {
    add_tuple(file, fields, parent_id);
    struct result_list_tuple* list = NULL;
    clock_t cl = clock();
    find_by_parent(file, parent_id, &list);
    printf("%f\n", (double)(clock() - cl) / CLOCKS_PER_SEC);
    free_result_list(list);
}

void free_result_list(struct result_list_tuple* result) {
    if (result != NULL) {
        struct result_list_tuple* next;
        while (result != NULL) {
            next = result->prev;
            free(result->value->data);
            free(result->value);
            free(result);
            result = next;
        }
    }
}