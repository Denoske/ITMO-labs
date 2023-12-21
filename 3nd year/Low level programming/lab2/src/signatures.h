#ifndef LLP_2_SIGNATURES_H
#define LLP_2_SIGNATURES_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


/**
 * Filter object
 */
struct Filter_object {
    union {
        struct filter_scheme* filter; //Объект для фильтрации
        struct property_scheme* prop; //Объект для указания свойства - используется в добавлении
    };
    struct Filter_object* next;
    long tab_level;
};



/**
 * Filter scheme object
 */
struct filter_scheme {
    int operator_val;
    bool is_single_val;
    struct element* val;
    char attribute[30]; /*optional*/
};


/**
 * Element of tree
 */
struct element {
    union {
        char string_val[30];
        bool boolean;
        int32_t num;
        double double_num;
    };
    int element_type;
    
};

/**
 * Property object
 */
struct property_scheme {
    int node_type;
    char property_name[30];
       
};



#endif //LLP_2_SIGNATURES_H
