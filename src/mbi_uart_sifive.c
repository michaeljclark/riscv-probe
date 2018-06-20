// See LICENSE for license details.

#include <stdint.h>

enum {
    UART_REG_TXFIFO = 0,
    UART_REG_RXFIFO = 1,
    UART_REG_TXCTRL = 2,
    UART_REG_RXCTRL = 3,
    UART_REG_DIV = 4
};

/* UART0 address on riscv-qemu 'sifive_e' and 'sifive_u' machines */
volatile int *uart = (int *)0x10013000;
volatile uint32_t *testfinisher = (uint32_t *)0x100000;

int mbi_console_getchar()
{
    int ch = uart[UART_REG_RXFIFO];
    if (ch < 0) return -1;
    return ch;
}

void mbi_console_putchar(uint8_t ch)
{
    while (uart[UART_REG_TXFIFO] < 0);
    uart[UART_REG_TXFIFO] = ch;
}

void mbi_poweroff()
{
    *testfinisher = 0x5555;
    while (1) {
        asm volatile("");
    }
}
