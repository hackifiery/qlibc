#include "stddef.h"
#include "stdarg.h"
#include "string.h"
#include "unistd.h"

int putchar(int c) {
    char ch = (char)c;
    write(1, &ch, 1); /* write to stdout (fd=1) */
    return c;
}
int puts(const char *s) {
    size_t len = strlen(s);
    write(1, s, len);
    write(1, "\n", 1); /* newline for puts */
    return 0;
}

static void itoa(int n, char *buf) {
    char temp[12];
    int i = 0;
    int j = 0;
    int neg = n < 0;
    if (neg) n = -n;

    do {
        temp[i++] = '0' + (n % 10);
        n /= 10;
    } while (n);

    if (neg) buf[j++] = '-';
    while (i--) buf[j++] = temp[i];
    buf[j] = 0;
}

int printf(const char *fmt, ...) {
    int count = 0;
    va_list ap;
    va_start(ap, fmt);

    for (; *fmt; fmt++) {
        if (*fmt == '%') {
            fmt++;
            if (*fmt == 'd') {
                char buf[12];
                int val = va_arg(ap, int);
                itoa(val, buf);
                write(1, buf, strlen(buf));
                count += strlen(buf);
            } else if (*fmt == 's') {
                char *s = va_arg(ap, char*);
                write(1, s, strlen(s));
                count += strlen(s);
            } else {
                char c = *fmt;
                write(1, &c, 1);
                count++;
            }
        } else {
            write(1, fmt, 1);
            count++;
        }
    }

    va_end(ap);
    return count;
}