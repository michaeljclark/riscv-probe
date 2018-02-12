#ifndef RISCV_MBI_H
#define RISCV_MBI_H

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

#include "encoding.h"

void mbi_console_putchar(uint8_t);
int mbi_console_getchar();
void mbi_poweroff(void) __attribute__((noreturn));

int vsnprintf(char* out, size_t n, const char* s, va_list vl);
int snprintf(char* out, size_t n, const char* s, ...);

static inline size_t strlen(const char* s)
{
  size_t c = 0; while (*s++) c++; return c;
}

static inline void mbi_putstring(const char* s)
{
  while (*s) mbi_console_putchar(*s++);
}

static inline void mbi_vprintf(const char* s, va_list vl)
{
  char buf[256];
  vsnprintf(buf, sizeof buf, s, vl);
  mbi_putstring(buf);
}

static inline void mbi_printf(const char* s, ...)
{
  va_list vl;
  va_start(vl, s);
  mbi_vprintf(s, vl);
  va_end(vl);
}

#define mbi_die(str, ...) ({ \
	mbi_printf("%s:%d: " str "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
	mbi_poweroff(); })

#define mbi_assert(x) ({ if (!(x)) mbi_die("assertion failed: %s", #x); })

#define mbi_read_const_csr(reg) ({ unsigned long __tmp; \
  asm ("csrr %0, " #reg : "=r"(__tmp)); __tmp; })

#define mbi_read_csr(reg) ({ unsigned long __tmp; \
  asm volatile ("csrr %0, " #reg : "=r"(__tmp)); __tmp; })

#define mbi_write_csr(reg, val) ({ \
  asm volatile ("csrw " #reg ", %0" :: "rK"(val)); })

#define mbi_swap_csr(reg, val) ({ unsigned long __tmp; \
  asm volatile ("csrrw %0, " #reg ", %1" : "=r"(__tmp) : "rK"(val)); __tmp; })

#define mbi_set_csr(reg, bit) ({ unsigned long __tmp; \
  asm volatile ("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "rK"(bit)); __tmp; })

#define mbi_clear_csr(reg, bit) ({ unsigned long __tmp; \
  asm volatile ("csrrc %0, " #reg ", %1" : "=r"(__tmp) : "rK"(bit)); __tmp; })

static inline unsigned long mbi_rdtime() { return mbi_read_csr(time); }
static inline unsigned long mbi_rdcycle() { return mbi_read_csr(cycle); }
static inline unsigned long mbi_rdinstret() { return mbi_read_csr(instret); }
static inline int64_t mbi_misa() { return mbi_read_const_csr(misa); }
static inline int mbi_ext(char ext) { return mbi_misa() & (1 << (ext - 'a')); }
static inline int mbi_xlen() { return mbi_misa() < 0 ? 64 : 32; }
static inline void mbi_wfi() { asm volatile ("wfi" ::: "memory"); }

typedef void (*mbi_trap_fn)(uintptr_t* regs, uintptr_t mcause, uintptr_t mepc);
void mbi_register_trap_fn(mbi_trap_fn fn);

int* mbi_csr_enum_array();
const char** mbi_csr_name_array();
long mbi_read_csr_enum(int csrenum);
void mbi_write_csr_enum(int csrenum, long value);

enum {
	mbi_cause_misaligned_fetch     = 0,
	mbi_cause_fault_fetch          = 1,
	mbi_cause_illegal_instruction  = 2,
	mbi_cause_breakpoint           = 3,
	mbi_cause_misaligned_load      = 4,
	mbi_cause_fault_load           = 5,
	mbi_cause_misaligned_store     = 6,
	mbi_cause_fault_store          = 7,
	mbi_cause_user_ecall           = 8,
	mbi_cause_supervisor_ecall     = 9,
	mbi_cause_hypervisor_ecall     = 10,
	mbi_cause_machine_ecall        = 11,
	mbi_cause_exec_page_fault      = 12,
	mbi_cause_load_page_fault      = 13,
	mbi_cause_store_page_fault     = 15
};

enum {
	mbi_intr_u_software           = 0,
	mbi_intr_s_software           = 1,
	mbi_intr_h_software           = 2,
	mbi_intr_m_software           = 3,
	mbi_intr_u_timer              = 4,
	mbi_intr_s_timer              = 5,
	mbi_intr_h_timer              = 6,
	mbi_intr_m_timer              = 7,
	mbi_intr_u_external           = 8,
	mbi_intr_s_external           = 9,
	mbi_intr_h_external           = 10,
	mbi_intr_m_external           = 11,
};

enum {
	mbi_csr_none,
	mbi_csr_fflags,
	mbi_csr_frm,
	mbi_csr_fcsr,
	mbi_csr_cycle,
	mbi_csr_time,
	mbi_csr_instret,
	mbi_csr_cycleh,
	mbi_csr_timeh,
	mbi_csr_instreth,
	mbi_csr_mvendorid,
	mbi_csr_marchid,
	mbi_csr_mimpid,
	mbi_csr_mhartid,
	mbi_csr_mstatus,
	mbi_csr_misa,
	mbi_csr_medeleg,
	mbi_csr_mideleg,
	mbi_csr_mie,
	mbi_csr_mtvec,
	mbi_csr_mcounteren,
	mbi_csr_mscratch,
	mbi_csr_mepc,
	mbi_csr_mcause,
	mbi_csr_mtval,
	mbi_csr_mip,
	mbi_csr_sstatus,
	mbi_csr_sedeleg,
	mbi_csr_sideleg,
	mbi_csr_sie,
	mbi_csr_stvec,
	mbi_csr_scounteren,
	mbi_csr_sscratch,
	mbi_csr_sepc,
	mbi_csr_scause,
	mbi_csr_stval,
	mbi_csr_sip,
	mbi_csr_satp
};


#endif
