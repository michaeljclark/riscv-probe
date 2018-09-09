// See LICENSE for license details.

#include <stdio.h>

int puts(const char *s)
{
    while (*s) putchar(*s++);
    putchar('\n');
}
