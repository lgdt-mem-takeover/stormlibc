# StormC BuildSystem
The StormC BuildSystem is designed to eliminate build-system friction.
It is written entirely in C, with no third-party dependencies. The configuration file is also C code, so you can write C that compiles C. It is using POSIX / syscalls, so using it on Windows will most likely not work without a few changes. I am planning on abstracting the POSIX syscalls into cross-platform ( Windows/Linux) calls, but I currently don't have time and do not use Windows almost ever. There are other functionalities that I'll add as I keep building it. At the end of this README I'll share a list of future functionalities.


**NOTE: Added Support for C++ Recently. Read at the bottom**
***DISCLAIMER: Not everything is documented yet, only major features.***

## Commands
- stormc init
- stormc build
- stormc build run
- stormc run
- stormc embed *target_file dest_file.h*
- stormc ctags *path_to_directory*

## Details
### stormc build, stormc build run, stormc run
These commands work in conjunction with the ***scbuild.h*** file, which is generated
by running the ***stormc init*** command.
Example
```
$ stormc init
$ ls
scbuild.c
```

The file ***scbuild.c*** contains the following
```
#include <storm/scbuild.h>

int main(int argc, char *argv[])

{
	build.in = make_string("main.c");
	build.out = make_string("main");
	build.compiler = make_string("gcc");

	SET_FLAGS(WALL, WPEDANTIC, ALLSAN, STD_C99, OPTIM_1);

	stormc_build(argc, argv);`
}
```
The commands **stormc build**, **stormc build run** and **stormc run** work with the **scbuild.c** file. The **build** command will compile **scbuild.c** and pass an argument to it to compile **main.c** (or whatever **build.in** is set to) and emit a binary, which has the name of the string passed to **build.out**.

The API is minimal such that the user doesn't have to bother with types, handling memory or anything other than pure scripting, while still writing C, not some other programming language or scripting language.

## The scbuild.c file
The **scbuild.c** file uses **scbuild.h** to import macros, types and functions into it, and emit the code to compile itself and the target file (passed to **build.in**).
### The following commands are available
#### All commands are strings, except for the flags which are all enums.
- build.in - Sets the name of the target file that will be compiled (eg: "main.c").
- build.out - Sets the name of the binary (out) file (eg: "main").
- build.compiler - Sets the name of the compiler (currently only gcc and clang)
- SET_FLAGS - Sets flags to pass to the compiler ( **flags are all enums** ).
- SET_LINK_PATH - Sets the file path ( directory ) to include for linking (eg: -I . for current directory)
- SET_LINKED_FILES - Sets the libraries to be linked to the project (eg: "-l*library_name*")

## The *stormc embed* command
With the **stormc embed** command, you can take any file and spit a binary ( hex ) into a header (.h) file, two variables, an array of hex values, representing each byte in that file, and a variable that stores the number of bytes in that embedded file.
Example
```
$ stormc embed token.png token.h
token_png
cat token.h | less
const unsigned char token_png[] = {
        0x89,   0x50,   0x4e,   0x47,   0x0d,   0x0a,   0x1a,   0x0a,   0x00,   0x00,   0x00,   0x0d,
        0x49,   0x48,   0x44,   0x52,   0x00,   0x00,   0x01,   0x00,   0x00,   0x00,   0x01,   0x00,
        0x08,   0x06,   0x00,   0x00,   0x00,   0x5c,   0x72,   0xa8,   0x66,   0x00,   0x00,   0x20,
        ...
const unsigned int token_png_len = 99557;

```
As you can see above, the output variables for a *file_name.extension* will be.
```
const unsigned char file_name_extension[] = {...};

const unsigned int file_name_extension = number_of_bytes;
```
## More examples
### Example stormc build run
```
$ cat main.c
#include <stdio.h>

int main(void)
{
	printf("Hello StormC\n");
}
$ stormc build run
[BUILDING] main.c -> main
[BUILD COMPLETE] 73.69 ms
[RUNNING] main
Hello StormC
```
Let's remove <stdio.h> so we can get an error
```
$ cat main.c

int main(void)
{
	printf("Hello StormC\n");
}

$[BUILDING] main.c -> main
main.c:4:2: error: call to undeclared library function 'printf' with type 'int (const char *, ...)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
    4 |         printf("Hello StormC\n");
      |         ^
main.c:4:2: note: include the header <stdio.h> or explicitly provide a declaration for 'printf'
1 error generated.
[BUILD FAILED]
failed command clang (exit code 1)
[BUIILD RUN]Failed to run system()
Status: 1
```

## Future functionalities ( in no specific order )
- Cross platform (with Windows ) integration
- Dump to stdout the commands / flags passed in (for debugging any errors / potential silent failures ).
- Github interop ( pulling github repos and automatically regenerate scbuild.c with any needed includes / flags ).
- C in-file metaprogramming and pragmas.
- Setting up configuration profiles for even quicker bootstrapping.
- Self C compiler integration.

## Currently available compiler flags (gcc / clang)
### Optimization
```
- 	OPTIM_0 : -O0
-	OPTIM_1 : -O1
-	OPTIM_2 : -O2
-	OPTIM_3 : -O3
```
### Architecture
```
-	MARCH_SSE 		: -msse
-	MARCH_SSE2		: -msse2
-	MARCH_SSE3 		: -msse3
-	MARCH_SSE4		: -msse4
-	MARCH_SSE42	    : -msse4.2
-	MARCH_AVX1 	    : -march_avx
-	MARCH_AVX2 	    : -march_avx2
-	MARCH_NATIVE    : -march=native
```
### Language Standard
```
-	STD_C89 : -std=c89
-	STD_C99 : -std=c99
-	STD_C2X : -std=c2x
```

### Sanitizers
```
-	ASAN    : -fsanitize=address
-	LSAN    : -fsanitize=leak
-	UBSAN 	: -fsanitize=undefined
-	TSAN 	: -fsanitize=thread
-	MEMSAN 	: -fsanitize=memory
-	ALLSAN 	: -fsanitize=address,leak,undefined
```

### Warnings
```
-	WALL 		: -Wall
-	WEXTRA 		: -Wextra
-	WERROR 		: -Werror
-	WPEDANTIC   : -Wpedantic
```

### OpenMP
```
-   OMP : "-fopenmp"
```



## C++ Support
To use the build system with c++, you can simply use it like this
```
#include <storm/scbuild.h>

int main(int argc, char *argv[]) {
    build.in = STR("main.cpp");
    build.out = STR("main");
    build.compiler = STR("g++");

    SET_FLAGS(STD_CPP11, OPTIM_2, WALL);

    stormc_build(argc, argv);
}
```

## C++ Language Standard flags
```
	STD_CPP98 : "-std=c++98"
	STD_CPP03 : "-std=c++03"
	STD_CPP11 : "-std=c++11"
	STD_CPP14 : "-std=c++14"
	STD_CPP17 : "-std=c++17"
	STD_CPP20 : "-std=c++20"
	STD_CPP23 : "-std=c++23"
```
