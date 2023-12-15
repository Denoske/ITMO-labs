#include <malloc.h>

#include "list.h"

listNode* createNode(uint64_t size, uint64_t indexNumber) {
    listNode* node = malloc(sizeof(listNode));
    if (node) {
        node->size = size;
        node->indexNumber = indexNumber;
        node->prev = NULL;
        node->next = NULL;
    }
    return node;
}

void destroyList(sortedList* list) {
    listNode* curr = list->front;
    while (curr) {
        listNode* next = curr->next;
        free(curr);
        curr = next;
    }
}

void insertNode(sortedList* list, listNode* node) {
    if (list->front) {
        listNode* curr = list->front;
        while (curr) {
            if ((node->size > curr->size) || (node->size == 0 && curr->size == 0)) {
                if (curr == list->front) {
                    list->front = node;
                } else {
                    curr->prev->next = node;
                }
                node->prev = curr->prev;
                node->next = curr;
                curr->prev = node;
                break;
            } else if (curr == list->back) {
                list->back = node;
                node->next = curr->next;
                node->prev = curr;
                curr->next = node;
                break;
            }
            curr = curr->next;
        }
    } else {
        list->front = node;
        list->back = node;
    }
}

listNode* popFront(sortedList* list) {
    if (list) {
        if (list->front) {
            listNode* front = list->front;
            list->front = list->front->next;
            if (list->front) {
                list->front->prev = NULL;
            } else {
                list->back = NULL;
            }
            return front;
        }
    }
    return NULL;
}

listNode* popBack(sortedList* list) {
    if (list) {
        if (list->back) {
            listNode* back = list->back;
            list->back = list->back->prev;
            if (list->back) {
                list->back->next = NULL;
            } else {
                list->front = NULL;
            }
            return back;
        }
    }
    return NULL;
}

bool removeNodeByIndexNumber(sortedList* list, uint64_t indexNumber) {
    listNode* curr = list->front;
    while (curr) {
        listNode* prev = curr->prev;
        listNode* next = curr->next;
        if (curr->indexNumber == indexNumber) {
            if (prev) {
                prev->next = next;
            }
            if (next) {
                next->prev = prev;
            }
            if (curr == list->front) {
                list->front = next;
            }
            if (curr == list->back) {
                list->back = prev;
            }
            free(curr);
            return true;
        }
        curr = next;
    }
    return false;
}