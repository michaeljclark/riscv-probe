// See LICENSE for license details.

#include "atomic.h"
#include "femto.h"

static config_data_t spike_htif[] = {
    { 0, 0 }
};

void setup()
{
    register_console(spike_htif, &console_htif);
    register_poweroff(spike_htif, &poweroff_htif);
}
