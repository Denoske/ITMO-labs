#include "printer.h"

void print_tab(long tab_level) {
    for (int i = 0; i < tab_level; i++) {
        printf("\t");
    }
}

long print_property(struct property_scheme *prop, long tab_level) {
    print_tab(tab_level);
    printf("property name: %s", prop->property_name);
    printf("\n");
    print_tab(tab_level);
    printf("property type: ");
    switch(prop->node_type) {
        case 0:
            printf("int32");
            break;
        case 1:
            printf("double");
            break;
        case 2:
            printf("string");
            break;
        case 3:
            printf("bool");
            break;
        default:
            printf("no such type");
            tab_level++;
            return tab_level;
    }
    printf("\n");
    return tab_level;
}

void print_element(struct element* el, long tab_level) {
    tab_level++;
    print_tab(tab_level);
    switch (el->element_type) {
        case 0:
            printf("value = %d" , el->num);
            break;
        case 1:
            printf("value = %f" , el->double_num);
            break;
        case 2:
            printf("value = %s", el->string_val);
            break;
        case 3:
            printf("value = %s", el->boolean ? "true" : "false");
            break;
        default:
            printf("no type with this num = %d", el->element_type);
    }
    printf("\n");
}


long print_el_for_single_filter(struct element* el, long tab_level) {
    print_tab(tab_level);
    tab_level++;
    printf("filter = select: ");
    printf("\n");
    print_tab(tab_level);
    tab_level++;
    if (el->element_type == 0) {
        printf(" --> element number: %d", el->num);
    }
    if (el->element_type == 2) {
        printf(" --> descendant schema name: %s", el->string_val);
    }
    printf("\n");
    return tab_level;
}


void print_operator(int operator_value, long tab_level) {
    print_tab(tab_level);
    tab_level++;
    printf("operator: ");
    printf("\n");
    print_tab(tab_level);
    tab_level++;
    switch(operator_value) {
        case 0:
            printf("equal to ");
            break;
        case 1:
            printf("not_equal to ");
            break;
        case 2:
            printf("more than");
            break;
        case 3:
            printf("less than");
            break;
        default:
            printf("not such operator :(");
    }
}

long print_filter_obj(struct Filter_object* obj, long tab_level) {
    print_tab(tab_level);
    tab_level++;
    printf("filter = select property:");
    printf("\n");
    print_tab(tab_level);
    tab_level++;
    printf(" --> property name %s", obj->filter->attribute);
    printf("\n");
    tab_level++;
    print_operator(obj->filter->operator_val,tab_level);
    printf("\n");
    tab_level++;
    print_element(obj->filter->val,tab_level);
    printf("\n");
    tab_level++;
    tab_level++;
    return tab_level;
}
