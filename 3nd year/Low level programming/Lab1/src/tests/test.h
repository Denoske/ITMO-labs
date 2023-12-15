#ifndef _TEST_H_
#define _TEST_H_

void testInsertTime(const char* fileName, query* insertRoot, query* insertChild);

void testSelectTime(const char* fileName, query* insertRoot, query* insertChild, query* selectChild);

void testUpdateTime(const char* fileName, query* insertRoot, query* insertChild, query* insertAltChild, query* updateChild);

void testFileSize(const char* fileName, query* insertRoot, query* insertChild);

#endif