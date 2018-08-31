// See LICENSE for license details.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdarg.h>

void init();
int putchar(int);
int getchar();
void poweroff(void) __attribute__((noreturn));

int memcmp(const void *s1, const void *s2, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *dest, int c, size_t n);
int printf(const char* s, ...);
int puts(const char *s);
int snprintf(char* out, size_t n, const char* s, ...);
size_t strlen(const char* s);
char *strncpy(char *dst, const char *src, size_t n);
int vprintf(const char* s, va_list vl);
int vsnprintf(char* out, size_t n, const char* s, va_list vl);

#define die(str, ...) ({ \
	printf("%s:%d: " str "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
	poweroff(); })

#define assert(x) ({ if (!(x)) die("assertion failed: %s", #x); })

#define read_const_csr(reg) ({ unsigned long __tmp; \
  asm ("csrr %0, " #reg : "=r"(__tmp)); __tmp; })

#define read_csr(reg) ({ unsigned long __tmp; \
  asm volatile ("csrr %0, " #reg : "=r"(__tmp)); __tmp; })

#define write_csr(reg, val) ({ \
  asm volatile ("csrw " #reg ", %0" :: "rK"(val)); })

#define swap_csr(reg, val) ({ unsigned long __tmp; \
  asm volatile ("csrrw %0, " #reg ", %1" : "=r"(__tmp) : "rK"(val)); __tmp; })

#define set_csr(reg, bit) ({ unsigned long __tmp; \
  asm volatile ("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "rK"(bit)); __tmp; })

#define clear_csr(reg, bit) ({ unsigned long __tmp; \
  asm volatile ("csrrc %0, " #reg ", %1" : "=r"(__tmp) : "rK"(bit)); __tmp; })

static inline unsigned long rdtime() { return read_csr(time); }
static inline unsigned long rdcycle() { return read_csr(cycle); }
static inline unsigned long rdinstret() { return read_csr(instret); }
static inline int64_t misa() { return read_const_csr(misa); }
static inline int has_ext(char ext) { return misa() & (1 << (ext - 'a')); }
static inline int xlen() { return misa() < 0 ? 64 : 32; }
static inline void wfi() { asm volatile ("wfi" ::: "memory"); }

typedef void (*trap_fn)(uintptr_t* regs, uintptr_t mcause, uintptr_t mepc);
void register_trap_fn(trap_fn fn);

int* csr_enum_array();
const char** csr_name_array();
long read_csr_enum(int csrenum);
void write_csr_enum(int csrenum, long value);

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

enum {
	csr_none,
	csr_fflags,
	csr_frm,
	csr_fcsr,
	csr_mcycle,
	csr_minstret,
	csr_mcycleh,
	csr_minstreth,
	csr_cycle,
	csr_time,
	csr_instret,
	csr_cycleh,
	csr_timeh,
	csr_instreth,
	csr_mvendorid,
	csr_marchid,
	csr_mimpid,
	csr_mhartid,
	csr_mstatus,
	csr_misa,
	csr_medeleg,
	csr_mideleg,
	csr_mie,
	csr_mtvec,
	csr_mcounteren,
	csr_mscratch,
	csr_mepc,
	csr_mcause,
	csr_mtval,
	csr_mip,
	csr_sstatus,
	csr_sedeleg,
	csr_sideleg,
	csr_sie,
	csr_stvec,
	csr_scounteren,
	csr_sscratch,
	csr_sepc,
	csr_scause,
	csr_stval,
	csr_sip,
	csr_satp
};

#ifdef __cplusplus
}
#endif
