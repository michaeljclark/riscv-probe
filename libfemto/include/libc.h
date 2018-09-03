// See LICENSE for license details.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

int memcmp(const void *s1, const void *s2, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *dest, int c, size_t n);
int printf(const char* s, ...);
int puts(const char *s);
int snprintf(char* out, size_t n, const char* s, ...);
size_t strlen(const char* s);
char *strncpy(char *dst, const char *src, size_t n);
int vprintf(const char* s, va_list vl);
int vsnprintf(char* out, size_t n, const char* s, va_list vl);

#define die(str, ...) ({ \
  printf("%s:%d: " str "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
  poweroff(); })

#define assert(x) ({ if (!(x)) die("assertion failed: %s", #x); })

#ifdef __cplusplus
}
#endif
