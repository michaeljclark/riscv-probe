// See LICENSE for license details.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*trap_fn)(uintptr_t* regs, uintptr_t mcause, uintptr_t mepc);
trap_fn get_trap_fn();
void set_trap_fn(trap_fn fn);

const char * riscv_excp_names[16];
const char * riscv_intr_names[16];

enum {
  cause_misaligned_fetch     = 0,
  cause_fault_fetch          = 1,
  cause_illegal_instruction  = 2,
  cause_breakpoint           = 3,
  cause_misaligned_load      = 4,
  cause_fault_load           = 5,
  cause_misaligned_store     = 6,
  cause_fault_store          = 7,
  cause_user_ecall           = 8,
  cause_supervisor_ecall     = 9,
  cause_hypervisor_ecall     = 10,
  cause_machine_ecall        = 11,
  cause_exec_page_fault      = 12,
  cause_load_page_fault      = 13,
  cause_store_page_fault     = 15
};

enum {
  intr_u_software           = 0,
  intr_s_software           = 1,
  intr_h_software           = 2,
  intr_m_software           = 3,
  intr_u_timer              = 4,
  intr_s_timer              = 5,
  intr_h_timer              = 6,
  intr_m_timer              = 7,
  intr_u_external           = 8,
  intr_s_external           = 9,
  intr_h_external           = 10,
  intr_m_external           = 11,
};

#ifdef __cplusplus
}
#endif
