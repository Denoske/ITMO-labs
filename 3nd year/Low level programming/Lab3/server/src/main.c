#include "../include/data/test_data.h"
#include "../include/interface/server.h"
#include "../include/interface/usecase.h"

int main(int argc, char **argv) {
    FILE *file;
    open_file_anyway(&file, "simple.txt");

    size_t pattern_size;
    size_t tuple_count;
    char **pattern;
    uint32_t *types;
    size_t *sizes;

    get_test_header(&pattern, &types, &pattern_size, &sizes, &tuple_count);

    init_empty_file(file, pattern, types, pattern_size, sizes);

    get_test_data(file, tuple_count, pattern_size, types);

    print_tree_header_from_file(file);

    print_tuple_array_from_file(file);

    free(pattern);
    free(types);
    free(sizes);

    int server = -1;
    if (argc > 1 && argv[1] != NULL) {
        server = start_server(atoi(argv[1]));
    }

    if (server == -1) {
        printf("error");
        exit(1);
    }

    printf("start...\n");

    while (1) {
        char *request_xml = calloc(MAX_REQUEST_SIZE, sizeof(char));
        int fd = handler_request(server, request_xml);
        manage(request_xml, file, fd);

        print_tuple_array_from_file(file);
    }

    return 0;
}

/*

    uint64_t *fields = malloc(sizeof(uint64_t * ) * 4);
    fields[0] = (uint64_t) "asdsadqwr";
    fields[1] = 1111;
    fields[3] = 1;
    uint64_t parent_id = 0;
    double d = 2222.2;
    memcpy(&fields[2], &d, sizeof(d));

    проверка размера файла
     for (int i = 0; i < 100; i++) {
        add_test(file, fields, 0);
        fseek(file, 0, SEEK_END);
        printf("%ld\n", ftell(file));
    }

 */


