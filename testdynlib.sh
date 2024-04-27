#!/bin/bash

cleanup() {
    jobs -p | xargs kill
}

trap cleanup EXIT

gcc hello.c -o hello
gcc -shared -fpic dummylib.c -o dummylib.so
gcc -shared -fpic testdynlib.c -o testdynlib.so

DISABLE_QUIT=1 ./hello < /dev/null &
echo -n
sudo ./gdb-dlopen.sh
wait