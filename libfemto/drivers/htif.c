// See LICENSE for license details.

#ifdef __riscv

#include "femto.h"
#include "spinlock.h"

struct { uint32_t arr[2]; } volatile tohost __attribute__((section(".htif")));
struct { uint32_t arr[2]; } volatile fromhost __attribute__((section(".htif")));

static spinlock_t htif_lock = SPINLOCK_INIT;

static inline void htif_send(uint8_t dev, uint8_t cmd, int64_t data)
{
    /* endian neutral encoding with ordered 32-bit writes */
    union { uint32_t arr[2]; uint64_t val; } encode = {
        .val = (uint64_t)dev << 56 | (uint64_t)cmd << 48 | data
    };
    tohost.arr[0] = encode.arr[0];
    tohost.arr[1] = encode.arr[1];
}

static inline void htif_recv(uint8_t *dev, uint8_t *cmd, int64_t *data)
{
    /* endian neutral decoding with ordered 32-bit reads */
    union { uint32_t arr[2]; uint64_t val; } decode;
    decode.arr[0] = fromhost.arr[0];
    decode.arr[1] = fromhost.arr[1];
    *dev = decode.val >> 56;
    *cmd = (decode.val >> 48) & 0xff;
    *data = decode.val << 16 >> 16;
}

static int64_t htif_get_fromhost(uint8_t dev, uint8_t cmd)
{
    /* receive data for specified device and command */
    uint8_t rdev, rcmd;
    int64_t data;
    htif_recv(&rdev, &rcmd, &data);
    return rdev == dev && rcmd == cmd ? data : -1;
}

static void htif_set_tohost(uint8_t dev, uint8_t cmd, int64_t data)
{
    /* send data with specified device and command */
    while (tohost.arr[0]) {
        asm volatile ("" : : "r" (fromhost.arr[0]));
        asm volatile ("" : : "r" (fromhost.arr[1]));
    }
    htif_send(dev, cmd, data);
}

static int htif_getchar()
{
    spinlock_lock(&htif_lock);
    int ch = htif_get_fromhost(1, 0);
    if (ch & 0xff) {
        htif_set_tohost(1, 0, 0);
    }
    if (ch != -1) {
        /* we read 0x1xx where xx is the char */
        ch &= 0xff;
    }
    spinlock_unlock(&htif_lock);
    return ch;
}

static int htif_putchar(int ch)
{
    spinlock_lock(&htif_lock);
    htif_set_tohost(1, 1, ch & 0xff);
    spinlock_unlock(&htif_lock);
    return ch & 0xff;
}

static void htif_poweroff(int status)
{
    for (;;) {
        htif_set_tohost(0, 0, 1);
    }
}

console_device_t console_htif = {
    NULL,
    htif_getchar,
    htif_putchar
};


poweroff_device_t poweroff_htif = {
    NULL,
    htif_poweroff
};

#endif
