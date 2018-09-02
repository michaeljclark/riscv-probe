// See LICENSE for license details.

#include <stdint.h>

enum {
    CPU_FREQ = 32000000,
    BAUD_RATE = 115200
};

enum {
    /* UART Registers */
    UART_REG_TXFIFO = 0,
    UART_REG_RXFIFO = 1,
    UART_REG_TXCTRL = 2,
    UART_REG_RXCTRL = 3,
    UART_REG_IE     = 4,
    UART_REG_IP     = 5,
    UART_REG_DIV    = 6,

    /* TXCTRL register */
    UART_TXEN       = 1,
    UART_TXSTOP     = 2,

    /* RXCTRL register */
    UART_RXEN       = 1,

    /* IP register */
    UART_IP_TXWM    = 1,
    UART_IP_RXWM    = 2
};

/* UART address on sifive_e2 FPGA image */
volatile int *uart = (int *)0x20000000;

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
    while (1) {
        asm volatile("");
    }
}

void init()
{
    uart[UART_REG_DIV] = CPU_FREQ / BAUD_RATE - 1;
    uart[UART_REG_TXCTRL] = UART_TXEN;
    uart[UART_REG_RXCTRL] = UART_RXEN;
    uart[UART_REG_IE] = 0;
    putchar('\n');
}
