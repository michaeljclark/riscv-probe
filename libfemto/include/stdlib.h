// See LICENSE for license details.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

void* malloc(size_t size);
void free(void* ptr);
void malloc_addblock(void* addr, size_t size);

#ifdef __cplusplus
}
#endif
