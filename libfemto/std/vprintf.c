// See LICENSE for license details.

#include <stdio.h>
#include <alloca.h>

int vprintf(const char* s, va_list vl)
{
    char *out;
    int res = vsnprintf(NULL, -1, s, vl);
    out = alloca(res + 1);
    vsnprintf(out, res + 1, s, vl);
    while (*out) putchar(*out++);
    return res;
}
