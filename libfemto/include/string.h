#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

int memcmp(const void *, const void *, size_t);
void *memcpy(void *, const void *, size_t);
void *memset(void *, int, size_t);
size_t strlen(const char *);
char *strncpy(char *, const char *, size_t);

#ifdef __cplusplus
}
#endif
