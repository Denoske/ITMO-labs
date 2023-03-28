#ifndef STRUCT_IMAGE
#define STRUCT_IMAGE

#include <stdint.h>

#define PIXEL_STRUCT_SIZE sizeof(struct pixel)

struct image {
    uint64_t width, height;
    struct pixel *data;
};

struct pixel {
    uint8_t b, g, r;
}__attribute__((packed));

#endif
