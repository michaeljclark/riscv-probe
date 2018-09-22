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
    RISCV_HTIF_BASE_ADDR       = 0x00050000,
    SIFIVE_CLINT_CTRL_ADDR     = 0x55550000,
    SIFIVE_CLIC_CRTL_ADDR      = 0x55550001,
    SIFIVE_TEST_CTRL_ADDR      = 0x55550002,
    SIFIVE_UART0_CTRL_ADDR     = 0x55550010,
    SIFIVE_GPIO0_CTRL_ADDR     = 0x55550020,
    SIFIVE_SPI0_CTRL_ADDR      = 0x55550030,
};

typedef struct auxval {
    unsigned long key;
    unsigned long val;
} auxval_t;

extern auxval_t __auxv[];

unsigned long getauxval(unsigned long key);

#ifdef __cplusplus
}
#endif
