#include "unistd.h"

/* write(fd, buf, count) */
ssize_t write(int fd, const void *buf, size_t count) {
    long ret;
    asm volatile (
        "syscall"
        : "=a"(ret)
        : "a"(1),        /* SYS_write */
          "D"(fd),
          "S"(buf),
          "d"(count)
        : "rcx", "r11", "memory"
    );
    return ret;
}

/* very small sbrk using brk syscall */
static char *heap_end;

void *sbrk(intptr_t increment) {
    char *prev = heap_end;
    char *new_end = heap_end + increment;
    long ret;

    asm volatile (
        "syscall"
        : "=a"(ret)
        : "a"(12),       /* SYS_brk */
          "D"(new_end)
        : "rcx", "r11", "memory"
    );

    if (ret == 0)
        return (void *)-1;

    heap_end = (char *)ret;
    return prev;
}