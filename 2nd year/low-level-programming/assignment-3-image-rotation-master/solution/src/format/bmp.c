#include "format/bmp.h"
#include <stdio.h>
#include <stdlib.h>

struct image* img_from_bmp(FILE* input_img){
    struct bmp_header header;

    fread(&header, 1, sizeof(struct bmp_header), input_img);
    
    struct image *output_img = (struct image*)malloc(sizeof(struct image));

    output_img->width = header.biWidth;
    output_img->height = header.biHeight;

    uint32_t padding = 0;

    if((output_img->width*3)%4){
        padding = 4 - (output_img->width*3)%4;
    }

    if(sizeof(struct bmp_header) != header.bOffBits){
        fseek(input_img, header.bOffBits - (uint32_t)sizeof(struct bmp_header), 1);
    }

    output_img->data = (struct pixel*)malloc(output_img->width*output_img->height*3);

    uint32_t cur = 0;

    for(uint32_t i = 0; i < output_img->height; i++){
        cur += fread((char*)output_img->data+cur, 1, output_img->width*3, input_img);
        if(padding){
            fseek(input_img, padding, 1);
        }
    }

    fseek(input_img, 0, 0);
    
    return output_img;
}


void bmp_from_img(const struct image img, FILE* output_file, FILE* input_file){
    struct bmp_header header;

    fseek(input_file, 0, 0);
    fseek(output_file, 0, 0);
    fread(&header, 1, sizeof(struct bmp_header), input_file);

    uint32_t padding= 4 - ((img.width*3)%4);

    header.biWidth = img.width;
    header.biHeight = img.height;
    header.bfileSize = img.width * img.height * sizeof(struct pixel) + sizeof(struct bmp_header) + padding * img.height;
    header.biSizeImage = img.height * (img.width + padding);

    fwrite(&header, sizeof (struct bmp_header), 1, output_file);

    int8_t cur = 0;

    for(int i = 0; i < header.biHeight; i++){
        fwrite(((char*)img.data)+(i*img.width*3), img.width*3, 1, output_file);
        for (int j = 0; j < padding; ++j) {
            fwrite(&cur, sizeof(int8_t), 1, output_file);
        }
    }
}



