#include "file/file.h"

enum ST_OPEN open_file(FILE** const file, const char* filename, const char* mode) {
    *file = fopen(filename, mode);
    if ((*file) == NULL) {
        return OP_ERROR;
    }
    return OPEN;
}

enum ST_CLOSE close_file(FILE* const file) {
    if (fclose(file) != 0) {
        return CL_ERROR;
    }
    return CLOSE;
}
