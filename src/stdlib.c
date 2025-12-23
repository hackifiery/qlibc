#include "stdlib.h"
#include "unistd.h"

static char *heap_end;

void *malloc(size_t size) {
    void *p;
    if (size == 0)
        return NULL;

    if (!heap_end)
        heap_end = sbrk(0);
    
    p = heap_end;
    heap_end += size;

    return p;
}

/* it just leaks memory bruh... */
void free(void *ptr) {
    (void)ptr;
}