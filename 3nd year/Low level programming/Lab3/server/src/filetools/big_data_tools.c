#include "../../include/filetools/big_data_tools.h"
#include "../../include/interface/basic_crud.h"
#include "../../include/interface/crud_interface.h"

size_t get_real_tuple_size(uint64_t pattern_size) {
    return pattern_size * SINGLE_TUPLE_VALUE_SIZE < MINIMAL_TUPLE_SIZE
        ? MINIMAL_TUPLE_SIZE
        : pattern_size * SINGLE_TUPLE_VALUE_SIZE;
}

static uint64_t max_custom(uint64_t n1, uint64_t n2) {
    if (n1 > n2) return n1;
    return n2;
}

size_t get_id_array_size(uint64_t pattern_size, uint64_t cur_id) {
    size_t real_tuple_size = get_real_tuple_size(pattern_size) + sizeof(union tuple_header);
    if (cur_id == 0) cur_id++;
    size_t whole = (cur_id * OFFSET_VALUE_SIZE / real_tuple_size);
    size_t frac = (cur_id * OFFSET_VALUE_SIZE % real_tuple_size ? 1 : 0);
    size_t value = max_custom((frac + whole) * real_tuple_size / OFFSET_VALUE_SIZE, MIN_ID_ARRAY_SIZE * real_tuple_size / OFFSET_VALUE_SIZE);
    //    printf("%zu %zu %zu %zu %zu %zu\n", pattern_size, cur_id, real_tuple_size, whole, frac, value);
    return value;
}

static enum file_read_status read_tree_subheader(struct tree_subheader* header, FILE* file) {
    enum file_read_status code = read_from_file(file, header, sizeof(struct tree_subheader));
    return code;
}

/**
 * Чтение текущего паттерна
 * @param key структура паттерна куда будет записан паттерн
 * @param file название файла
 * @return статус записи
 */
static enum file_read_status read_key(struct key* key, FILE* file) {
    struct key_header* header = malloc(sizeof(struct key_header));
    enum file_read_status code = read_from_file(file, header, sizeof(struct key_header));
    key->header = header;

    char* key_value = (char*)malloc(
        header->size / FILE_GRANULARITY + (header->size % FILE_GRANULARITY ? FILE_GRANULARITY : 0));
    code |= read_from_file(file, key_value, header->size);
    key->key_value = key_value;

    return code;
}

enum file_read_status read_tree_header(struct tree_header* header, FILE* file) {
    fseek(file, 0, SEEK_SET);
    struct tree_subheader* subheader = malloc(sizeof(struct tree_subheader));
    enum file_read_status code = read_tree_subheader(subheader, file);
    header->subheader = subheader;
    struct key** array_of_key = malloc(sizeof(struct key*) * subheader->pattern_size);
    header->pattern = array_of_key;
    for (size_t iter = subheader->pattern_size; iter-- > 0; array_of_key++) {
        struct key* element_pattern = malloc(sizeof(struct key));
        code |= read_key(element_pattern, file);
        *array_of_key = element_pattern;
        //free(element_pattern);
    }

    size_t real_id_array_size = get_id_array_size(header->subheader->pattern_size, header->subheader->cur_id);
    uint64_t* id_array = (uint64_t*)malloc(real_id_array_size * sizeof(uint64_t));
    header->id_sequence = id_array;
    code |= read_from_file(file, id_array, real_id_array_size * sizeof(uint64_t));
    return code;
}

enum file_read_status read_basic_tuple(FILE* file, struct tuple** tuple, uint64_t pattern_size) {
    union tuple_header* header = malloc(sizeof(union tuple_header));
    enum file_read_status code = read_from_file(file, header, sizeof(union tuple_header));
    struct tuple* temp_tuple = malloc(sizeof(struct tuple));
    temp_tuple->header = *header;
    free(header);

    uint64_t* data = malloc(get_real_tuple_size(pattern_size));
    code |= read_from_file(file, data, get_real_tuple_size(pattern_size));
    temp_tuple->data = data;

    *tuple = temp_tuple;

    return code;
}

enum file_read_status read_string_tuple(FILE* file, struct tuple** tuple, uint64_t pattern_size) {
    union tuple_header* header = malloc(sizeof(union tuple_header));
    enum file_read_status code = read_from_file(file, header, sizeof(union tuple_header));
    struct tuple* temp_tuple = malloc(sizeof(struct tuple));
    temp_tuple->header = *header;
    free(header);

    uint64_t* data = (uint64_t*)malloc(get_real_tuple_size(pattern_size));
    code |= read_from_file(file, data, get_real_tuple_size(pattern_size));
    temp_tuple->data = data;

    *tuple = temp_tuple;

    return code;
}

static size_t how_long_string_is(FILE* file, uint64_t offset) {
    fseek(file, offset, SEEK_SET);
    size_t len = 1;
    union tuple_header* temp_header = malloc(sizeof(union tuple_header));
    read_from_file(file, temp_header, sizeof(union tuple_header));
    //    printf("'%lu %lu %lu'\n", offset, temp_header->next, temp_header->prev);
    while (temp_header->next) {
        fseek(file, temp_header->next, SEEK_SET);
        read_from_file(file, temp_header, sizeof(union tuple_header));
        len++;
    }
    free(temp_header);
    return len;
}

enum file_read_status read_string_from_tuple(FILE* file, char** string, uint64_t pattern_size, uint64_t offset) {
    size_t str_len = how_long_string_is(file, offset);
    size_t rts = get_real_tuple_size(pattern_size);
    *string = malloc(str_len * rts);
    struct tuple* temp_tuple;
    for (size_t iter = 0; iter < str_len; iter++) {
        fseek(file, offset, SEEK_SET);
        read_string_tuple(file, &temp_tuple, pattern_size);
        offset = temp_tuple->header.next;
        strncpy((*string) + rts * iter, (char*)temp_tuple->data, rts);
        free(temp_tuple->data);
        free(temp_tuple);
    }
    return 0;
}



enum file_write_status write_tree_subheader(FILE* file, struct tree_subheader* subheader) {
    enum file_write_status code = write_to_file(file, subheader, sizeof(struct tree_subheader));
    return code;
}

enum file_write_status write_pattern(FILE* file, struct key** pattern, size_t pattern_size) {
    enum file_write_status code = NULL_VALUE;
    for (; pattern_size-- > 0; pattern++) {
        code |= write_to_file(file, (*pattern)->header, sizeof(struct key_header));
        code |= write_to_file(file, (*pattern)->key_value, (*pattern)->header->size);
    }
    return code;
}

enum file_write_status write_id_sequence(FILE* file, uint64_t* id_sequence, size_t size) {
    enum file_write_status code = write_to_file(file, id_sequence, size);
    return code;
}

enum file_write_status write_tree_header(FILE* file, struct tree_header* header) {
    fseek(file, 0, SEEK_SET);

    size_t pattern_size = header->subheader->pattern_size;

    enum file_write_status code = write_tree_subheader(file, header->subheader);
    if (code != WRITE_OK) {
        printf("WRITE ERROR\n");
    }

    fseek(file, sizeof(struct tree_subheader), SEEK_SET);
    code |= write_pattern(file, header->pattern, pattern_size);
    size_t real_id_array_size = get_id_array_size(header->subheader->pattern_size, header->subheader->cur_id);
    code |= write_id_sequence(file, header->id_sequence, real_id_array_size * sizeof(uint64_t));


    if (code == CRUD_INVALID) {
        printf("WRITE ERROR\n");
    }
    return code;
}

enum file_write_status init_empty_file(FILE* file, char** pattern, uint32_t* types, size_t pattern_size, size_t* key_sizes) {
    fseek(file, 0, SEEK_SET);
    struct tree_header* header = (struct tree_header*)malloc(sizeof(struct tree_header));
    generate_empty_tree_header(pattern, types, pattern_size, key_sizes, header);
    return write_tree_header(file, header);
}

enum file_write_status write_tuple(FILE* file, struct tuple* tuple, size_t tuple_size) {
    union tuple_header* tuple_header = malloc(sizeof(union tuple_header));
    *tuple_header = tuple->header;
    enum file_write_status code = write_to_file(file, tuple_header, sizeof(union tuple_header));
    free(tuple_header);

    code |= write_to_file(file, tuple->data, tuple_size);
    return code;
}

void print_tree_header_from_file(FILE* file) {
    struct tree_header* header = malloc(sizeof(struct tree_header));
    read_tree_header(header, file);
    printf("=============== HEADER ===============\n");
    printf("%-20s%ld\n", "ASCII Signature: ", header->subheader->ASCII_signature);
    printf("%-20s%ld\n", "Root Offset: ", header->subheader->root_offset);
    printf("%-20s%ld\n", "First Sequence: ", header->subheader->first_seq);
    printf("%-20s%ld\n", "Second Sequence: ", header->subheader->second_seq);
    printf("%-20s%ld\n", "Current ID: ", header->subheader->cur_id);
    printf("%-20s%ld\n", "Pattern Size: ", header->subheader->pattern_size);
    printf("=============== FIELDS ===============\n");
    for (size_t iter = 0; iter < header->subheader->pattern_size; iter++) {
        printf("Key %3d [Type %3d]: %s\n",
            header->pattern[iter]->header->size, header->pattern[iter]->header->type,
            header->pattern[iter]->key_value);
    }

    free_test_tree_header(header);
}

void print_tuple_array_from_file(FILE* file) {
    struct tree_header header;
    read_tree_header(&header, file);
    uint32_t* types;
    size_t size;
    get_types(file, &types, &size);
    struct tuple* cur_tuple;

    for (size_t i = 0; i < header.subheader->cur_id; i++) {
        if (header.id_sequence[i] == NULL_VALUE) continue;

        fseek(file, header.id_sequence[i], SEEK_SET);
        read_basic_tuple(file, &cur_tuple, size);
        printf("=============== TUPLE %1zu ===============\n", i);
        printf("%-20s %lu\n", "parent", cur_tuple->header.parent);
        for (size_t iter = 0; iter < size; iter++) {
            if (types[iter] == STRING_TYPE) {
                char* s;
                read_string_from_tuple(file, &s, header.subheader->pattern_size, cur_tuple->data[iter]);
                printf("%-20s %s\n", header.pattern[iter]->key_value, s);
                free(s);
            }
            else if (types[iter] == INTEGER_TYPE || types[iter] == BOOLEAN_TYPE) {
                printf("%-20s %lu\n", header.pattern[iter]->key_value, cur_tuple->data[iter]);
            }
            else if (types[iter] == FLOAT_TYPE) {
                double res;
                memcpy(&res, &(cur_tuple->data[iter]), sizeof(cur_tuple->data[iter]));
                printf("%-20s %.6f\n", header.pattern[iter]->key_value, res);
            }
        }
        free(cur_tuple->data);
        free(cur_tuple);
    }
    free(types);
}

void free_test_tree_header(struct tree_header* header) {
    for (size_t iter = 0; iter < header->subheader->pattern_size; iter++) {
        free(header->pattern[iter]->key_value);
        free(header->pattern[iter]->header);
        free(header->pattern[iter]);
    }

    free(header->pattern);
    free(header->id_sequence);
    free(header->subheader);
    free(header);
}

void free_test_tuple(struct tuple* tuple) {
    free(tuple->data);
    free(tuple);
}
struct map_data {
    void* ptr;
    size_t size;
};

struct map_data map[100000] = { 0 };
size_t glob_size = 0;
size_t iter = 0;

void* malloc_test(size_t size) {
    glob_size += size;
    void* ptr = malloc(size);
    map[iter].ptr = ptr;
    map[iter++].size = size;
    return ptr;
}

void free_test(void* ptr) {
    free(ptr);
    for (size_t i = 0; i < 100000; i++) {
        if (map[i].ptr == ptr) {
            glob_size -= map[i].size;
            map[i].ptr = 0;
            break;
        }
    }
}

void print_ram() {
    printf("'%zu'\n", glob_size);
}


void print_result_list_tuple(struct result_list_tuple* result) {
    printf("%lu\n", result->id);
}