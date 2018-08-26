// See LICENSE for license details.

#include <stddef.h>

int memcmp(const void *s1, const void *s2, size_t n)
{
    while (n-- > 0) {
        char c1 = *(const char*)s1++;
        char c2 = *(const char*)s2++;
        if (c1 != c2) {
            return c1 - c2;
        }
    }
    return 0;
}
