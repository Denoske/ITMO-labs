#include "iterator.h"
#include "document.h"

#include <malloc.h>

iterator* createIterator() {
    iterator* it = malloc(sizeof(iterator));
    if (it) {
        it->refs = NULL;
        it->length = 0;
        it->curr = -1;
    }
    return it;
}

void destroyIterator(iterator* it) {
    if (it) {
        if (it->refs) {
            free(it->refs);
        }
        free(it);
    }
}

bool addRef(iterator* dest, uint64_t ref) {
    if (dest) {
        uint64_t* tmp = realloc(dest->refs, sizeof(uint64_t) * (dest->length + 1));
        if (tmp) {
            dest->refs = tmp;
            dest->refs[dest->length++] = ref;
            return true;
        }
    }
    return false;
}

bool hasNext(iterator* it) {
    return it && (it->curr + 1 < it->length);
}

document* next(zgdbFile* file, iterator* it) {
    if (hasNext(it)) {
        return readDocument(file, it->refs[++it->curr]);
    }
    return NULL;
}