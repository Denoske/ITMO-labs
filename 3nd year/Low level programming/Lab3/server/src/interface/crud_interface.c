#include "../../include/interface/crud_interface.h"

enum crud_operation_status add_tuple(FILE *file, uint64_t *fields, uint64_t parent_id) {
    uint32_t *types;
    size_t size;
    get_types(file, &types, &size);
    struct tree_header *header = malloc(sizeof(struct tree_header));
    read_tree_header(header, file);

    struct tuple *new_tuple = malloc(sizeof(struct tuple));
    union tuple_header new_tuple_header = {.parent = parent_id, .alloc = header->subheader->cur_id};

    new_tuple->header = new_tuple_header;
    new_tuple->data = malloc(get_real_tuple_size(size));
    uint64_t link;

    for (size_t iter = 0; iter < size; iter++) {
        if (types[iter] == STRING_TYPE) {
            insert_string_tuple(file, fields[iter], get_real_tuple_size(size), &link);
            new_tuple->data[iter] = link;
        } else {
            new_tuple->data[iter] = (uint64_t) fields[iter];
        }
    }


    size_t full_tuple_size = sizeof(union tuple_header) + get_real_tuple_size(size);

    enum crud_operation_status status = insert_new_tuple(file, new_tuple, full_tuple_size, &link);


    link_strings_to_tuple(file, new_tuple, link);

    size_t id = append_to_id_array(file, link);


    free_test_tuple(new_tuple);
    free(types);
    free_test_tree_header(header);

    return status;
}

enum crud_operation_status get_tuple(FILE *file, struct tuple **tuple, uint64_t id) {
    uint64_t offset;
    id_to_offset(file, id, &offset);
    if (offset == NULL_VALUE) return CRUD_INVALID;
    uint32_t *types;
    size_t size;
    get_types(file, &types, &size);
    fseek(file, offset, SEEK_SET);
    read_basic_tuple(file, tuple, (uint64_t) size);

    return CRUD_OK;
}

enum crud_operation_status remove_tuple(FILE *file, uint64_t id, uint8_t str_flag) {

    uint32_t *types;
    size_t size;
    get_types(file, &types, &size);
    //    printf("%lu\n", id);

    if (!str_flag) {
        uint64_t offset;
        if (remove_from_id_array(file, id, &offset) == CRUD_INVALID) {
            // invalid id
            return CRUD_INVALID;
        }

        for (size_t field_num = 0; field_num < size; field_num++) {
            if (types[field_num] == STRING_TYPE) {
                struct tuple *tpl;
                fseek(file, (long) offset, SEEK_SET);
                read_basic_tuple(file, &tpl, size);
                remove_tuple(file, tpl->data[field_num], 1);
                free(tpl->data);
                free(tpl);
            }
        }

        swap_last_tuple_to(file, offset, get_real_tuple_size(size));

        struct result_list_tuple *children = NULL;
        find_by_parent(file, id, &children);
        while (children != NULL) {
            remove_tuple(file, children->id, 0);
            children = children->prev;
        }

    } else {
        struct tuple *str_tpl;
        while (id != NULL_VALUE) {
            //            struct tree_header* header1 = malloc(sizeof(struct tree_header));
            //            read_tree_header(header1, file);
            //            printf("--- SUBHEADER ---\n");
            //            printf("%-20s%ld\n", "ASCII Signature: ", header1->subheader->ASCII_signature);
            fseek(file, id, SEEK_SET);
            read_string_tuple(file, &str_tpl, size);


            swap_last_tuple_to(file, id, get_real_tuple_size(size) + sizeof(union tuple_header));


            id = str_tpl->header.next;
            free(str_tpl->data);
            free(str_tpl);
            struct tree_header *header = malloc(sizeof(struct tree_header));
            read_tree_header(header, file);
            //            printf("%-20s%ld\n", "ASCII Signature: ", header->subheader->ASCII_signature);
        }
    }

    free(types);
    return CRUD_OK;
}

enum crud_operation_status swap_last_tuple_to(FILE *file, uint64_t pos_to, size_t tuple_size) {

    //    struct tree_header* header = malloc(sizeof(struct tree_header));
    //    read_tree_header(header, file);
    //    printf("--- SUBHEADER ---\n");
    //    printf("%-20s%ld\n", "ASCII Signature: ", header->subheader->ASCII_signature);

    uint32_t *types;
    size_t size;
    get_types(file, &types, &size);

    fseek(file, (long) -(get_real_tuple_size(size) + sizeof(union tuple_header)), SEEK_END);
    uint64_t pos_from = ftell(file);

    free(types);

    enum crud_operation_status status = swap_tuple_to(file, pos_to, pos_from, tuple_size);
    //
    //    read_tree_header(header, file);
    //    printf("%-20s%ld\n", "ASCII Signature: ", header->subheader->ASCII_signature);

    ftruncate(fileno(file), (long) pos_from);

    //    read_tree_header(header, file);
    //    printf("%-20s%ld\n", "ASCII Signature: ", header->subheader->ASCII_signature);

    return status;
}

static void append_to_result_list(struct tuple **tuple_to_add, uint64_t id, struct result_list_tuple **result) {
    if ((*result) == NULL) {
        *result = malloc(sizeof(struct result_list_tuple));
        (*result)->prev = NULL;
    } else {
        struct result_list_tuple *new_result = malloc(sizeof(struct result_list_tuple));
        new_result->prev = *result;
        *result = new_result;
    }
    (*result)->value = *tuple_to_add;
    (*result)->id = id;
    *tuple_to_add = malloc(sizeof(struct tuple));
}

enum crud_operation_status
find_by_field(FILE *file, uint64_t field_number, uint64_t *condition, struct result_list_tuple **result) {
    uint32_t *types;
    size_t size;
    get_types(file, &types, &size);
    uint64_t type = types[field_number];
    struct tree_header *header = malloc(sizeof(struct tree_header));
    size_t pos;
    read_tree_header(header, file);
    struct tuple *cur_tuple = malloc(sizeof(struct tuple));
    for (size_t i = 0; i < header->subheader->cur_id; i++) {
        if (header->id_sequence[i] == NULL_VALUE) continue;
        fseek(file, header->id_sequence[i], SEEK_SET);
        read_basic_tuple(file, &cur_tuple, size);
        if (type == STRING_TYPE) {
            char *s;
            read_string_from_tuple(file, &s, size, cur_tuple->data[field_number]);
            if (!strcmp(s, (char *) condition)) {
                append_to_result_list(&cur_tuple, i, result);
            }
        } else {
            if (cur_tuple->data[field_number] == *condition) {
                append_to_result_list(&cur_tuple, i, result);
            }
        }

    }
    return 0;
}

enum crud_operation_status find_by_parent(FILE *file, uint64_t parent_id, struct result_list_tuple **result) {
    struct tree_header *header = malloc(sizeof(struct tree_header));
    size_t pos;
    read_tree_header(header, file);
    struct tuple *cur_tuple = malloc(sizeof(struct tuple));
    for (size_t i = 0; i < header->subheader->cur_id; i++) {
        if (header->id_sequence[i] == NULL_VALUE) continue;
        fseek(file, header->id_sequence[i], SEEK_SET);
        read_basic_tuple(file, &cur_tuple, header->subheader->pattern_size);
        if (cur_tuple->header.parent == parent_id) {
            append_to_result_list(&cur_tuple, i, result);
        }

    }
    return 0;
}

enum crud_operation_status update_tuple(FILE *file, uint64_t field_number, uint64_t *new_value, uint64_t id) {
    uint32_t *types;
    size_t size;
    get_types(file, &types, &size);
    uint64_t type = types[field_number];
    uint64_t offset;
    id_to_offset(file, id, &offset);
    struct tuple *cur_tuple;
    fseek(file, offset, SEEK_SET);
    read_basic_tuple(file, &cur_tuple, size);

    if (type == STRING_TYPE) {
        char buffer[20];
        sprintf(buffer, "%d", new_value);
        change_string_tuple(file, cur_tuple->data[field_number], (char *) buffer, get_real_tuple_size(size));
    } else {
        memcpy(&(cur_tuple->data[field_number]), new_value, sizeof(*new_value));
        fseek(file, offset, SEEK_SET);
        write_tuple(file, cur_tuple, get_real_tuple_size(size));
    }
    //free(cur_tuple->data);
    //free(cur_tuple);
    free(types);
    return 0;
}