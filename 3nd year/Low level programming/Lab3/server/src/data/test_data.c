#include "../../include/data/test_data.h"


void get_test_header(char*** pattern, uint32_t** types, size_t* pattern_size, size_t** sizes, size_t* tuple_count) {
    FILE* file_data = open_file();
    char* cur_line;
    size_t len = 0;
    getline(&cur_line, &len, file_data);
    //printf("%s\n", cur_line);
    init_header_param(&cur_line, tuple_count, pattern_size);
    malloc_header_struct(pattern_size, pattern, types, sizes);
    cur_line = strtok(cur_line, " ");
    cur_line = strtok(NULL, " ");
    int iter = 0;
    while (cur_line != NULL) {
        (*types)[iter] = get_type_from_string(cur_line);
        cur_line = strtok(NULL, " ");

        for (size_t i = 0; i < sizeof(cur_line); i++) {
            if (cur_line[i] == '\n') {
                cur_line[i] = '\000';
            }
        }
        (*pattern)[iter] = cur_line;
        (*sizes)[iter] = (strlen(cur_line)) / FILE_GRANULARITY + FILE_GRANULARITY;
        iter++;
        cur_line = strtok(NULL, " ");
    }

}

void get_test_data(FILE* file, size_t tuple_count, size_t pattern_size, uint32_t* types) {
    FILE* file_data = open_file();
    uint64_t* fields = malloc(sizeof(uint64_t*) * (pattern_size));
    uint64_t parent_id;
    char* cur_line = malloc(sizeof(char) * 1024);
    size_t len = 0;
    getline(&cur_line, &len, file_data);

    for (int tuple_idx = 0; tuple_idx < tuple_count; tuple_idx++) {
        getline(&cur_line, &len, file_data);

        // printf("%s\n", cur_line);

        cur_line = strtok(cur_line, " ");
        parent_id = get_parent_id(cur_line);
        cur_line = strtok(NULL, " ");

        //printf("parent id %lu\n", parent_id);
        int tuple_attr = 0;
        while (cur_line != NULL) {
            //printf("%s\n", cur_line);
            if (types[tuple_attr] != FLOAT_TYPE) {
                fields[tuple_attr] = get_real_tuple_attr(types[tuple_attr], cur_line);
            }
            else {
                double var = strtod(cur_line, NULL);
                memcpy(&fields[tuple_attr], &var, sizeof(var));
            }
            tuple_attr++;
            cur_line = strtok(NULL, " ");
        }
        //print_ram();
        add_tuple(file, fields, parent_id);
        //print_ram();
    }
    free(cur_line);
}

bool get_bool_attr(char* string) {
    if (strcmp(string, "True\r") == 0) {
        return true;
    } return false;
}

void init_header_param(char** cur_line, size_t* tuple_count, size_t* pattern_size) {
    char* tmp = malloc(sizeof(char) * strlen(*cur_line) + 1);
    strcpy(tmp, *cur_line);
    char* count_str = strtok(tmp, " ");
    *tuple_count = strtol(count_str, NULL, 10);
    int count = 0;

    while (strtok(NULL, " ")) {
        count++;
    }
    *pattern_size = count / 2;
    free(tmp);
}

void malloc_header_struct(const size_t* pattern_size, char*** pattern, uint32_t** types, size_t** sizes) {
    *pattern = malloc(sizeof(char*) * (*pattern_size));
    *types = malloc(sizeof(uint32_t) * (*pattern_size));
    *sizes = malloc(sizeof(size_t) * (*pattern_size));
}

uint64_t get_parent_id(char* string) {
    if (string > 0)
    {
        return strtol(string, NULL, 10);
    }
    else    
    return 0;
}

//char *get_cur_line(FILE *df) {
//    char *cur_line = "";
//    size_t len = 0;
//    getline(&cur_line, &len, df);
//    return cur_line;
//}

FILE* open_file() {
    FILE* df;
    df = fopen("data_generator/data.txt", "r");
    if (df == NULL) {
        printf("The file does not exist\n");
    }
}

//char* substr(const char *src, int m, int n) {
//    printf("%d\n", 0);
//    int len = n - m;
//    char *dest = (char*)malloc(sizeof(char) * (len + 1));
//    printf("%d\n", 0);
//    for (int i = m; i < n && (*(src + i) != '\0'); i++){
//        *dest = *(src + i);
//        dest++;
//    }
//    printf("%d\n", 0);
//    *dest = '\0';
//    return dest - len;
//}

uint64_t get_real_tuple_attr(int type, char* attr) {
    double var;
    if (type == BOOLEAN_TYPE) {
        return (uint64_t)get_bool_attr(attr);
    }
    else if (type == INTEGER_TYPE) {
        return (uint64_t)strtol(attr, NULL, 10);
    }
    else if (type == STRING_TYPE) {
        return (uint64_t)attr;
    }
    else {
        printf("Invalid input data format\n");
    }
}

int get_type_from_string(char* str_type) {
    if (!strcmp(str_type, "boolean")) {
        return BOOLEAN_TYPE;
    }
    else if (!strcmp(str_type, "integer")) {
        return INTEGER_TYPE;
    }
    else if (!strcmp(str_type, "float")) {
        return FLOAT_TYPE;
    }
    else if (!strcmp(str_type, "string")) {
        return STRING_TYPE;
    }
    else {
        printf("Invalid input data format\n");
    }
}