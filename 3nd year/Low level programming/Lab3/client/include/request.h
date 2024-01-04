#ifndef ROMA_LAB2_REQUEST_H
#define ROMA_LAB2_REQUEST_H

#define MAX_STRING_SIZE 32
#define TAB "    "

struct attribute {
    char *left;
    char *right;
    char *condition;
    struct attribute *next_attribute;
    char *combined_condition;
};

struct request {
    char *operation;
    char *parent_id;
    char *star;
    struct attribute *attributes;
};

#endif //ROMA_LAB2_REQUEST_H
