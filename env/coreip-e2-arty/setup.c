// See LICENSE for license details.

#include "femto.h"

static config_data_t coreip_e2_arty[] = {
    { UART0_CLOCK_FREQ,         32000000   },
    { UART0_BAUD_RATE,          115200     },
    { SIFIVE_UART0_CTRL_ADDR,   0x20000000 },
    { 0, 0 }
};

void setup()
{
	/* note: clock setup code can modify uart clock speed */
    register_console(coreip_e2_arty, &console_sifive_uart);
}
