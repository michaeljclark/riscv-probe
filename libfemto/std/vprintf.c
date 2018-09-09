// See LICENSE for license details.

#include <stdio.h>

int vprintf(const char* s, va_list vl)
{
    char buf[256], *o = buf;
    int res = vsnprintf(buf, sizeof(buf) - 1, s, vl);
    buf[sizeof(buf) - 1] = '\0';
    while (*o) putchar(*o++);
    return res;
}
