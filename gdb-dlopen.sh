#!/bin/bash

LIB_PATH=$(pwd)/testdynlib.so
PROCID=$(pgrep hello)

# Verify permissions
if [[ "$EUID" -ne 0 ]]; then
    echo "Please run as root"
    exit 1
fi

# Check if library exists
if [ ! -f "$LIB_PATH" ]; then
    echo "Library not found"
    exit 1
fi

# Check if library is already loaded (dont print anything)
if lsof -p $PROCID 2> /dev/null | grep -q $LIB_PATH; then
    echo "Library is already loaded"
    exit 1
fi

echo "Library path: $LIB_PATH"

# Check if the process is running
if [ -z "$PROCID" ]; then
    echo "Process is not running"
    exit 1
fi

echo "Process ID: $PROCID"

gdb -n --batch -ex "attach $PROCID" -ex "call ((void * (*) (const char*, int)) dlopen)(\"$LIB_PATH\", 1)" -ex "detach"