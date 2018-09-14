#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

void *memchr(const void *s, int c, size_t n);
int memcmp(const void *, const void *, size_t);
void *memcpy(void *, const void *, size_t);
void *memset(void *, int, size_t);
char *strchr(const char *s, int c);
int strcmp(const char *, const char *);
size_t strlen(const char *);
int strncmp(const char *, const char *, size_t);
char *strncpy(char *, const char *, size_t);

#ifdef __cplusplus
}
#endif
