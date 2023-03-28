#include "struct_image.h"
#include <stdio.h>

#ifndef BMP_WRITER
#define BMP_WRITER

enum write_status {
    WRITE_OK = 0,
    WRITE_ERROR,
    WRITE_ERROR_HEADER,
    WRITE_ERROR_BYTES
    /* коды других ошибок  */
};

enum write_status to_bmp(FILE *const out, struct image const *image);


#endif
