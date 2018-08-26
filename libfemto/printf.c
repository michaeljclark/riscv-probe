// See LICENSE for license details.

#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>

#include "common.h"

int vprintf(const char* s, va_list vl)
{
  char buf[256];
  int res = vsnprintf(buf, sizeof buf, s, vl);
  putstring(buf);
  return res;
}

int printf(const char* s, ...)
{
  int res = 0;
  va_list vl;
  va_start(vl, s);
  res = vprintf(s, vl);
  va_end(vl);
  return res;
}

