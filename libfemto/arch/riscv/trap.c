// See LICENSE for license details.

#include "femto.h"
#include "arch/riscv/trap.h"
#include "arch/riscv/encoding.h"
#include "arch/riscv/machine.h"

static trap_fn tfn = 0;

const char * riscv_excp_names[16] = {
    "misaligned_fetch",
    "fault_fetch",
    "illegal_instruction",
    "breakpoint",
    "misaligned_load",
    "fault_load",
    "misaligned_store",
    "fault_store",
    "user_ecall",
    "supervisor_ecall",
    "hypervisor_ecall",
    "machine_ecall",
    "exec_page_fault",
    "load_page_fault",
    "reserved",
    "store_page_fault"
};

const char * riscv_intr_names[16] = {
    "u_software",
    "s_software",
    "h_software",
    "m_software",
    "u_timer",
    "s_timer",
    "h_timer",
    "m_timer",
    "u_external",
    "s_external",
    "h_external",
    "m_external",
    "reserved",
    "reserved",
    "reserved",
    "reserved"
};

trap_fn get_trap_fn()
{
    return tfn;
}

void set_trap_fn(trap_fn fn)
{
    tfn = fn;
}

void trap_handler(uintptr_t* regs, uintptr_t mcause, uintptr_t mepc)
{
    if (tfn) {
        tfn(regs, mcause, mepc);
    } else {
        die("machine mode: unhandlable trap %d @ %p", mcause, mepc);
    }
}
