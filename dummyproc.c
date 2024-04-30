#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char libname[] = "dummylib.so";
    char libpath[sizeof(libname) + 2];

    snprintf(libpath, sizeof(libpath), "./%s", libname);

    void *libaddr = dlopen(libpath, RTLD_LAZY);
    if (!libaddr)
    {
        fprintf(stderr, "Failed to load library. Are you in the same directory as '%s'?\n", libname);
        return 1;
    }

    fprintf(stdout, "Waiting for testdynlib from gdb...\n");

    if (getenv("DISABLE_QUIT") == NULL)
    {
        fprintf(stdout, "Press enter to quit...\n");
        getchar();
    }
    else
    {
        fprintf(stdout, "Quit on enter disabled by DISABLE_QUIT, use Ctrl+C to quit\n");

        while (1)
        {
            getchar();
        }
    }

    return 0;
}