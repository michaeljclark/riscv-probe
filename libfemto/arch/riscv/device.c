// See LICENSE for license details.

#include "femto.h"

void register_console(console_device_t const *dev)
{
    console_dev = dev;
    if (dev->init) {
        dev->init();
    }
}

void register_poweroff(poweroff_device_t const *dev)
{
    poweroff_dev = dev;
    if (dev->init) {
        dev->init();
    }
}

static int default_getchar()
{
    asm volatile("ebreak");
    return 0;
}

static int default_putchar(int ch)
{
    asm volatile("ebreak");
    return 0;
}

static void default_poweroff(int status)
{
    asm volatile("ebreak");
    while (1) {
        asm volatile("" : : : "memory");
    }
}

const console_device_t console_none = {
    NULL,
    default_getchar,
    default_putchar
};

const poweroff_device_t poweroff_none = {
    NULL,
    default_poweroff,
};

console_device_t const *console_dev;
poweroff_device_t const *poweroff_dev;

void reset_device_handlers(void)
{
    console_dev = &console_none;
    poweroff_dev = &poweroff_none;
}
