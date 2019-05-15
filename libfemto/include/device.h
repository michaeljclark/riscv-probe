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

void reset_device_handlers(void);
void register_console(console_device_t const *  dev);
void register_poweroff(poweroff_device_t const * dev);

extern console_device_t const *console_dev;
extern poweroff_device_t const *poweroff_dev;

extern const console_device_t console_none;
extern const console_device_t console_htif;
extern const console_device_t console_ns16550a;
extern const console_device_t console_sifive_uart;
extern const console_device_t console_semihost;

extern const poweroff_device_t poweroff_none;
extern const poweroff_device_t poweroff_htif;
extern const poweroff_device_t poweroff_sifive_test;
extern const poweroff_device_t poweroff_semihost;

#ifdef __cplusplus
}
#endif
