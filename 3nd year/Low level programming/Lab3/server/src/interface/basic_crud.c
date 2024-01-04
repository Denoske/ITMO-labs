#include "../../include/interface/basic_crud.h"

enum crud_operation_status delete_last_tuple(FILE* file, size_t full_tuple_size) {
    fseek(file, full_tuple_size, SEEK_END);
    int fd = fileno(file);
    return ftruncate(fd, ftell(file));
}

enum crud_operation_status swap_tuple_to(FILE* file, uint64_t pos_to, uint64_t pos_from, size_t tuple_size) {
    uint32_t* types;
    size_t size;
    get_types(file, &types, &size);

    //    struct tree_header* header = malloc(sizeof(struct tree_header));
    //    read_tree_header(header, file);
    //    printf("--- SUBHEADER ---\n");
    //    printf("%-20s%ld\n", "ASCII Signature: ", header->subheader->ASCII_signature);

    if (pos_from != pos_to) {
        fseek(file, pos_from, SEEK_SET);
        void* buffer = malloc(tuple_size);
        read_from_file(file, buffer, tuple_size);


        fseek(file, pos_to, SEEK_SET);
        write_to_file(file, buffer, tuple_size);
        free(buffer);

        fseek(file, 0, SEEK_SET);
        struct tree_header* header = malloc(sizeof(struct tree_header));
        read_tree_header(header, file);
        uint64_t id;
        struct tuple* tpl;

        enum crud_operation_status st = offset_to_id(file, &id, pos_from);

        if (st == CRUD_INVALID) {

            fseek(file, pos_from, SEEK_SET);
            read_string_tuple(file, &tpl, size);
            union tuple_header* temp_header = malloc(sizeof(union tuple_header));

            //            if (tpl->header.next != 0) {
            //                fseek(file, tpl->header.next, SEEK_SET);
            //                read_from_file(file, temp_header, sizeof(union tuple_header));
            //                temp_header->prev = pos_to;
            //                fseek(file, tpl->header.next, SEEK_SET);
            //
            //                printf("%lu\n", ftell(file));
            //
            //                write_to_file(file, temp_header, sizeof(union tuple_header));
            //            }

            fseek(file, tpl->header.prev, SEEK_SET);
            read_from_file(file, temp_header, sizeof(union tuple_header));

            if (temp_header->next == pos_from) {
                temp_header->next = pos_to;
                fseek(file, tpl->header.prev, SEEK_SET);
                write_to_file(file, temp_header, sizeof(union tuple_header));
            }
            else {


                struct tuple* parent;
                fseek(file, tpl->header.prev, SEEK_SET);
                read_basic_tuple(file, &parent, size);
                for (size_t iter = 0; iter < size; iter++) {
                    if (types[iter] == STRING_TYPE && parent->data[iter] == pos_from) {
                        parent->data[iter] = pos_to;
                        break;
                    }
                }

                fseek(file, (tpl->header.prev), SEEK_SET);
                write_tuple(file, parent, get_real_tuple_size(size));
                //                free(parent->data);
                //                free(parent);
            }
            free(temp_header);
        }
        else {
            fseek(file, pos_from, SEEK_SET);
            read_basic_tuple(file, &tpl, size);
            link_strings_to_tuple(file, tpl, pos_to);
            header->id_sequence[id] = pos_to;
            write_tree_header(file, header);
        }

        free(tpl->data);
        free(tpl);
        free_test_tree_header(header);

    }

    free(types);
    return CRUD_OK;
}

enum crud_operation_status
    insert_new_tuple(FILE* file, struct tuple* tuple, size_t full_tuple_size, uint64_t* tuple_pos) {
    fseek(file, 0, SEEK_END);
    *tuple_pos = ftell(file);
    int fd = fileno(file);
    ftruncate(fd, ftell(file) + full_tuple_size);
    enum file_write_status status = write_tuple(file, tuple, full_tuple_size - sizeof(union tuple_header));
    return status == WRITE_OK ? CRUD_OK : CRUD_INVALID;
}


enum crud_operation_status insert_string_tuple(FILE* file, char* string, size_t tuple_size, uint64_t* str_pos) {
    size_t len = 20; //strlen(string);
    size_t count = len / tuple_size + (len % tuple_size ? 1 : 0);
    struct tuple* temp_tuple = malloc(sizeof(struct tuple));
    char* temp_tuple_content = string;
    size_t pos = (size_t)ftell(file);
    uint64_t fake_pos;
    fseek(file, 0, SEEK_END);
    *str_pos = ftell(file);
    for (size_t iter = 0; count > iter; iter++) {
        if (count - 1 == iter) {
            temp_tuple->header.next = 0;
        }
        else {
            temp_tuple->header.next = pos + (tuple_size + sizeof(union tuple_header)) * (iter + 1);
        }
        if (0 == iter) {
            temp_tuple->header.prev = 0;
        }
        else {
            temp_tuple->header.prev = pos + (tuple_size + sizeof(union tuple_header)) * (iter - 1);
        }
        temp_tuple->data = (uint64_t*)(temp_tuple_content + tuple_size * iter);
        insert_new_tuple(file, temp_tuple, tuple_size + sizeof(union tuple_header), &fake_pos);
    }
    free(temp_tuple);
    return 0;
}

void get_types(FILE* file, uint32_t** types, size_t* size) {
    fseek(file, 0, SEEK_SET);
    struct tree_header* header = malloc(sizeof(struct tree_header));
    read_tree_header(header, file);
    uint32_t* temp_types = malloc(header->subheader->pattern_size * sizeof(uint32_t));
    for (size_t iter = 0; iter < header->subheader->pattern_size; iter++) {
        temp_types[iter] = header->pattern[iter]->header->type;
    }
    *types = temp_types;
    *size = header->subheader->pattern_size;
    free_test_tree_header(header);
}

enum crud_operation_status change_parameter(FILE* file, enum tree_subheader_parameter parameter, uint64_t value) {
    fseek(file, 0, SEEK_SET);
    struct tree_header* header = malloc(sizeof(struct tree_header));
    size_t pos;
    read_tree_header(header, file);
    switch (parameter) {
    case PAR_CURRENT_ID:
        header->subheader->cur_id = value;
        break;
    case PAR_FIRST_SEQ:
        header->subheader->first_seq = value;
        break;
    case PAR_SECOND_SEQ:
        header->subheader->second_seq = value;
        break;
    case PAR_ROOT_OFFSET:
        header->subheader->root_offset = value;
        break;
    default:
        break;
    }
    write_tree_header(file, header);
    free(header);
    return 0;
}

size_t append_to_id_array(FILE* file, uint64_t offset) {

    size_t id;
    struct tree_header* header = malloc(sizeof(struct tree_header));
    read_tree_header(header, file);
    uint64_t from = ftell(file);
    uint64_t real_tuple_size = get_id_array_size(header->subheader->pattern_size, header->subheader->cur_id);

    //    if (!((header->subheader->cur_id + 1) % real_tuple_size)){
    //        fseek(file, 0, SEEK_END);
    //        uint64_t cur_end = ftell(file);
    //        ftruncate(fileno(file), cur_end + get_real_tuple_size(header->subheader->pattern_size) + sizeof(union tuple_header));
    //
    //        swap_tuple_to(file, cur_end, from, get_real_tuple_size(header->subheader->pattern_size));
    //
    //
    //
    //        free_test_tree_header(header);
    //        header = malloc(sizeof(struct tree_header));
    //        read_tree_header(header, file);
    //    }


    header->id_sequence[header->subheader->cur_id] = offset;
    header->subheader->cur_id++;
    id = header->subheader->cur_id - 1;

    fseek(file, 0, SEEK_SET);
    if (write_tree_header(file, header) != WRITE_OK) {
        printf("WRITE ERROR\n");
    }

    free_test_tree_header(header);

    return id;
}

enum crud_operation_status remove_from_id_array(FILE* file, uint64_t id, uint64_t* offset) {
    fseek(file, 0, SEEK_SET);
    struct tree_header* header = malloc(sizeof(struct tree_header));
    size_t pos;
    read_tree_header(header, file);
    if (header->id_sequence[id] == 0)
        return CRUD_INVALID;
    else {
        *offset = header->id_sequence[id];
        if (header->subheader->cur_id - 1 == id) {
            header->subheader->cur_id--;
        }
        header->id_sequence[id] = 0;
        write_tree_header(file, header);
        free(header);
        return CRUD_OK;
    }

}

enum crud_operation_status id_to_offset(FILE* file, uint64_t id, uint64_t* offset) {
    fseek(file, 0, SEEK_SET);
    struct tree_header* header = malloc(sizeof(struct tree_header));
    size_t pos;
    read_tree_header(header, file);
    *offset = header->id_sequence[id];
    return CRUD_OK;
}

enum crud_operation_status offset_to_id(FILE* file, uint64_t* id, uint64_t offset) {

    struct tree_header* header = malloc(sizeof(struct tree_header));
    read_tree_header(header, file);

    struct tuple* tpl;
    fseek(file, offset, SEEK_SET);
    read_basic_tuple(file, &tpl, header->subheader->pattern_size);

    if (header->id_sequence[tpl->header.alloc] == offset) {
        *id = tpl->header.alloc;
        free_test_tree_header(header);
        free(tpl->data);
        free(tpl);
        return CRUD_OK;
    }
    else {
        free_test_tree_header(header);
        free(tpl->data);
        free(tpl);
        return CRUD_INVALID;
    }

}

enum crud_operation_status change_string_tuple(FILE* file, uint64_t offset, char* new_string, size_t size) {
    struct tuple* cur_tuple = malloc(sizeof(struct tuple));
    size_t len = strlen(new_string);
    uint64_t old_offset = offset;
    do {
        offset = old_offset;
        fseek(file, offset, SEEK_SET);
        read_basic_tuple(file, &cur_tuple, size);
        fseek(file, offset, SEEK_SET);
        cur_tuple->data = (uint64_t*)(new_string);
        new_string += size;
        write_tuple(file, cur_tuple, size);
        old_offset = cur_tuple->header.next;
        len -= size;
    } while (cur_tuple->header.next && len > 0);
    uint64_t fpos;
    if (len > 0) {
        insert_string_tuple(file, new_string, size, &fpos);
        cur_tuple->header.next = fpos;
        fseek(file, offset, SEEK_SET);
        write_tuple(file, cur_tuple, size);
    }
    return CRUD_OK;
}

enum crud_operation_status link_strings_to_tuple(FILE* file, struct tuple* tpl, uint64_t tpl_offset) {
    uint32_t* types;
    size_t size;
    get_types(file, &types, &size);
    struct tuple* str;

    for (uint64_t iter = 0; iter < size; iter++) {
        if (types[iter] == STRING_TYPE) {
            fseek(file, tpl->data[iter], SEEK_SET);
            read_string_tuple(file, &str, size);
            str->header.prev = tpl_offset;
            fseek(file, tpl->data[iter], SEEK_SET);
            write_tuple(file, str, get_real_tuple_size(size));
            free_test_tuple(str);
        }
    }
    free(types);
    return CRUD_OK;
}