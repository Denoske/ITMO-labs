#include "my_tests.h"
#include <stdio.h>

int main(void){
	printf("test1 Simple alloc:\n");
	test1();
	printf("--------------------------------------------\n");

	printf("test2 Free one block:\n");
	test2();
	printf("--------------------------------------------\n");

	printf("test3 Free two blocks\n");
	test3();
	printf("--------------------------------------------\n");

	printf("test4 Expand a drained memory block:\n");
	test4();
	printf("--------------------------------------------\n");

	printf("test5 Unable to expand the drained block, so allocate a new one:\n");
	test5();
	printf("--------------------------------------------\n");


	return 0;
}
