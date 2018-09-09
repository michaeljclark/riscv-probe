// See LICENSE for license details.

#include <stddef.h>

void *memcpy(void *dest, const void *src, size_t n)
{
    char *p = dest;
    while (n-- > 0) {
        *(char*)dest++ = *(char*)src++;
    }
    return p;
}
