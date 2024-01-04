#ifndef ROMA_LAB2_PARSER_H
#define ROMA_LAB2_PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "request.h"
#include "malloc.h"

enum parser_status parse_request(char * req, struct request *request);

enum parser_status get_xml(struct request *request, xmlDocPtr xmlDocPtr);

enum parser_status {
    PARSE_OK = 0,
    WRAP_OK = 0,
    PARSE_INCORRECT_REQUEST = 1,
    PARSE_ERROR = 2,
    WRAP_ERROR = 3
};

#endif //ROMA_LAB2_PARSER_H
