#include "../include/parser.h"


void print_error() {
    printf("incorrect\n");
    exit(EXIT_FAILURE);
}

void check_path(char *req, int *path_length) {
    int bracket = 0;

    for (int i = 0; i < *path_length; i++) {
        if (req[i] == '[') bracket++;
        if (req[i] == ']') bracket--;
    }

    if (bracket != 0) {
        print_error();
    }
}

void remove_char(char **req, int *path_length) {
    (*path_length)--;
    (*req)++;
}


int check_on_del_char(char symbol) {
    if (symbol == '=') return 1;
    if (symbol == '!') return 1;
    if (symbol == '>') return 1;
    if (symbol == '<') return 1;

    return 0;
}

char *read_condition(char **req, int *path_length) {

    char *cond = calloc(4, sizeof(char));

    int i;
    for (i = 0; i < *path_length; i++) {
        if (((*req)[i] >= 'a' && (*req)[i] <= 'z') || ((*req)[i] >= '1' && (*req)[i] <= '9')) {
            break;
        }
        cond[i] = (*req)[i];
    }

    for (int j = 0; j < i; j++) {
        remove_char(req, path_length);
    }

    return cond;
}

char *read_left(char **req, int *path_length) {

    if (*req[0] == '[') remove_char(req, path_length);
    char *word = calloc(MAX_STRING_SIZE, sizeof(char));

    int i;
    for (i = 0; i < *path_length; i++) {
        if (check_on_del_char((*req)[i])) {
            break;
        }
        word[i] = (*req)[i];
    }

    for (int j = 0; j < i; j++) {
        remove_char(req, path_length);
    }

    return word;
}

char *read_word(char **req, int *path_length) {

    if (*req[0] == '[') remove_char(req, path_length);
    char *word = calloc(MAX_STRING_SIZE, sizeof(char));

    int i;
    for (i = 0; i < *path_length; i++) {
        if ((*req)[i] == '/' || (*req)[i] == ']' || (*req)[i] == '[' || (*req)[i] == '\n') {
            if ((*req)[i] == ']' || (*req)[i] == '[') i--;
            break;
        }
        word[i] = (*req)[i];
    }
    i++;

    for (int j = 0; j < i; j++) {
        remove_char(req, path_length);
    }

    return word;
}

void read_attributes(char **req, int *path_length, struct attribute *attribute) {

    if ((*req)[0] == '[') {

        char *left = read_left(req, path_length);
        char *cond = read_condition(req, path_length);
        char *right = read_word(req, path_length);

        attribute->left = left;
        attribute->condition = cond;
        attribute->right = right;
    }

    if ((*req)[0] == ']') {
        remove_char(req, path_length);
        if (*path_length > 1) {
            struct attribute *new_attribute = malloc(sizeof(struct attribute));
            read_attributes(req, path_length, new_attribute);
            attribute->next_attribute = new_attribute;
        }
    } else if ((*req)[0] == '|' || (*req)[0] == '&') {
        char *combined_condition = read_word(req, path_length);
        attribute->combined_condition = combined_condition;
        read_attributes(req, path_length, attribute);
    }
}

enum parser_status parse_request(char *req, struct request *request) {

    int path_length = strlen(req);

    check_path(req, &path_length);

    char *operation = read_word(&req, &path_length);
    request->operation = operation;

    if (!(
            strcmp("add", operation) == 0 ||
            strcmp("find", operation) == 0 ||
            strcmp("remove", operation) == 0 ||
            strcmp("update", operation) == 0
    ))
        print_error();

    char *id = read_word(&req, &path_length);
    request->parent_id = id;

    if (req[0] == '[') {
        struct attribute *attribute = malloc(sizeof(struct attribute));
        request->attributes = attribute;
        read_attributes(&req, &path_length, attribute);
    } else if (req[0] == '*') {
        struct attribute *attribute = malloc(sizeof(struct attribute));
        attribute->left = "id";
        attribute->right = "*";
        request->attributes = attribute;
    }

    return PARSE_OK;
}

void get_xml_attribute(struct request *request, xmlDocPtr request_tree, xmlNodePtr parent) {

    struct attribute *attribute = request->attributes;

    xmlNodePtr node;

    if (parent != NULL) {
        node = xmlNewChild(parent, NULL, BAD_CAST
        "tuple", NULL);
    } else {
        node = xmlNewChild(request_tree->last, NULL, BAD_CAST
        "tuple", NULL);
    }

    int i = 1, j = 1;
    while (attribute) {

        if (attribute->combined_condition) {
            char *comb_cond = calloc(sizeof(char), 16);
            snprintf(comb_cond, 16, "comb_cond%d", j++);
            xmlNewProp(node, BAD_CAST
            comb_cond, BAD_CAST
            attribute->combined_condition);
        }

        xmlNewProp(node, BAD_CAST
        attribute->left, BAD_CAST
        attribute->right);

        char *operand = calloc(sizeof(char), 16);
        snprintf(operand, 16, "operand_%d", i++);
        xmlNewProp(node, BAD_CAST
        operand, BAD_CAST
        attribute->condition);

        attribute = attribute->next_attribute;
    }
}

enum parser_status get_xml(struct request *request, xmlDocPtr xmlDocPtr) {

    xmlNodePtr
    root = xmlNewNode(NULL, BAD_CAST
    request->operation);
    xmlDocSetRootElement(xmlDocPtr, root);

    xmlNodePtr parent = NULL;

    if (request->parent_id) {
        parent = xmlNewChild(root, NULL, BAD_CAST
        "tuple", NULL);
        xmlNewProp(parent, BAD_CAST
        "id", BAD_CAST
        request->parent_id);
    }

    if (request->attributes) get_xml_attribute(request, xmlDocPtr, parent);

    return WRAP_OK;
}
