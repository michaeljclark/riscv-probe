// See LICENSE for license details.

#include "femto.h"

static config_data_t qemu_sifive_u[] = {
    { UART0_CLOCK_FREQ,         32000000   },
    { UART0_BAUD_RATE,          115200     },
    { SIFIVE_UART0_CTRL_ADDR,   0x10013000 },
    { SIFIVE_TEST_CTRL_ADDR,    0x100000   },
    { 0, 0 }
};

void setup()
{
    register_console(qemu_sifive_u, &console_sifive_uart);
    register_poweroff(qemu_sifive_u, &poweroff_sifive_test);
}
