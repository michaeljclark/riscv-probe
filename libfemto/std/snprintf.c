// See LICENSE for license details.

#include <stdio.h>
#include <stddef.h>
#include <stdarg.h>

int snprintf(char* out, size_t n, const char* s, ...)
{
    va_list vl;
    va_start(vl, s);
    int res = vsnprintf(out, n, s, vl);
    va_end(vl);
    return res;
}
