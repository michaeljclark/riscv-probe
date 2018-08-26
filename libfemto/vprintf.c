// See LICENSE for license details.

#include "femto.h"

int vprintf(const char* s, va_list vl)
{
  char buf[256];
  int res = vsnprintf(buf, sizeof buf, s, vl);
  putstring(buf);
  return res;
}
