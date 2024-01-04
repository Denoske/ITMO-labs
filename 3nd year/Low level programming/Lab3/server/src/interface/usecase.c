#include "../../include/interface/usecase.h"

void get_text_tuple(FILE *file, struct tuple *tuple, char *response) {

    char *curr = calloc(256, sizeof(char));

    char *str;
    read_string_from_tuple(file, &str, (uint64_t) 4, tuple->data[0]);

    double res;
    memcpy(&res, &(tuple->data[2]), sizeof(tuple->data[2]));


    snprintf(curr, 256,
             "=============== TUPLE %1zu ===============\nparent_id - %lu\nname - %s\nage - %lu\nheight - %.3f\nmale - %lu\n",
             tuple->header.alloc,
             tuple->header.parent,
             str,
             tuple->data[1],
             res,
             tuple->data[3]
    );

    strcat(response, curr);
    free(str);
}


void get_tuples(FILE *file, struct result_list_tuple *list, char *response) {
    if (list != NULL) {
        struct result_list_tuple *next;
        while (list != NULL) {
            next = list->prev;
            get_text_tuple(file, list->value, response);
            list = next;
        }
    }
}

void manage(char xml_request[], FILE *file, int fd) {

    struct tree_header *treeHeader = malloc(sizeof(struct tree_header));
    read_tree_header(treeHeader, file);

    xmlDocPtr request_tree = xmlReadMemory(xml_request, MAX_REQUEST_SIZE, 0, NULL, XML_PARSE_RECOVER);
    xmlNodePtr lastNode = request_tree->last;

    while (lastNode->last != NULL) {
        lastNode = lastNode->last;
    }

    char *response = calloc(MAX_RESPONSE_SIZE, sizeof(char));

    if (xmlStrEqual(request_tree->last->name, xmlCharStrdup("add"))) {

        uint64_t *data = malloc(sizeof(uint64_t) * 4);
        data[0] = (uint64_t) xmlGetProp(lastNode, xmlCharStrdup(treeHeader->pattern[0]->key_value));
        data[1] = (uint64_t) atoi((char *) xmlGetProp(lastNode, xmlCharStrdup(treeHeader->pattern[1]->key_value)));
        double d = atof((char *) xmlGetProp(lastNode, xmlCharStrdup(treeHeader->pattern[2]->key_value)));
        memcpy(&data[2], &d, sizeof(double));
        data[3] = (uint64_t) atoi((char *) xmlGetProp(lastNode, xmlCharStrdup(treeHeader->pattern[3]->key_value)));


        if (add_tuple(file, data, atoi((char *) xmlGetProp(lastNode->parent, xmlCharStrdup(TUPLE_ID)))) == 0) {
            response = "added!\n";
        } else {
            response = "error";
        }

    } else if (xmlStrEqual(request_tree->last->name, xmlCharStrdup("remove"))) {
        if (remove_tuple(file, atoi((char *) xmlGetProp(lastNode, xmlCharStrdup(TUPLE_ID))), 0) == 0) {
            response = "deleted!\n";
        } else {
            response = "error";
        }
    } else if (xmlStrEqual(request_tree->last->name, xmlCharStrdup("update"))) {

        uint64_t param = atoi((char *) xmlGetProp(lastNode, xmlCharStrdup(treeHeader->pattern[1]->key_value)));
        uint64_t id = atoi((char *) xmlGetProp(lastNode->parent, xmlCharStrdup(TUPLE_ID)));

        if (update_tuple(
                file,
                INTEGER_TYPE,
                &param,
                id
        ) == 0) {
            response = "updated\n";
        } else {
            response = "error";
        }

    } else if (xmlStrEqual(request_tree->last->name, xmlCharStrdup("find"))) {

        if (xmlStrEqual(xmlGetProp(request_tree->last->last, xmlCharStrdup(TUPLE_ID)), xmlCharStrdup(STAR))) {

            struct result_list_tuple *list = NULL;
            uint64_t cond = atoi((char *) xmlGetProp(lastNode,
                                                     xmlCharStrdup(treeHeader->pattern[1]->key_value)));
            find_by_field(file,
                          INTEGER_TYPE,
                          &cond,
                          &list);
            get_tuples(file, list, response);
            free_result_list(list);

        } else {

            if (request_tree->last->children == lastNode) {

                struct tuple *tuple;
                uint64_t id = atoi((char *) xmlGetProp(lastNode, xmlCharStrdup(TUPLE_ID)));
                get_tuple(file, &tuple, id);
                get_text_tuple(file, tuple, response);

            } else {

                struct result_list_tuple *list = NULL;
                uint64_t id = atoi((char *) xmlGetProp(request_tree->last->children, xmlCharStrdup(TUPLE_ID)));
                find_by_parent(file, id, &list);
                get_tuples(file, list, response);
                free_result_list(list);
            }
        }
    }

    send_response(response, fd);
}