#include <stdio.h>

const char *dummylib_function()
{
    fprintf(stdout, "dummylib_function called!\n");
    return "Hi from dummylib!";
}

__attribute__((constructor)) void init()
{
    fprintf(stdout, "dummylib loaded...\n");
}