#ifndef _UNISTD_H
#define _UNISTD_H

#include "stddef.h"
#include "stdint.h"

typedef long ssize_t;

ssize_t write(int fd, const void *buf, size_t count);

void *sbrk(intptr_t increment);

#endif