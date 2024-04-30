#!/bin/bash

cleanup() {
    jobs -p | xargs kill
}

trap cleanup EXIT

gcc dummyproc.c -o dummyproc
gcc -shared -fpic dummylib.c -o dummylib.so
gcc -shared -fpic testdynlib.c -o testdynlib.so

DISABLE_QUIT=1 ./dummyproc < /dev/null &
echo -n
sudo ./gdb-dlopen.sh
wait