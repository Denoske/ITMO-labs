#include "image/image.h"
#include "file/file.h"
#include "format/bmp.h"
#include <stdlib.h>




int main( int argc, char** argv ) {
    (void) argc; (void) argv;

    if(argc != 3) {
        fprintf(stderr, "Недостаточное количество аргументов");
        return 5;
    }
    FILE* input_file = NULL;
    FILE* output_file = NULL;

    if (open_file(&input_file, argv[1], "rb") != OPEN) {
        fprintf(stderr, "Не удается открыть входной файл для чтения!");
        return 1;
    }
    if (open_file(&output_file, argv[2], "wb") != OPEN) {
        fprintf(stderr, "Не удается открыть выходной файл для записи!");
        close_file(input_file);
        return 2;
    }
    struct image* input_image = img_from_bmp(input_file);
    struct image trans_picture = twist(input_image);

    bmp_from_img(trans_picture, output_file, input_file);

    free(input_image->data);
    free(trans_picture.data);
    free(input_image);


    if (close_file(input_file)) {
        fprintf(stderr, "Произошла ошибка при закрытии входного файла!");
        return 3;
    }

    if (close_file(output_file)) {
        fprintf(stderr, "Произошла ошибка при закрытии выходного файла!");
        return 4;
    }
    return 0;
}
