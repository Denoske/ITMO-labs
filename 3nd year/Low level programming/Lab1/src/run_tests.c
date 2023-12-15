#include <stddef.h>

#include "zgdb/query_public.h"
#include "tests/test.h"

int main(int argc, char** argv) {
    // Создаём корень и запрос на его вставку:
    documentSchema* rootSchema = createSchema("root");
    query* insertRoot = createInsertQuery(NULL, rootSchema, NULL);

    // Создаём ребёнка:
    documentSchema* childSchema = createSchema("child");
    addElementToSchema(childSchema, intElement("childInt", 1001));
    addElementToSchema(childSchema, doubleElement("childDouble", 3.1415));
    addElementToSchema(childSchema, booleanElement("childBool", true));
    addElementToSchema(childSchema, stringElement("childString", "THIS IS TEST DOCUMENT!"));

    // Создаём альтернативного ребёнка:
    documentSchema* altChildSchema = createSchema("child");
    addElementToSchema(altChildSchema, intElement("childInt", 101));
    addElementToSchema(altChildSchema, doubleElement("childDouble", 3.1415));
    addElementToSchema(altChildSchema, doubleElement("childBool", true));
    addElementToSchema(altChildSchema, stringElement("childString", "THIS IS TEST DOCUMENT!"));

    // Создаём элементы для обновления ребёнка:
    documentSchema* newElements = createElements();
    addElementToSchema(childSchema, booleanElement("childBool", false));

    // Создаём условие для выбора детей при обновлении:
    condition* cond = condEqual(intElement("childInt", 1001));

    // Создаём запрос на вставку ребёнка:
    query* insertChild = createInsertQuery("root", NULL, NULL);
    addNestedQuery(insertChild, createInsertQuery(NULL, childSchema, NULL));
    // Создаём запрос на вставку альтернативного ребёнка:
    query* insertAltChild = createInsertQuery("root", NULL, NULL);
    addNestedQuery(insertChild, createInsertQuery(NULL, altChildSchema, NULL));
    // Создаём запрос на чтение ребёнка:
    query* selectChild = createSelectQuery("root", NULL);
    addNestedQuery(selectChild, createSelectQuery("child", NULL));
    // Создаём запрос на обновление ребёнка:
    query* updateChild = createUpdateQuery("root", NULL, NULL);
    addNestedQuery(updateChild, createUpdateQuery("child", newElements, cond));

    // Запускаем тесты:
    //testInsertTime("test_insert", insertRoot, insertChild);
    testSelectTime("test_select", insertRoot, insertChild, selectChild);
    //testUpdateTime("test_update", insertRoot, insertChild, insertAltChild, updateChild);
    //testFileSize("test_size", insertRoot, insertChild);

    destroySchema(rootSchema);
    destroySchema(childSchema);
    destroySchema(altChildSchema);
    destroySchema(newElements);
    destroyQuery(insertRoot);
    destroyQuery(insertChild);
    destroyQuery(insertAltChild);
    destroyQuery(selectChild);
    destroyQuery(updateChild);

    return 0;
}

