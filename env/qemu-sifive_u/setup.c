// See LICENSE for license details.

#include "femto.h"

auxval_t __auxv[] = {
    { UART0_CLOCK_FREQ,         32000000   },
    { UART0_BAUD_RATE,          115200     },
    { SIFIVE_UART0_CTRL_ADDR,   0x10010000 },
    { SIFIVE_TEST_CTRL_ADDR,    0x4000   },
    { 0, 0 }
};

void arch_setup()
{
    register_console(&console_sifive_uart);
    register_poweroff(&poweroff_sifive_test);
}
