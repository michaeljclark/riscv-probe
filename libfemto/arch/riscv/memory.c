// See LICENSE for license details.

#include "femto.h"
#include "arch/riscv/trap.h"
#include "arch/riscv/encoding.h"
#include "arch/riscv/machine.h"

static volatile int save_cause = -1;

static void trap_save_cause(uintptr_t* regs, uintptr_t mcause, uintptr_t mepc)
{
	save_cause = mcause;
    write_csr(mepc, mepc + 4);
}

/* we add 4 to PC so can't risk emitting compressed instructions */
asm (".option norvc");

uintptr_t memory_probe(uintptr_t start, uintptr_t limit)
{
    trap_fn save = get_trap_fn();
    set_trap_fn(trap_save_cause);
	volatile uintptr_t *p = (volatile uintptr_t *)start;
	for (; p < (uintptr_t *)limit; p += RISCV_PGSIZE) {
        asm volatile ("" : : "r" (*p));
        if (save_cause != -1) {
        	break;
        }
	}
    set_trap_fn(save);
	return ((uintptr_t)p)-1;
}
