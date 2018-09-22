// See LICENSE for license details.

#include "femto.h"

extern uint64_t tohost;
extern uint64_t fromhost;

auxval_t __auxv[] = {
    { RISCV_HTIF_BASE_ADDR, 0 },
    { 0, 0 }
};

void arch_setup()
{
	__auxv[0].val = (uintptr_t)(&tohost < &fromhost ? &tohost : &fromhost);
    register_console(&console_htif);
    register_poweroff(&poweroff_htif);
}
