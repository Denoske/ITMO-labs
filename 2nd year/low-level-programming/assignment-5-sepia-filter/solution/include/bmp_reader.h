#include "struct_image.h"
#include <stdio.h>

#ifndef BMP_READER
#define BMP_READER

enum read_status {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER
    /* коды других ошибок  */
};

enum read_status from_bmp(FILE *const in, struct image *image);

#endif
