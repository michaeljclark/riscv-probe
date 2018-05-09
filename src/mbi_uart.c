// See LICENSE for license details.

#include <stdint.h>

enum {
    UART_REG_TXFIFO = 0,
    UART_REG_RXFIFO = 1,
    UART_REG_TXCTRL = 2,
    UART_REG_RXCTRL = 3,
    UART_REG_DIV = 4
};

uint32_t *uart = (uint32_t *)0x10013000;

int mbi_console_getchar()
{
  int32_t ch = uart[UART_REG_RXFIFO];
  if (ch < 0) return -1;
  return ch;
}

void mbi_console_putchar(uint8_t ch)
{
    volatile uint32_t *tx = &uart[UART_REG_TXFIFO];
    while ((int32_t)(*tx) < 0);
    *tx = ch;
}

void mbi_poweroff()
{
  while (1) {
    asm volatile("");
  }
}