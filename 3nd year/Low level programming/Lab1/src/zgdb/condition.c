#include <string.h>
#include <malloc.h>

#include "format.h"
#include "condition.h"
#include "element.h"
#include "schema.h"
#include "query.h"

condition* createCondition(operationType type, void* operand1, void* operand2) {
    condition* cond = NULL;
    if ((cond = malloc(sizeof(condition)))) {
        cond->isMet = false;
        cond->opType = type;
        cond->cond1 = operand1;
        cond->cond2 = operand2;
    }
    return cond;
}

condition* condEqual(element* el) {
    return el ? createCondition(OP_EQ, el, NULL) : NULL;
}

condition* condNotEqual(element* el) {
    return el ? createCondition(OP_NEQ, el, NULL) : NULL;
}

condition* condGreater(element* el) {
    return el ? createCondition(OP_GT, el, NULL) : NULL;
}

condition* condGreaterOrEqual(element* el) {
    return el ? createCondition(OP_GTE, el, NULL) : NULL;
}

condition* condLess(element* el) {
    return el ? createCondition(OP_LE, el, NULL) : NULL;
}

condition* condLessOrEqual(element* el) {
    return el ? createCondition(OP_LEE, el, NULL) : NULL;
}

condition* condAnd(condition* cond1, condition* cond2) {
    return (cond1 && cond2) ? createCondition(OP_AND, cond1, cond2) : NULL;
}

condition* condOr(condition* cond1, condition* cond2) {
    return (cond1 && cond2) ? createCondition(OP_OR, cond1, cond2) : NULL;
}

condition* condNot(condition* cond) {
    return cond ? createCondition(OP_NOT, cond, NULL) : NULL;
}

void destroyCondition(condition* cond) {
    if (cond) {
        if (cond->opType >= OP_AND) {
            destroyCondition(cond->cond1);
            destroyCondition(cond->cond2);
        } else {
            destroyElement(cond->el);
        }
        free(cond);
    }
}

void resetCondition(condition* cond) {
    if (cond) {
        cond->isMet = false;
        if (cond->opType >= OP_AND) {
            resetCondition(cond->cond1);
            resetCondition(cond->cond2);
        }
    }
}

bool checkCondition(element* el, condition* cond) {
    // Если условие уже проверялось, то нет смысла проверять его ещё раз:
    if (cond->isMet) {
        return true;
    }
    // Если у элементов не совпадает тип или ключ, то нет смысла их сравнивать:
    if (cond->opType < OP_AND && (el->type != cond->el->type || strcmp(el->key, cond->el->key) != 0)) {
        return false;
    }
    // Проверяем условие в зависимости от типа операции:
    bool result;
    switch (cond->opType) {
        case OP_EQ:
            result = compare(el, cond->el) == 0;
            break;
        case OP_NEQ:
            result = compare(el, cond->el) != 0;
            break;
        case OP_GT:
            result = compare(el, cond->el) > 0;
            break;
        case OP_GTE:
            result = compare(el, cond->el) >= 0;
            break;
        case OP_LE:
            result = compare(el, cond->el) < 0;
            break;
        case OP_LEE:
            result = compare(el, cond->el) <= 0;
            break;
        case OP_AND:
            result = checkCondition(el, cond->cond1) & checkCondition(el, cond->cond2);
            break;
        case OP_OR:
            result = checkCondition(el, cond->cond1) | checkCondition(el, cond->cond2);
            break;
        case OP_NOT:
            result = !checkCondition(el, cond->cond1);
            break;
    }
    // Если условие выполнилось, то записываем в него эту информацию:
    if (result) {
        cond->isMet = true;
    }
    return result;
}

bool checkDocument(zgdbFile* file, uint64_t indexNumber, query* q) {
    // Если название схемы не указано, то это говорит о том, что документ ещё не создан. Возвращаем true:
    if (q->type == INSERT_QUERY && !q->schemaName) {
        return true;
    }
    // Если документ существует, то проверяем его:
    document* doc = readDocument(file, indexNumber);
    if (doc) {
        if (!strcmp(q->schemaName, doc->header.schemaName)) {
            // Проверяем новые значения на соответствие схеме (если они переданы):
            if (q->newValues) {
                // Если хотя бы один ключ из списка новых элементов отсутствует в схеме документа, возвращаем false:
                for (uint64_t i = 0; i < q->newValues->length; i++) {
                    if (!getElementFromSchema(doc->schema, q->newValues->elements[i]->key)) {
                        destroyDocument(doc);
                        return false;
                    }
                }
            }
            // Проверяем условие:
            if (q->cond) {
                for (uint64_t i = 0; i < doc->schema->length; i++) {
                    checkCondition(doc->schema->elements[i], q->cond);
                }
            }
            destroyDocument(doc);
            // Если условие не передано, возвращаем true; иначе - результат проверки:
            return !q->cond || q->cond->isMet;
        }
        destroyDocument(doc);
    }
    return false;
}

int32_t compare(element* el1, element* el2) {
    switch (el1->type) {
        case TYPE_INT:
            return (el1->integerValue > el2->integerValue) - (el1->integerValue < el2->integerValue);
        case TYPE_DOUBLE:
            return (el1->doubleValue > el2->doubleValue) - (el1->doubleValue < el2->doubleValue);
        case TYPE_BOOLEAN:
            return el1->booleanValue - el2->booleanValue;
        case TYPE_STRING:
            return strcmp(el1->stringValue.data, el2->stringValue.data);
    }
    return 0;
}