// See LICENSE for license details.

#include <stdint.h>

#define GLUE_HELPER(x, y) x##y
#define GLUE(x, y) GLUE_HELPER(x, y)

#define DEFINE_CTZ(T,bits)         \
int GLUE(ctz,bits)(T val)          \
{                                  \
    int n = 0;                     \
    for (n = 0; n < bits; n++) {   \
        if (val & 1) break;        \
        val >>= 1;                 \
    }                              \
    return n;                      \
}

DEFINE_CTZ(int8_t,8)
DEFINE_CTZ(int16_t,16)
DEFINE_CTZ(int32_t,32)
DEFINE_CTZ(int64_t,64)
