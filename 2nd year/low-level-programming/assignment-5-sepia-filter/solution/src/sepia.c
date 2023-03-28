#include "../include/bmp_reader.h"
#include "../include/bmp_writer.h"
#include "../include/image_actions.h"
#include "../include/struct_image.h"

#include <malloc.h>
#include <stdio.h>

static uint8_t cut(uint64_t x) {
    if (x < 255) {
        return x;
    }
    return 255;
}

static struct pixel filter_pixel(struct pixel const old) {
    struct pixel new_pixel = {0};
    static const float c[3][3] = {
            { .393f, .769f, .189f },
            { .349f, .686f, .168f },
            { .272f, .543f, .131f } };
    new_pixel.r = cut(old.r * c[0][0] + old.g * c[0][1] + old.b * c[0][2]);
    new_pixel.g = cut(old.r * c[1][0] + old.g * c[1][1] + old.b * c[1][2]);
    new_pixel.b = cut(old.r * c[2][0] + old.g * c[2][1] + old.b * c[2][2]);
    return new_pixel;
}

struct image *sepia_with_c(struct image *source) {
    struct image *target = malloc(sizeof(struct image));
    size_t size = source->width * source->height;
    target->height = source->height;
    target->width = source->width;
    target->data = malloc(sizeof(struct pixel) * size);
    for (size_t i = 0; i < size; i++) {
        target->data[i] = filter_pixel(source->data[i]);
    }

    return target;
}


extern void sepia_asm(struct pixel *, struct pixel *restrict);

struct image *sepia_with_asm(struct image *source) {
    struct image *target = malloc(sizeof(struct image));
    size_t size = source->width * source->height;
    target->height = source->height;
    target->width = source->width;
    target->data = malloc(sizeof(struct pixel) * size);
    size_t offset = size % 4;
    for (size_t i = 0; i + 4 < size; i = i + 4) {
        sepia_asm(source->data + i, target->data + i);
    }
    for (size_t i = 0; i < offset; i++) {
        target->data[size - offset + i] = source->data[size - offset + i];
    }
    return target;
}