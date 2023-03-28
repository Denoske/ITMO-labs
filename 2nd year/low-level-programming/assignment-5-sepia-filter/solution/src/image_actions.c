#include "../include/image_actions.h"

#include <malloc.h>
#include <stdint.h>

size_t get_padding(uint64_t width) {
    return (size_t) BMP_REQUIRED_PADDING - (width * PIXEL_STRUCT_SIZE) % BMP_REQUIRED_PADDING;
}

void free_image(struct image* image) {
    free(image->data);
    free(image);
}
