#ifndef FILE_H
#define FILE_H

#include <stdio.h>

enum ST_OPEN {
    OPEN = 0,
    OP_ERROR
};

enum ST_CLOSE{
    CLOSE = 0,
    CL_ERROR

};

enum ST_OPEN open_file(FILE** const file, const char* const filename, const char* const mode);
enum ST_CLOSE close_file(FILE* const file);


#endif
