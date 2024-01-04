#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <string.h>
#include <inttypes.h>
#include "configuration.h"

/**
 *  онтейнер, хран€щий параметры файла
 * ASCII_signature - 0xFFFE или 0xFEFF символы дл€ определени€ little- или big- endian пор€док байтов
 * root_offset     - отступ корневого элемента
 * first_seq       - последовательность, увеличивающа€с€ при открытии файла
 * second_seq      - последовательность, увеличивающа€с€ при закрытии файла
 * cur_id          - последовательность дл€ отслеживани€ текущего id
 * pattern_size    - количество полей в шаблоне вершин
 */
struct tree_subheader {
    uint64_t ASCII_signature;
    uint64_t root_offset;
    uint64_t first_seq;
    uint64_t second_seq;
    uint64_t cur_id;
    uint64_t pattern_size;
};

enum tree_subheader_parameter {
    PAR_ASCII_SIGNATURE = 0,
    PAR_ROOT_OFFSET,
    PAR_FIRST_SEQ,
    PAR_SECOND_SEQ,
    PAR_CURRENT_ID,
    PAR_PATTERN_SIZE
};

/**
 *  онтейнер дл€ ключа шаблона
 */
#pragma pack(push, 4)
struct key_header {
    uint32_t size;
    uint32_t type;
};
struct key {
    struct key_header* header;
    char* key_value;
};
#pragma pack(pop)

/**
 * ѕолный заголовок файла
 * id_sequence - массив ссылок на кортежи
 */
struct tree_header {
    struct tree_subheader* subheader;
    struct key** pattern;
    uint64_t* id_sequence;
};

/**
 * «аголовок кортежа
 */
union tuple_header {
    struct {
        uint64_t parent;
        uint64_t alloc;
    };
    struct {
        uint64_t prev;
        uint64_t next;
    };
};

/**
 *  ортеж
 */
struct tuple {
    union tuple_header header;
    uint64_t* data;
};

#endif