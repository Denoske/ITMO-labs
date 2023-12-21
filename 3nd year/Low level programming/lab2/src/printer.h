#ifndef LLP_2_PRINTER_H
#define LLP_2_PRINTER_H

#include "signatures.h"

void print_tab();

long print_property(struct property_scheme *prop, long tab_level);

long print_filter_obj(struct Filter_object *obj, long tab_level);

long print_el_for_single_filter(struct element *el, long tab_level);

#endif //LLP_2_PRINTER_H
