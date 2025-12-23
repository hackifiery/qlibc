# qlibc: minimalist c standard library
`qlibc` is a very, very tiny c std library I made out of curiosity. It currently defines a very small subset of c headers and functions, some of which I used cheap workarounds to achcieve (e.g. `free` just leaks memory to simulate an actual `free`). It barely manages to run a bubbesort and print the result.
## Building
To build qlibc, just run `make all` and it'll give you a `.a` file to link against. If you want to run a file using qlibc, compile it and link it to qlibc. **and make sure to disable the standard library if you have another c library (like glibc) installed**.
```
gcc program.c -o program.o
gcc -nostdlib -nodefaultlibs -ffreestanding -I include program.o -L . -l qlibc -o program
```
## Note about the `main` function
qlibc is so minimal that having a main function will cause a segementation fault; use `void _start()` instead. If you `return x` at the end of your `main` function, replace that with `_exit(x)` (since a `void` can't return a number).
