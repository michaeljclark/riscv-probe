#pragma once

#include <stdint.h>

#if __SIZE_WIDTH__ == 32
#define ctzl ctz32
#define clzl clz32
#endif

#if __SIZE_WIDTH__ == 64
#define ctzl ctz64
#define clzl clz64
#endif

#define clz(X) _Generic((X),                \
                 char: clz8,                \
                 signed char: clz8,         \
                 unsigned char: clz8,       \
                 short: clz16,              \
                 unsigned short: clz16,     \
                 int: clz32,                \
                 unsigned int: clz32,       \
                 long: clzl,                \
                 unsigned long: clzl,       \
                 long long: clz64,          \
                 unsigned long long: clz64  \
                 )(X)

#define ctz(X) _Generic((X),                \
                 char: ctz8,                \
                 unsigned char: ctz8,       \
                 signed char: ctz8,         \
                 short: ctz16,              \
                 unsigned short: ctz16,     \
                 int: ctz32,                \
                 unsigned int: ctz32,       \
                 long: ctzl,                \
                 unsigned long: ctzl,       \
                 long long: ctz64,          \
                 unsigned long long: ctz64  \
                 )(X)

int clz8(int8_t val);
int clz16(int16_t val);
int clz32(int32_t val);
int clz64(int64_t val);

int ctz8(int8_t val);
int ctz16(int16_t val);
int ctz32(int32_t val);
int ctz64(int64_t val);

#define ispow2(val) ((val) && !((val) & ((val)-1)))
#define roundpow2(val) (1<<((sizeof(val)>>3)-clz(val-1)))
