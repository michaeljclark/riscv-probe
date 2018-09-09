// See LICENSE for license details.

#include "femto.h"

uintptr_t get_config_data(config_data_t *cfg, uintptr_t key)
{
	while(cfg->key) {
		if (cfg->key == key) {
			return cfg->val;
		}
		cfg++;
	}
	return 0;
}

int getchar()
{
    return console_dev->getchar();
}

int putchar(int ch)
{
    return console_dev->putchar(ch);
}

void poweroff()
{
    poweroff_dev->poweroff();
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

static __attribute__((noreturn)) void default_poweroff()
{
    asm volatile("ebreak");
    while (1) {
    	asm volatile("" : : : "memory");
    }
}

console_device_t console_none = {
    NULL,
    default_getchar,
    default_putchar
};

poweroff_device_t poweroff_none = {
    NULL,
    default_poweroff,
};

console_device_t *console_dev = &console_none;
poweroff_device_t *poweroff_dev = &poweroff_none;
