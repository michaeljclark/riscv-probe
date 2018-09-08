// See LICENSE for license details.

#include "atomic.h"
#include "encoding.h"
#include "femto.h"

volatile uint64_t tohost __attribute__((section(".htif")));
volatile uint64_t fromhost __attribute__((section(".htif")));

static spinlock_t htif_lock = SPINLOCK_INIT;

static inline void htif_send(uint8_t dev, uint8_t cmd, int64_t data)
{
    ((volatile uint32_t *)&tohost)[0] = data;
    ((volatile uint32_t *)&tohost)[1] = dev << 24 | cmd << 16 | data >> 32;
}

static inline void htif_recv(uint8_t *dev, uint8_t *cmd, int64_t *data)
{
    uint32_t lo = ((volatile uint32_t *)&fromhost)[0];
    uint64_t hi = ((volatile uint32_t *)&fromhost)[1];
    uint64_t val = hi << 32 | lo;
    *dev = val >> 56;
    *cmd = (val >> 48) & 0xff;
    *data = val << 16 >> 16;
}

static int64_t htif_get_fromhost(uint8_t dev, uint8_t cmd)
{
    uint8_t rdev, rcmd;
    int64_t data;
    htif_recv(&rdev, &rcmd, &data);
    return rdev == dev && rcmd == cmd ? data : -1;
}

static void htif_set_tohost(uint8_t dev, uint8_t cmd, int64_t data)
{
    while (tohost) {
        asm volatile ("" : : "r" (fromhost));
    }
    htif_send(dev, cmd, data);
}

int getchar()
{
    int ch;
    spinlock_lock(&htif_lock);
    if (ch = htif_get_fromhost(1, 0) & 0xff) {
        htif_set_tohost(1, 0, 0);
    }
    spinlock_unlock(&htif_lock);
    return ch;
}

int putchar(int ch)
{
    spinlock_lock(&htif_lock);
    htif_set_tohost(1, 1, ch & 0xff);
    spinlock_unlock(&htif_lock);
    return ch & 0xff;
}

void poweroff()
{
    for (;;) {
        htif_set_tohost(0, 0, 1);
    }
}

void init() {}
