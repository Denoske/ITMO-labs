#include "../include/bmp_header.h"
#include "../include/image_actions.h"

#include <stdlib.h>

struct image* rotate_image(struct image* const source, struct image* target) {
    target->width = source->height;
    target->height = source->width;
    target->data = (struct pixel *) malloc(sizeof(struct pixel) * target->width * target->height);
    for (size_t i = 0; i < source->height; i++) {
        for (size_t j = 0; j < source->width; j++) {
            target->data[target->width * j + target->width - i - 1] = source->data[i*source->width+j];
        }
    }
    return target;
}
