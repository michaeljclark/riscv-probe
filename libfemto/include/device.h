// See LICENSE for license details.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct console_device {
    void (*init)();
    int (*getchar)();
    int (*putchar)(int);
} console_device_t;

typedef struct poweroff_device {
    void (*init)();
    void (*poweroff)(int);
} poweroff_device_t;

void register_console(console_device_t *dev);
void register_poweroff(poweroff_device_t *dev);

extern console_device_t *console_dev;
extern poweroff_device_t *poweroff_dev;

extern console_device_t console_none;
extern console_device_t console_htif;
extern console_device_t console_ns16550a;
extern console_device_t console_sifive_uart;
extern console_device_t console_semihost;

extern poweroff_device_t poweroff_none;
extern poweroff_device_t poweroff_htif;
extern poweroff_device_t poweroff_sifive_test;
extern poweroff_device_t poweroff_semihost;

#ifdef __cplusplus
}
#endif
