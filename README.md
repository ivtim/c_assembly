# c_assembly

An example of building a program with gcc in the following ways: 

- Executable object files
- Static library
- Dynamic library

## Simple

Building relocatable ELF object files (source: main.c quick_sort.c and utils.c)

```sh
mkdir obj
gcc -c main.c -o obj/main.o
gcc -c quick_sort.c -o obj/quick_sort.o
gcc -c utils.c -o obj/utils.o
```

Linking generated relocatable object files in order to produce an executable ELF object file

```sh
mkdir out
gcc obj/main.c obj/quick_sort.o obj/utils.o -o out/a.out
```

## Static library

A static library is simply a Unix archive made from the relocatable object files.
Such a library is usually linked together with other object files to form an
executable object file.

Compiling a number of sources to their corresponding relocatable object files.

```sh
mkdir obj
gcc -c main.c -o obj/main.o
gcc -c quick_sort.c -o obj/quick_sort.o
gcc -c utils.c -o obj/utils.o
```

Creation single archive for object files
```sh
mkdir lib
ar crs libsort.a obj/quick_sort.o obj/utils.o
mv libsort.a lib
```

Compiling and linking with lib
```sh
gcc main.o -L lib -l sort -lm -o a.out
```

## Dynamic library

Dynamic libraries are another way to produce libraries for reuse. As their name implies, unlike the static libraries, dynamic libraries are not
part of the final executable itself. Instead, they should be loaded and brought in
while loading a process for execution.

Building object files with -fPIC option and shared library.

```sh
mkdir obj
gcc -c quick_sort.c -fPIC -o obj/quick_sort.o
gcc -c utils.c -fPIC -o obj/utils.o

gcc -shared obj/quick_sort.o obj/utils.o -o libsort.so
mkdir lib
mv libsort.so lib
```

Add environment variable for search
the specified paths for the required shared libraries.

```sh
export LD_LIBRARY_PATH=/.../lib
```

Linking with the built shared object file.
```sh
mkdir out
gcc -c main.c -o obj/main.o
gcc obj/main.o -L lib -lsort -lm -o a.out
```

## Manual loading of shared libraries

Shared object files can also be loaded and used in a different way, in which they
are not loaded automatically by the loader program.

functions dlopen and dlsym load the shared object file and then find the symbol
quick_sort in it. The function dlsym returns a function pointer,
which can be used to invoke the target function.

Compiling main_manual.c.
```sh
gcc main_manual.c -ldl -o a_manual.out
```
