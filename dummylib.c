#include <stdio.h>

__attribute__((constructor)) void init()
{
    fprintf(stdout, "dummylib loaded...\n");
}