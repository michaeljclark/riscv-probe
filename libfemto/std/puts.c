// See LICENSE for license details.

#include "femto.h"

int puts(const char *s)
{
  while (*s) putchar(*s++);
  putchar('\n');
}
