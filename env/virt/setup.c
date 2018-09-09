// See LICENSE for license details.

#include "femto.h"

static config_data_t virt[] = {
    { UART0_CLOCK_FREQ,         1843200    },
    { UART0_BAUD_RATE,          115200     },
    { NS16550A_UART0_CTRL_ADDR, 0x10000000 },
    { SIFIVE_TEST_CTRL_ADDR,    0x100000   },
    { 0, 0 }
};

void setup()
{
    register_console(virt, &console_ns16550a);
    register_poweroff(virt, &poweroff_sifive_test);
}
