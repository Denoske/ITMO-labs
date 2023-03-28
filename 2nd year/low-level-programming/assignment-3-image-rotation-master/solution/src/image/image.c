#include "image/image.h"
#include <stdlib.h>

struct image create(uint32_t width, uint32_t height){
    struct image image={
            .width = width,
            .height = height,
            .data = malloc(  width * sizeof(struct pixel) * height)
    };
    return image;
}
struct image twist(struct image* input_image){
    uint32_t width = input_image->width;
    uint32_t height  = input_image->height;
    struct image trans_picture = create(height, width);
    for(int i = 0; i < height; i++){
        for(int j  = 0; j < width; j++){
            trans_picture.data[j * height + (height - 1 - i)] = input_image->data[i*width+j];
        }
    }
    return trans_picture;
}
