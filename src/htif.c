// See LICENSE for license details.

#include "atomic.h"
#include "encoding.h"
#include "trap.h"
#include "common.h"

# define TOHOST_CMD(dev, cmd, payload) \
  (((uint64_t)(dev) << 56) | ((uint64_t)(cmd) << 48) | (uint64_t)(payload))

#define FROMHOST_DEV(fromhost_value) ((uint64_t)(fromhost_value) >> 56)
#define FROMHOST_CMD(fromhost_value) ((uint64_t)(fromhost_value) << 8 >> 56)
#define FROMHOST_DATA(fromhost_value) ((uint64_t)(fromhost_value) << 16 >> 16)

volatile uint64_t tohost __attribute__((section(".htif")));
volatile uint64_t fromhost __attribute__((section(".htif")));

volatile int htif_console_buf;

static spinlock_t htif_lock = SPINLOCK_INIT;

static void __check_fromhost()
{
  uint64_t fh = fromhost;
  if (!fh)
    return;
  fromhost = 0;

  // this should be from the console
  switch (FROMHOST_CMD(fh)) {
    case 0:
      htif_console_buf = 1 + (uint8_t)FROMHOST_DATA(fh);
      break;
    case 1:
      break;
    default:
      break;
  }
}

static void __set_tohost(uintptr_t dev, uintptr_t cmd, uintptr_t data)
{
  while (tohost)
    __check_fromhost();
  tohost = TOHOST_CMD(dev, cmd, data);
}

static void do_tohost_fromhost(uintptr_t dev, uintptr_t cmd, uintptr_t data)
{
  spinlock_lock(&htif_lock);
    __set_tohost(dev, cmd, data);

    while (1) {
      uint64_t fh = fromhost;
      if (fh) {
        if (FROMHOST_DEV(fh) == dev && FROMHOST_CMD(fh) == cmd) {
          fromhost = 0;
          break;
        }
        __check_fromhost();
      }
    }
  spinlock_unlock(&htif_lock);
}

int getchar()
{
  spinlock_lock(&htif_lock);
    __check_fromhost();
    int ch = htif_console_buf;
    if (ch >= 0) {
      htif_console_buf = -1;
      __set_tohost(1, 0, 0);
    }
  spinlock_unlock(&htif_lock);

  return ch - 1;
}

int putchar(int ch)
{
  spinlock_lock(&htif_lock);
    __set_tohost(1, 1, ch & 0xff);
  spinlock_unlock(&htif_lock);
  return ch & 0xff;
}

void poweroff()
{
  while (1) {
    fromhost = 0;
    tohost = 1;
  }
}
