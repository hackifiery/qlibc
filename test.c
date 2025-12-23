#include "stdio.h"
#include "unistd.h"

void _start(){
    printf("Hello, world!");
    _exit(0);
}