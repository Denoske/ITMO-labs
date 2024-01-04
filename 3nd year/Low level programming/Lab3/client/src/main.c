#include "../include/parser.h"
#include "../include/view.h"
#include "../include/client.h"

void free_request(struct request *request) {
    if (request->attributes) {
        struct attribute *attribute;
        while (request->attributes) {
            attribute = request->attributes;
            request->attributes = attribute->next_attribute;
            free(attribute);
        }
    }
    if (request->operation) free(request->operation);
    if (request->parent_id) free(request->parent_id);
    if (request->star) free(request->star);
    free(request);
}

int main(int argc, char **argv) {

    while (1) {

        int size_tree;
        xmlDocPtr request_tree;

        printf("your request?\n\n");

        char req[MAX_REQUEST_SIZE];
        fgets(req, MAX_REQUEST_SIZE, stdin);

        struct request *request = malloc(sizeof(struct request));
        enum parser_status status = parse_request(req, request);
        if (status != PARSE_OK) {
            printf("parse error\n");
            exit(status);
        }

        request_tree = xmlNewDoc(BAD_CAST "1.0");
        status = get_xml(request, request_tree);
        xmlChar *str_tree = (xmlChar *) malloc(sizeof(xmlChar) * MAX_REQUEST_SIZE);
        xmlDocDumpMemory(request_tree, &str_tree, &size_tree);

        printf("%s\n", (char *) str_tree);

        if (status == WRAP_OK) sendRequest(atoi(argv[1]), size_tree, (char *) str_tree);

        free(str_tree);
        free_request(request);
    }
    return 0;
}
