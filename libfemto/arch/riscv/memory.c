// See LICENSE for license details.

#include "femto.h"
#include "arch/riscv/trap.h"
#include "arch/riscv/encoding.h"
#include "arch/riscv/machine.h"

extern char _memory_start;

static memory_info_t memory_info = {
    .start = -1UL,
    .end = -1UL
};

static volatile int save_cause = -1;

static void trap_save_cause(uintptr_t* regs, uintptr_t mcause, uintptr_t mepc)
{
    save_cause = mcause;
    write_csr(mepc, mepc + 4);
}

uintptr_t memory_probe_range(uintptr_t start, uintptr_t end)
{
    trap_fn save = get_trap_fn();
    set_trap_fn(trap_save_cause);
    volatile uintptr_t *p = (volatile uintptr_t *)start;
    for (; p < (uintptr_t *)end; p += RISCV_PGSIZE) {
        /* trap_save_cause adds 4 to the PC so we
         * can't emit compressed instructions */
        asm volatile (".option push");
        asm volatile (".option norvc");
        asm volatile ("" : : "r" (*p));
        asm volatile (".option pop");
        if (save_cause != -1) {
            break;
        }
    }
    set_trap_fn(save);
    return ((uintptr_t)p)-1;
}

memory_info_t memory_probe()
{
    if (memory_info.start == -1UL) {
        memory_info.start = (uintptr_t)&_memory_start,
        memory_info.end = memory_probe_range((uintptr_t)&_memory_start, -1UL);
    }
    return memory_info;
}
