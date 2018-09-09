// See LICENSE for license details.

#include "femto.h"

auxval_t __auxv[] = {
    { 0, 0 }
};

void setup()
{
    register_console(&console_htif);
    register_poweroff(&poweroff_htif);
}
