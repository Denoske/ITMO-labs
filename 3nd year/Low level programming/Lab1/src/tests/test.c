#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "../zgdb/format.h"
#include "../zgdb/query_public.h"
#include "test.h"

void testInsertTime(const char* fileName, query* insertRoot, query* insertChild) {
    printf("[ TEST INSERT TIME ]\n");
    // Создаём файл:
    zgdbFile* file = createFile(fileName);
    if (!file) {
        printf("Error\n");
        exit(-1);
    }
    // Пробуем вставить корень:
    bool error = false;
    if (!executeInsert(file, &error, insertRoot)) {
        exit(-1);
    }
    // Пробуем вставить 50000 детей:
    for (int i = 1; i <= 50000; i++) {
        struct timeval start, end;
        gettimeofday(&start, NULL);
        bool result = executeInsert(file, &error, insertChild);
        gettimeofday(&end, NULL);
        if (!result) {
            exit(-1);
        }
        printf("%d\t%lu\n", i, (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec);
    }
    closeFile(file);
}

void testSelectTime(const char* fileName, query* insertRoot, query* insertChild, query* selectChild) {
    printf("[ TEST SELECT TIME ]\n");
    // Создаём файл:
    zgdbFile* file = createFile(fileName);
    if (!file) {
        printf("Error\n");
        exit(-1);
    }
    // Пробуем вставить корень:
    bool error = false;
    if (!executeInsert(file, &error, insertRoot)) {
        exit(-1);
    }
    // Пробуем вставить и вывести 5000 детей:
    for (int i = 1; i <= 5000; i++) {
        bool result = executeInsert(file, &error, insertChild);
        if (!result) {
            exit(-1);
        }
        struct timeval start, end;
        iterator* it;
        gettimeofday(&start, NULL);
        result = executeSelect(file, &error, &it, selectChild);
        gettimeofday(&end, NULL);
        if (!result) {
            exit(-1);
        }
        destroyIterator(it);
        printf("%d\t%lu\n", i, (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec);
    }
    closeFile(file);
}

void testUpdateTime(const char* fileName, query* insertRoot, query* insertChild, query* insertAltChild, query* updateChild) {
    printf("[ TEST UPDATE TIME ]\n");
    // Создаём файл:
    zgdbFile* file = createFile(fileName);
    if (!file) {
        printf("Error\n");
        exit(-1);
    }
    // Пробуем вставить корень:
    bool error = false;
    if (!executeInsert(file, &error, insertRoot)) {
        exit(-1);
    }
    // Пробуем вставить 2500 детей каждого типа и обновить только детей первого типа:
    for (int i = 1; i <= 5000; i++) {
        bool result = executeInsert(file, &error, i % 2 ? insertChild : insertAltChild);
        if (!result) {
            exit(-1);
        }
        struct timeval start, end;
        gettimeofday(&start, NULL);
        result = executeUpdate(file, &error, updateChild);
        gettimeofday(&end, NULL);
        if (!result) {
            exit(-1);
        }
        printf("%d\t%lu\n", i, (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec);
    }
    closeFile(file);
}

void testFileSize(const char* fileName, query* insertRoot, query* insertChild) {
    printf("[ TEST FILE SIZE ]\n");
    // Создаём файл:
    zgdbFile* file = createFile(fileName);
    if (!file) {
        printf("Error\n");
        exit(-1);
    }
    // Пробуем вставить корень:
    bool error = false;
    if (!executeInsert(file, &error, insertRoot)) {
        exit(-1);
    }
    // Пробуем вставить 50000 детей:
    for (int i = 1; i <= 50000; i++) {
        bool result = executeInsert(file, &error, insertChild);
        if (!result) {
            exit(-1);
        }
        printf("%d\t%lu\n", i, file->header.fileSize);
    }
    closeFile(file);
}