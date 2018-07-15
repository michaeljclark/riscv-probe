// See LICENSE for license details.

#include <stdint.h>

enum {
    UART_REG_QUEUE     = 0,
    UART_REG_LINESTAT  = 5,
    UART_REG_STATUS_RX = 0x01,
    UART_REG_STATUS_TX = 0x20
};

/* UART0 address on riscv-qemu 'virt' machine */
volatile uint8_t *uart16550 = (uint8_t *)0x10000000;
volatile uint32_t *testfinisher = (uint32_t *)0x100000;

int getchar()
{
    if (uart16550[UART_REG_LINESTAT] & UART_REG_STATUS_RX) {
        return uart16550[UART_REG_QUEUE];
    } else {
        return -1;
    }
}

int putchar(int ch)
{
    while ((uart16550[UART_REG_LINESTAT] & UART_REG_STATUS_TX) == 0);
    return uart16550[UART_REG_QUEUE] = ch & 0xff;
}

void poweroff()
{
    *testfinisher = 0x5555;
    while (1) {
        asm volatile("");
    }
}
