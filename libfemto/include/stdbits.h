#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define clz(val) ({                         \
    int result;                             \
    switch(sizeof(val)) {                   \
    case 1: result = clz8(val); break;      \
    case 2: result = clz16(val); break;     \
    case 4: result = clz32(val); break;     \
    case 8: result = clz64(val); break;     \
    }                                       \
    result;                                 \
})

#define ctz(val) ({                         \
    int result;                             \
    switch(sizeof(val)) {                   \
    case 1: result = ctz8(val); break;      \
    case 2: result = ctz16(val); break;     \
    case 4: result = ctz32(val); break;     \
    case 8: result = ctz64(val); break;     \
    }                                       \
    result;                                 \
})

int clz8(int8_t val);
int clz16(int16_t val);
int clz32(int32_t val);
int clz64(int64_t val);

int ctz8(int8_t val);
int ctz16(int16_t val);
int ctz32(int32_t val);
int ctz64(int64_t val);

static inline int ispow2(uintptr_t val)
{
    return val && !(val & (val-1));
}

static inline uintptr_t roundpow2(uintptr_t val)
{
    val--;
    val |= val >> 1;
    val |= val >> 2;
    val |= val >> 4;
    val |= val >> 8;
    val |= val >> 16;
#if __SIZE_WIDTH__ == 64
    val |= val >> 32;
#endif
    val++;
    return val;
}

#ifdef __cplusplus
}
#endif
