#ifndef _STDLIB_H
#define _STDLIB_H

#include "stddef.h"
#include "stdint.h"

static char *heap_end;

void *malloc(size_t size);
void  free(void *ptr);

#endif