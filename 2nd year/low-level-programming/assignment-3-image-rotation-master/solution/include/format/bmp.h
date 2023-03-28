#ifndef BMP_H
#define BMP_H

#include "image/image.h"
#include <stdint.h>
#include <stdio.h>

struct bmp_header{
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
}__attribute__((packed));

struct image* img_from_bmp(FILE* input_img);

void bmp_from_img(struct image img, FILE* output_file ,FILE* input_file);



#endif
