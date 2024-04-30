#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

__attribute__((constructor)) void init()
{
    FILE *log_file = fopen("./testdynlib.log", "w");

    fprintf(log_file, "Library has been loaded!\n");
    fprintf(stdout, "testdynlib loaded...\n");

    void *dummylib_handle = dlopen("./dummylib.so", RTLD_NOLOAD | RTLD_NOW);
    if (!dummylib_handle)
    {
        fprintf(log_file, "Failed to load dummylib.so\n");
        return;
    }

    fprintf(log_file, "dummylib.so loaded at %p\n", dummylib_handle);

    const char *(*dummylib_function)() = dlsym(dummylib_handle, "dummylib_function");
    if (!dummylib_function)
    {
        fprintf(log_file, "Failed to load dummylib_function\n");
        return;
    }

    fprintf(log_file, "dummylib_function loaded at %p\n", dummylib_function);
    fprintf(log_file, "dummylib_function returned: %s\n", dummylib_function());

    fclose(log_file);
    dlclose(dummylib_handle);
}

__attribute__((destructor)) void unload()
{
    FILE *log_file = fopen("./testdynlib.log", "a");

    fprintf(stdout, "testdynlib unloaded...\n");
    fprintf(log_file, "Library has been unloaded!\n");

    fclose(log_file);
}