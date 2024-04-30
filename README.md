# Linux Dynamic Libraries

This program will dynamically load a library using `dlopen`, normally and forcibly through use of the GDB debugger.

See an example in action by running:
```bash
bash testdynlib-run.sh
```

See below for instructions on compiling and using individual components.

## Components

### **dummyproc**
Loads `dummylib.so` at runtime and waits for input.

### **dummylib**
Prints a message to `stdout` on load using the *GNU C* `__attribute__((constructor))` syntax to mark the `init()` function. 

`dummylib_function()` returns a string to the caller and is exported to the binary's symbol table. This is a default behavior for functions in a lib that are not marked with `__attribute__((visibility("hidden")))`.

### **testdynlib**
Loaded forcibly at runtime into **dummyproc** by `gdb-dlopen.sh`. Outputs initial message to `stdout` and a log file, `testdynlib.log`. All further log messages are sent to the log file and handled externally, as `stdout` useage in practice is unsafe. 

Prints the result of a `dummylib_function` call by getting a pointer to the function dynamically with a handle to **dummylib** from `dlopen` and `dlsym`.

### **gdb-dlopen**
Attaches GDB debugger to `dummyproc` and *"forcibly"* calls `dlopen` to load **testdynlib**. 

Upon reception of a `SIGNIT` (Ctrl+C) the GDB debugger will call `dlclose` to unload **testdynlib**.

### **testdynlib-run**
Builds project and runs everything. 

Libraries are compiled with `gcc -shared -fpic [...] -o [...]`, `-fpic` is used to generate *Platform Independent Code*. A basic understanding of *PIC*: normally programs address objects by absolute address, thanks to virtual memory they are able to recieve the addresses that the ask for. However, because libaries are loaded within the address space of their parent programs they aren't garunteed addresses. This means the library must address objects relativley, hence *Platform Independent Code*.

## Compiling and Using
Read the [testdynlib-run](#testdynlib-run) section for more information about `-fpic`.

Compile with:
```bash
gcc dummyproc.c -o dummyproc
gcc -shared -fpic dummylib.c -o dummylib.so
gcc -shared -fpic testdynlib.c -o testdynlib.so
```

Then, run `dummyproc`:
```bash
./dummyproc
```

In another terminal, load `testdynlib` into `dummyproc` with:
```bash
sudo bash gdb-dlopen.sh
```

To unload, press Ctrl+C.