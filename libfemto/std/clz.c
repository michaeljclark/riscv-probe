// See LICENSE for license details.

#include <stdint.h>

#define GLUE_HELPER(x, y) x##y
#define GLUE(x, y) GLUE_HELPER(x, y)

#define DEFINE_CLZ(T,bits)         \
int GLUE(clz,bits)(T val)          \
{                                  \
    int n = 0;                     \
    for (n = 0; n < bits; n++) {   \
        if (val < 0) break;        \
        val <<= 1;                 \
    }                              \
    return n;                      \
}

DEFINE_CLZ(int8_t,8)
DEFINE_CLZ(int16_t,16)
DEFINE_CLZ(int32_t,32)
DEFINE_CLZ(int64_t,64)
