#ifndef LLP_2_DECL_H
#define LLP_2_DECL_H

#include "adder.h"

struct Filter_object *create_filter_obj(int op, char *attribute, struct element *el, long tab_level);

struct Filter_object *create_single_filter_obj(struct element *el, long tab_level);

struct Filter_object *create_property_scheme_filter_obj(char *prop_name, int type, long tab_level);



#endif //LLP_2_DECL_H
