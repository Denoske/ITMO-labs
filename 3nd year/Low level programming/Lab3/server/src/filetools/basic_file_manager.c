#include "../../include/filetools/basic_file_manager.h"

enum file_read_status read_from_file(FILE* file, void* buffer, size_t size) {
    size_t length = fread(buffer, size, 1, file);
    enum file_read_status code = READ_OK;
    if (length < 1) {
        code = READ_INVALID;
    }
    else if (sizeof(buffer) < length) {
        code = READ_END_OF_FILE;
    }
    return code;
}

//enum file_write_status write_to_file(FILE* file, void* buffer, size_t size) {
enum file_write_status write_to_file(FILE* file, char* buffer, size_t size) {
    if (buffer > 0) {
        size_t length = fwrite(buffer, size, 1, file);
        enum file_write_status code = WRITE_OK;
        if (length < 1) {
            code = WRITE_WRONG_INTEGRITY;
        }
        else if (sizeof(buffer) < length) {
            code = WRITE_INVALID;
        }
        return code;
    }
    else return WRITE_INVALID;
}

static enum file_open_status open_file(char* filename, FILE** file, char* open_descriptor) {
    *file = fopen(filename, open_descriptor);
    enum file_open_status code = OPEN_OK;
    if (*file == NULL) {
        code = OPEN_FAILED;
    }
    return code;
}

enum file_open_status open_exist_file(char* filename, FILE** file) {
    return open_file(filename, file, "r+b");
}

enum file_open_status open_new_file(char* filename, FILE** file) {
    return open_file(filename, file, "w+b");
}

void close_file(FILE* file) {
    fclose(file);
}

enum file_open_status open_file_anyway(FILE** file, char* filename) {
    enum file_open_status code = open_exist_file(filename, file);
    if (code == OPEN_FAILED) {
        code = open_new_file(filename, file);
    }
    return code;
}

enum file_open_status open_empty_file(char* filename, FILE** file) {
    //open_file(filename, file, "w");
    //close_file(*file);
    return open_file(filename, file, "w+b");
}