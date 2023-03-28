#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>

struct pixel
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
}__attribute__((packed));


struct image
{
    uint32_t width;
    uint32_t height;
    struct pixel* data;

};

struct image twist(struct image* input_image);
struct image create(uint32_t width, uint32_t height);




#endif
