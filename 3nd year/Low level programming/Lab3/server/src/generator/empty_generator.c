#include "../../include/generator/empty_generator.h"

static void generate_empty_tree_subheader(struct tree_subheader* subheader, size_t pattern_size) {
    subheader->pattern_size = (uint64_t)pattern_size;
    subheader->cur_id = NULL_VALUE;
    subheader->ASCII_signature = BIG_ENDIAN_SIGNATURE;
    subheader->first_seq = NULL_VALUE;
    subheader->second_seq = NULL_VALUE;
    subheader->root_offset = NULL_VALUE;
}

static void copy_string(char* from, char* to, size_t size_from, size_t size_to) {
    while (size_to-- && size_from--) *(to++) = *(from++);
}

static void generate_empty_pattern(struct key** key_pattern, char** pattern, uint32_t* types, size_t pattern_size, size_t* key_sizes) {
    struct key* pattern_key;
    size_t real_size;
    for (size_t iter = pattern_size; iter-- > 0; key_pattern++ && pattern++ && types++ && key_sizes++) {
        pattern_key = malloc(sizeof(struct key));
        real_size = (*key_sizes) / FILE_GRANULARITY * FILE_GRANULARITY + ((*key_sizes) % FILE_GRANULARITY ? FILE_GRANULARITY : 0);
        char* appended_string = malloc(sizeof(char) * real_size);
        copy_string(*pattern, appended_string, *key_sizes, real_size);
        pattern_key->key_value = appended_string;
        pattern_key->header = malloc(sizeof(struct key_header));
        pattern_key->header->size = (uint32_t)real_size;
        pattern_key->header->type = *types;
        *key_pattern = pattern_key;
    }
}

void generate_empty_tree_header(char** pattern, uint32_t* types, size_t pattern_size, size_t* key_sizes, struct tree_header* header) {
    header->subheader = (struct tree_subheader*)malloc(sizeof(struct tree_subheader));
    generate_empty_tree_subheader(header->subheader, pattern_size);

    header->pattern = malloc(sizeof(struct key*) * pattern_size);
    generate_empty_pattern(header->pattern, pattern, types, pattern_size, key_sizes);

    header->id_sequence = malloc(sizeof(uint64_t) * get_id_array_size(header->subheader->pattern_size, header->subheader->cur_id));
    for (size_t iter = 0; iter < get_id_array_size(header->subheader->pattern_size, header->subheader->cur_id); iter++) {
        header->id_sequence[iter] = 0;
    }
}