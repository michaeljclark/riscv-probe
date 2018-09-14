#include <string.h>

void *memchr(const void *s, int c, size_t n)
{
    unsigned char *p = (unsigned char *)s;
    while (n-- > 0) {
       if (*p == c) return p;
       p++;
    }
    return NULL;
}
