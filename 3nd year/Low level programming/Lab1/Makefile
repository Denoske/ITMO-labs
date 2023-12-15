CFLAGS = -mno-ms-bitfields
CC = gcc

SRC_PATH = ./src
TESTS_PATH = $(SRC_PATH)/tests
UTILS_PATH = $(SRC_PATH)/utils
ZGDB_PATH = $(SRC_PATH)/zgdb
LIB_SOURCE_FILES = $(UTILS_PATH)/optional.c $(ZGDB_PATH)/format.c $(ZGDB_PATH)/list.c $(ZGDB_PATH)/document.c $(ZGDB_PATH)/element.c $(ZGDB_PATH)/schema.c $(ZGDB_PATH)/query.c $(ZGDB_PATH)/condition.c $(ZGDB_PATH)/iterator.c

all: demo run_tests

demo: $(LIB_SOURCE_FILES) $(SRC_PATH)/demo.c
	$(CC) $(CFLAGS) $(LIB_SOURCE_FILES) $(SRC_PATH)/demo.c -o demo

run_tests: $(LIB_SOURCE_FILES) $(TESTS_PATH)/test.c $(SRC_PATH)/run_tests.c
	$(CC) $(CFLAGS) $(LIB_SOURCE_FILES) $(TESTS_PATH)/test.c $(SRC_PATH)/run_tests.c -o run_tests

clean:
	rm -rf demo
	rm -rf run_tests

.PHONY: all clean