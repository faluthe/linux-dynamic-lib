#include <stdio.h>
#include <stdlib.h>

__attribute__((constructor)) void init()
{
    FILE *log_file = fopen("./testdynlib.log", "a");

    fprintf(log_file, "Library has been loaded!\n");
    fprintf(stdout, "testdynlib loaded...\n");

    fclose(log_file);
}