#include "../include/bmp_reader.h"
#include "../include/bmp_writer.h"
#include "../include/image_actions.h"
#include "../include/struct_image.h"

#include <malloc.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>



int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "%s\n", "Invalid number of arguments");
        return 1;
    }

    FILE *source_file = fopen(argv[1], "rb");
    if (source_file == NULL) {
        fprintf(stderr, "Invalid input file");
    }

    FILE *target_c_file = fopen(argv[2], "wb ");
    FILE *target_asm_file = fopen(argv[3], "wb ");

    struct image *source_image = malloc(sizeof(struct image));

    if (from_bmp(source_file, source_image) == READ_OK) {
        struct rusage r;
        struct timeval start;
        struct timeval end;

        getrusage(RUSAGE_SELF, &r);
        start = r.ru_utime;
        struct image *target_c_image = sepia_with_c(source_image);
        getrusage(RUSAGE_SELF, &r);
        end = r.ru_utime;
        long res = ((end.tv_sec - start.tv_sec) * 1000000L) + end.tv_usec - start.tv_usec;
        printf("C implementation time: %ld\n", res);

        to_bmp(target_c_file, target_c_image);
        free_image(target_c_image);

        getrusage(RUSAGE_SELF, &r);
        start = r.ru_utime;
        struct image *target_asm_image = sepia_with_asm(source_image);
        getrusage(RUSAGE_SELF, &r);
        end = r.ru_utime;
        res = ((end.tv_sec - start.tv_sec) * 1000000L) + end.tv_usec - start.tv_usec;
        printf("ASM implementation time: %ld\n", res);

        to_bmp(target_asm_file, target_asm_image);
        free_image(target_asm_image);
    }
    free_image(source_image);
    return 0;
}
