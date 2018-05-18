// See LICENSE for license details.

#include <stdint.h>

enum {
    UART_REG_QUEUE     = 0,
    UART_REG_LINESTAT  = 5,
    UART_REG_STATUS_RX = 0x01,
    UART_REG_STATUS_TX = 0x20
};

volatile uint8_t *uart16550 = (uint8_t *)0x10000000;

int mbi_console_getchar()
{
    if (uart16550[UART_REG_LINESTAT] & UART_REG_STATUS_RX) {
        return uart16550[UART_REG_QUEUE];
    } else {
        return -1;
    }
}

void mbi_console_putchar(uint8_t ch)
{
    while ((uart16550[UART_REG_LINESTAT] & UART_REG_STATUS_TX) == 0);
    uart16550[UART_REG_QUEUE] = ch;
}

void mbi_poweroff()
{
    while (1) {
        asm volatile("");
    }
}