// See LICENSE for license details.

#include <stdint.h>

enum {
    /* UART Registers */
    UART_REG_TXFIFO = 0,
    UART_REG_RXFIFO = 1,
    UART_REG_TXCTRL = 2,
    UART_REG_RXCTRL = 3,
    UART_REG_IE     = 4,
    UART_REG_IP     = 5,
    UART_REG_DIV    = 6
};

/* UART0 address on riscv-qemu 'sifive_e' and 'sifive_u' machines */
volatile int *uart = (int *)0x10013000;
volatile uint32_t *testfinisher = (uint32_t *)0x100000;

int getchar()
{
    int ch = uart[UART_REG_RXFIFO];
    if (ch < 0) return -1;
    return ch;
}

int putchar(int ch)
{
    while (uart[UART_REG_TXFIFO] < 0);
    return uart[UART_REG_TXFIFO] = ch & 0xff;
}

void poweroff()
{
    *testfinisher = 0x5555;
    while (1) {
        asm volatile("");
    }
}

void init() {}
