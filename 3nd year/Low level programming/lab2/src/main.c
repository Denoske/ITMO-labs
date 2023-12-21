#include "y.tab.h"
#include "stdio.h"

int main() {
    fprintf(stdout, "print X-Path query:\n");
    yyparse();
    return 0;
}
