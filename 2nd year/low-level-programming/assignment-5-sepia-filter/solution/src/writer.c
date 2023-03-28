#include "bmp_header.h"
#include "bmp_writer.h"
#include "image_actions.h"
#include "struct_image.h"

#include <stdlib.h>


static struct bmp_header make_header(uint64_t height, uint64_t width) {
    struct bmp_header header = {0};
    header.bfType = 0x4D42;
    header.bfileSize = sizeof(struct bmp_header) + sizeof(struct pixel) * width * height
                       + get_padding(width) * height;
    header.bfReserved = 0;
    header.bOffBits = BMP_HEADER_SIZE;
    header.biSize = BMP_HEADER_SIZE - 14;
    header.biWidth = width;
    header.biHeight = height;
    header.biPlanes = 1;
    header.biBitCount = 24;
    header.biCompression = 0;
    header.biSizeImage = PIXEL_STRUCT_SIZE * width * height + get_padding(width) * height;
    header.biXPelsPerMeter = 0;
    header.biYPelsPerMeter = 0;
    header.biClrUsed = 0;
    header.biClrImportant = 0;
    return header;
}

enum write_status to_bmp(FILE *const out, const struct image  *image) {
    struct bmp_header *header_ptr = malloc(BMP_HEADER_SIZE);
    *header_ptr = make_header(image->height, image->width);
    if (fwrite(header_ptr, BMP_HEADER_SIZE, 1, out) != 1) {
        free(header_ptr);
        return WRITE_ERROR_HEADER;
    }
    free(header_ptr);

    const size_t padding = get_padding(image->width);
    for (size_t i = 0; i < image->height; i++) {
        for (size_t j = 0; j < image->width; j++) {
            if (fwrite(&(image->data[i * image->width + j]), PIXEL_STRUCT_SIZE, 1, out) != 1) {
                return WRITE_ERROR_BYTES;
            }
        }
        for (size_t j = 0; j < padding; j++) {
            uint8_t padding_zero = 0;
            if (fwrite(&padding_zero, sizeof(uint8_t), 1, out) != 1) {
                return WRITE_ERROR_BYTES;
            }
        }
    }
    return WRITE_OK;
}
