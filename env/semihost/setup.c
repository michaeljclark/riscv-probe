// See LICENSE for license details.

#include "femto.h"

auxval_t __auxv[] = {
    { 0, 0 }
};

void arch_setup() {
    register_console(&console_semihost);
    register_poweroff(&poweroff_semihost);
}
