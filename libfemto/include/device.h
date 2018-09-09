// See LICENSE for license details.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

enum {
	HART0_CLOCK_FREQ           = 0x00010000,
	UART0_CLOCK_FREQ           = 0x00011000,
	UART0_BAUD_RATE            = 0x00011100,
	NS16550A_UART0_CTRL_ADDR   = 0x00030000,
	RISCV_HTIF_TOHOST_ADDR     = 0x00050000,
	RISCV_HTIF_FROMHOST_ADDR   = 0x00050001,
	SIFIVE_CLINT_CTRL_ADDR     = 0x55550000,
	SIFIVE_CLIC_CRTL_ADDR      = 0x55550001,
	SIFIVE_TEST_CTRL_ADDR      = 0x55550002,
	SIFIVE_UART0_CTRL_ADDR     = 0x55550010,
	SIFIVE_GPIO0_CTRL_ADDR     = 0x55550020,
	SIFIVE_SPI0_CTRL_ADDR      = 0x55550030,
};

typedef struct config_data {
	uintptr_t key;
	uintptr_t val;
} config_data_t;

typedef struct console_device {
	void (*init)(config_data_t *);
	int (*getchar)();
	int (*putchar)(int);
} console_device_t;

typedef struct poweroff_device {
	void (*init)(config_data_t *);
	void (*poweroff)(void) __attribute__((noreturn));
} poweroff_device_t;

void setup();
int putchar(int);
int getchar();
void poweroff(void) __attribute__((noreturn));

void register_console(config_data_t *cfg, console_device_t *dev);
void register_poweroff(config_data_t *cfg, poweroff_device_t *dev);
uintptr_t get_config_data(config_data_t *cfg, uintptr_t key);

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
