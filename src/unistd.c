#include "unistd.h"
#include "stdint.h"

/* write(fd, buf, count) */
ssize_t write(int fd, const void *buf, size_t count) {
    long ret;
    __asm__ volatile (
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

static char *heap_end;

void *sbrk(intptr_t increment) {
    char *prev = heap_end;
    char *new_end = heap_end + increment;
    long ret;

    __asm__ volatile (
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


void *_brk(void *addr) {
    long ret;

    /* syscall number 12 = brk on x86_64 */
    __asm__ volatile (
        "mov $12, %%rax\n"   /* SYS_brk */
        "mov %1, %%rdi\n"    /* new break */
        "syscall\n"
        "mov %%rax, %0\n"    /* return value */
        : "=r"(ret)
        : "r"(addr)
        : "%rax", "%rdi", "rcx", "r11", "memory"
    );

    if (ret == 0) return (void *)-1;
    return (void *)ret;
}

__attribute__((noreturn))
void _exit(int status) {
    __asm__ volatile (
        "mov $60, %%rax\n\t"    /* put exit (60) into rax */
        "syscall\n\t"          /* call it */
        : 
        : "D" (status)
    );
    __builtin_unreachable();
}