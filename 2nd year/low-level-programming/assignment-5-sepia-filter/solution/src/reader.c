#include "bmp_header.h"
#include "bmp_reader.h"
#include "image_actions.h"
#include "struct_image.h"

#include <stdlib.h>


enum read_status from_bmp(FILE *const in, struct image *image) {
    struct bmp_header header;
    if (fread(&header, sizeof(struct bmp_header), 1, in) != 1) {
        return READ_INVALID_HEADER;
    }
    if (header.bfType != BMP_SIGNATURE) {
        return READ_INVALID_HEADER;
    }
    image->width = header.biWidth;
    image->height = header.biHeight;
    image->data = (struct pixel *) malloc(sizeof(struct pixel) * image->width * image->height);
    const size_t padding = get_padding(image->width);
    for (size_t i = 0; i < image->height; i++) {
        for (size_t j = 0; j < image->width; j++) {
            if (fread(&(image->data[i * image->width + j]), PIXEL_STRUCT_SIZE, 1, in) != 1) {
                return READ_INVALID_BITS;
            }
        }
        if (fseek(in, (long) padding, SEEK_CUR) != 0) {
            return READ_INVALID_BITS;
        }
    }
    return READ_OK;
}
