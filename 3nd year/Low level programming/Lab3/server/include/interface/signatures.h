#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <string.h>
#include <inttypes.h>
#include "configuration.h"

/**
 * ���������, �������� ��������� �����
 * ASCII_signature - 0xFFFE ��� 0xFEFF ������� ��� ����������� little- ��� big- endian ������� ������
 * root_offset     - ������ ��������� ��������
 * first_seq       - ������������������, ��������������� ��� �������� �����
 * second_seq      - ������������������, ��������������� ��� �������� �����
 * cur_id          - ������������������ ��� ������������ �������� id
 * pattern_size    - ���������� ����� � ������� ������
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
 * ��������� ��� ����� �������
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
 * ������ ��������� �����
 * id_sequence - ������ ������ �� �������
 */
struct tree_header {
    struct tree_subheader* subheader;
    struct key** pattern;
    uint64_t* id_sequence;
};

/**
 * ��������� �������
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
 * ������
 */
struct tuple {
    union tuple_header header;
    uint64_t* data;
};

#endif