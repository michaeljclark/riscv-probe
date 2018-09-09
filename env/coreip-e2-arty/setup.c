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
    /*
     * clock setup code should be placed here and should modify the
     * uart clock speed before calling register_console, which calls
     * uart_init and reads the uart clock speed from the config array.
     */
    register_console(coreip_e2_arty, &console_sifive_uart);
}
