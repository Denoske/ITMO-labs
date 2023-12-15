#include <malloc.h>
#include <string.h>

#include "schema.h"
#include "element.h"

documentSchema* createSchema(const char* name) {
    if (name && strlen(name) <= 12) {
        documentSchema* schema = malloc(sizeof(documentSchema));
        if (schema) {
            schema->length = 0;
            schema->elements = NULL;
            strcpy(schema->name, name);
            return schema;
        }
    }
    return NULL;
}

documentSchema* createElements() {
    return createSchema("0");
}

void destroySchema(documentSchema* schema) {
    if (schema) {
        if (schema->elements) {
            for (uint64_t i = 0; i < schema->length; i++) {
                destroyElement(schema->elements[i]);
            }
            free(schema->elements);
        }
        free(schema);
    }
}

bool addElementToSchema(documentSchema* schema, element* el) {
    element** tmp = realloc(schema->elements, sizeof(element*) * (schema->length + 1));
    if (tmp) {
        schema->elements = tmp;
        schema->elements[schema->length++] = el;
        return true;
    }
    return false;
}

element* getElementFromSchema(documentSchema* schema, const char* key) {
    if (schema && key && strlen(key) <= 12) {
        for (uint64_t i = 0; i < schema->length; i++) {
            if (!strcmp(schema->elements[i]->key, key)) {
                return schema->elements[i];
            }
        }
    }
    return NULL;
}

uint64_t calcDocumentSize(documentSchema* schema) {
    uint64_t size = sizeof(documentHeader);
    for (uint64_t i = 0; i < schema->length; i++) {
        size += sizeof(uint8_t) + 13 * sizeof(char); // type и key
        element* el = schema->elements[i];
        switch (el->type) {
            case TYPE_INT:
                size += sizeof(int32_t);
                break;
            case TYPE_DOUBLE:
                size += sizeof(double);
                break;
            case TYPE_BOOLEAN:
                size += sizeof(uint8_t);
                break;
            case TYPE_STRING:
                size += sizeof(uint32_t); // размер строки
                size += sizeof(char) * el->stringValue.size; // сама строка
                break;
        }
    }
    return size;
}