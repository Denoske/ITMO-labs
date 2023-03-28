#ifndef IMAGE_ACTIONS
#define IMAGE_ACTIONS

#include "struct_image.h"

#include <stddef.h>

#define BMP_REQUIRED_PADDING 4

size_t get_padding(size_t width);
void free_image(struct image* image);
struct image* rotate_image(struct image* const source, struct image* target);
struct image*  sepia_with_asm(struct image* source);
struct image*  sepia_with_c(struct image* source);


#endif
