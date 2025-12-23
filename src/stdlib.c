#include "stdlib.h"
#include "unistd.h"

void *malloc(size_t size) {
    if (size == 0)
        return NULL;

    if (!heap_end)
        heap_end = sbrk(0);

    void *p = heap_end;
    heap_end += size;

    return p;
}

/* it just leaks memory... */
void free(void *ptr) {
    (void)ptr;
}