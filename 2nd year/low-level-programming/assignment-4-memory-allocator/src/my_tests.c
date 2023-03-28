#include "my_tests.h"
#include <stdlib.h>

#define SIZE_OF_HEAD 4096
#define VALUE_DEFAULT 3000
#define SIZE_OF_BLOCK 1024
#define TEST_HEAP_SIZE 8192
#define HEAP_FAILED "test failed. Heap is not initialized\n"
#define MEMORY_FAILED "test failed. Memory is not allocated.\n"
#define HEAP_ALLOC "Heap after alloc:\n"
#define HEAP_AFTER_INIT "Heap after init\n"


static struct block_header* block_get_header(void* contents) {
  return (struct block_header*) (((uint8_t*)contents)-offsetof(struct block_header, contents));
}

void test1(void) {
    void* test_heap = heap_init(SIZE_OF_HEAD);
    if (test_heap == NULL) {
        fprintf(stderr, HEAP_FAILED);
        abort();
    }
    printf(HEAP_AFTER_INIT);
    debug_heap(stdout, test_heap);
    void* allocate_memory = _malloc(VALUE_DEFAULT);
    if (allocate_memory == NULL){
        fprintf(stderr, MEMORY_FAILED);
        abort();
    }
    printf(HEAP_ALLOC);
    debug_heap(stdout, test_heap);
    _free(allocate_memory);
    printf("Heap after free mem\n");
    debug_heap(stdout, test_heap);
    munmap(test_heap, size_from_capacity((block_capacity) {.bytes = SIZE_OF_HEAD}).bytes);
    fprintf(stdout, "test1 is successful\n");
}

void test2(void) {
    void* test_heap = heap_init(SIZE_OF_HEAD);
    if (test_heap == NULL){
        fprintf(stderr, HEAP_FAILED);
        abort();
    }
    printf(HEAP_AFTER_INIT);
    debug_heap(stdout, test_heap);
    void* allocate_memory1 = _malloc(SIZE_OF_BLOCK);
    void* allocate_memory2 = _malloc(SIZE_OF_BLOCK);
    if (allocate_memory1 == NULL || allocate_memory2 == NULL){
        fprintf(stderr, MEMORY_FAILED);
        abort();
    }
    printf(HEAP_ALLOC);
    debug_heap(stdout, test_heap);
    _free(allocate_memory1);
    if ( allocate_memory2 == NULL ){
        fprintf(stderr, "test failed. Release of the first damaged the second.\n");
        abort();
    }
    printf("Heap after free mem\n");
    debug_heap(stdout, test_heap);
    _free(allocate_memory2);
    munmap(test_heap, size_from_capacity((block_capacity) {.bytes = SIZE_OF_HEAD}).bytes);
    fprintf(stdout, "test2 is successful\n");
}

void test3(void) {
    void* test_heap = heap_init(SIZE_OF_HEAD);
    if (test_heap == NULL){
        fprintf(stderr, HEAP_FAILED);
        abort();
    }
    printf(HEAP_AFTER_INIT);
    debug_heap(stdout, test_heap);
    void* allocate_memory1 = _malloc(SIZE_OF_BLOCK);
    void* allocate_memory2 = _malloc(SIZE_OF_BLOCK);
    void* allocate_memory3 = _malloc(SIZE_OF_BLOCK);
    if ( allocate_memory1 == NULL ){
        fprintf(stderr, "test failed. First memory is not allocated.\n");
        abort();
    }
    if ( allocate_memory2 == NULL || allocate_memory3 == NULL){
        fprintf(stderr, "test failed. Second memory is not allocated.\n");
        abort();
    }
    if ( allocate_memory3 == NULL){
        fprintf(stderr, "test failed. Third memory is not allocated.\n");
        abort();   
    }
    printf(HEAP_ALLOC);
    debug_heap(stdout, test_heap);
    _free(allocate_memory1);
    _free(allocate_memory3);
    if ( allocate_memory2 == NULL ){
        fprintf(stderr, "test failed. Release of the first damaged the second.\n");
        abort();      
    }
    printf("Heap after free mem\n");
    debug_heap(stdout, test_heap);
    munmap(test_heap, size_from_capacity((block_capacity) {.bytes = SIZE_OF_HEAD}).bytes);
    fprintf(stdout, "test3 is successful\n");
}

void test4(void) {
    void* test_heap = heap_init(1);
    if ( test_heap == NULL ){
        fprintf(stderr, HEAP_FAILED);
         abort();
    }
    printf(HEAP_AFTER_INIT);
    debug_heap(stdout, test_heap);
    void* allocate_memory1 = _malloc(TEST_HEAP_SIZE);
    void* allocate_memory2 = _malloc(16384);
    if (allocate_memory1 == NULL){
        fprintf(stderr, "test failed. First memory is not allocated.\n");
        abort();
    }
    if (allocate_memory2 == NULL){
        fprintf(stderr, "test failed. Second memory is not allocated.\n");
        abort();
    }
    printf(HEAP_ALLOC);
    debug_heap(stdout, test_heap);
    
    struct block_header* header1 = block_get_header(allocate_memory1);
    struct block_header* header2 = block_get_header(allocate_memory2);
    if ( header1 == NULL || header1->next != header2 ){
        fprintf(stderr, "test failed. Headers are not linked.\n");
        abort();
    }
    munmap(test_heap, (int) (header1->capacity.bytes + header2->capacity.bytes + ( (struct block_header*) test_heap)->capacity.bytes ));
    fprintf(stdout, "test4 is successful\n");
}


void test5(void) {
    void* test_heap = heap_init(1);
    if (test_heap == NULL){
        fprintf(stderr, "test failed. Heap is not initialized.\n");
        abort();
    }
    printf(HEAP_AFTER_INIT);
    debug_heap(stdout, test_heap);
    void* allocate_memory1 = _malloc(TEST_HEAP_SIZE);
    if ( allocate_memory1 == NULL ){
        fprintf(stderr, "test failed. First memory is not allocated.\n");
        abort();
    }
    struct block_header* header1 = block_get_header(allocate_memory1);
    if ( header1 == NULL ){
        fprintf(stderr, "test failed. Header is not find.\n");
        abort();
    }
    printf(HEAP_ALLOC);
    debug_heap(stdout, test_heap);
    void* region = mmap( header1->contents + header1->capacity.bytes, REGION_MIN_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0 );
    void* allocate_memory2 = _malloc(TEST_HEAP_SIZE);
    struct block_header* header2 = block_get_header(allocate_memory2);
    if ( allocate_memory2 == NULL){
        fprintf(stderr, "test failed. Second memory is not allocated\n");
        abort();
    }
    printf("Heap after second malloc\n");
    debug_heap(stdout, test_heap);
    _free(allocate_memory1);
    _free(allocate_memory2);
    printf("Heap after realising\n");
    debug_heap(stdout, test_heap);
    munmap(region, size_from_capacity((block_capacity) {.bytes = REGION_MIN_SIZE}).bytes);
    munmap(test_heap, size_from_capacity((block_capacity) {.bytes =  (int) (header1->capacity.bytes + header2->capacity.bytes + ( (struct block_header*) test_heap)->capacity.bytes)}).bytes);
    fprintf(stdout, "test5 is successful\n");
}
