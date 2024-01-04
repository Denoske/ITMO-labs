#include "../include/view.h"

void print_tab(int *count) {
    for (int i = 0; i < *count; i++) {
        printf("%s", TAB);
    }
    (*count)++;
}

void print_attribute(struct attribute *attribute, int *count_tab) {

    print_tab(count_tab);
    printf("left part - %s\n", attribute->left);
    print_tab(count_tab);
    printf("condition - %s\n", attribute->condition);
    print_tab(count_tab);
    printf("right part - %s\n", attribute->right);

    if (attribute->next_attribute) {
        if (attribute->next_attribute->combined_condition) {
            print_tab(count_tab);
            printf("between pair - %s\n", attribute->next_attribute->combined_condition);
        }
        print_attribute(attribute->next_attribute, count_tab);
    }
}

void get_request_view(struct request *request) {
    int count_tab = 1;
    struct attribute *attribute = request->attributes;

    printf("\naction - %s\n\n", request->operation);
    printf("id - %s\n", request->parent_id);

    if (request->star) {
        print_tab(&count_tab);
        printf("all nodes - %s\n", request->star);
    }

    if (attribute) print_attribute(attribute, &count_tab);
}
