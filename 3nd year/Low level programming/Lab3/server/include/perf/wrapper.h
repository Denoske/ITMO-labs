#ifndef LLP1_WRAPPER_H
#define LLP1_WRAPPER_H

#include <stdio.h>
#include <inttypes.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include "time.h"
#include "../interface/crud_interface.h"

void time_add_wrapper(FILE* file, uint64_t* fields, uint64_t parent_id);

void time_add_get_wrapper(FILE* file, uint64_t* fields, uint64_t parent_id, uint64_t id);

void time_add_get_cond_wrapper(FILE* file, uint64_t* fields, uint64_t parent_id);

void time_add_update_wrapper(FILE* file, uint64_t* fields, uint64_t parent_id, uint64_t id);

void time_add_remove_wrapper(FILE* file, uint64_t* fields, uint64_t parent_id, uint64_t id);

void time_add_get_by_parent_wrapper(FILE* file, uint64_t* fields, uint64_t parent_id);

void free_result_list(struct result_list_tuple* result);

#endif //LLP1_WRAPPER_H