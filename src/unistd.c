#include "unistd.h"
#include "stdint.h"

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

__attribute__((noreturn))
void _exit(int status) {
    asm volatile (
        "mov $60, %%rax\n\t"    // System call number for exit (60) into rax
        "syscall\n\t"           // Invoke the system call
        :
        : "D" (status)     // "D" constraint puts status_code into rdi
        : "%rax", "memory"      // Clobber list: rax is modified, memory might be affected
    );
    __builtin_unreachable();
}