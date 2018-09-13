// See LICENSE for license details.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

void arch_setup();
void exit(int status) __attribute__((noreturn));

#define die(str, ...) ({ \
  printf("%s:%d: " str "\n", __FILE__, __LINE__, ##__VA_ARGS__); exit(-1); })

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

static inline uintptr_t get_field(uintptr_t reg, uintptr_t mask)
{
    return ((reg & mask) / (mask & ~(mask << 1)));
}

static inline uintptr_t set_field(uintptr_t reg, uintptr_t mask, uintptr_t val)
{
    return ((reg & ~mask) | ((val * (mask & ~(mask << 1))) & mask));
}

static inline unsigned long rdtime() { return read_csr(time); }
static inline unsigned long rdcycle() { return read_csr(cycle); }
static inline unsigned long rdinstret() { return read_csr(instret); }
static inline int64_t misa() { return read_const_csr(misa); }
static inline int has_ext(char ext) { return misa() & (1 << (ext - 'a')); }
static inline int xlen() { return misa() < 0 ? 64 : 32; }
static inline void wfi() { asm volatile ("wfi" ::: "memory"); }

__attribute__((noreturn)) static inline void mret()
{
    asm volatile ("mret");
    __builtin_unreachable();
}

/*
 * - PMP is optional
 * - PMP enforcement is mandatory by default if PMP is implemented
 *   meaning loads, stores or instruction fetches from modes higher
 *   than M mode will fail unless explicitly allowed. This means
 *   PMP must be configured irregardless of whether it is implemented.
 * - PMP can be unimplemented, wired to zero, or may trap
 */
static inline void pmp_allow_all()
{
  /* borrowed from bbl. set up a PMP to permit access to all of memory.
   * Ignore the illegal-instruction trap if PMPs aren't supported. */
  uintptr_t pmpc = PMP_NAPOT | PMP_R | PMP_W | PMP_X;
  asm volatile ("la t0, 1f\n\t"
                "csrrw t0, mtvec, t0\n\t"
                "csrw pmpaddr0, %1\n\t"
                "csrw pmpcfg0, %0\n\t"
                ".align 2\n\t"
                "1: csrw mtvec, t0"
                : : "r" (pmpc), "r" (-1UL) : "t0");
            /*                        ^ Reserved
             * Section 3.6.1 Physical Memory Protection CSRs
             * Table 3.9: NAPOT range encoding in PMP address and
             * configuration registers: 1111...1111 NAPOT Reserved
             */
}

/*
 * pmp_entry_set - configure a pmp entry
 *
 * - n    : pmp entry number
 * - prot : protection (PMP_R | PMP_W | PMP_X)
 * - addr : start address
 * - len  : power of two length
 */
int pmp_entry_set(unsigned n, uint8_t prot, uint64_t addr, uint64_t len);

/*
 * set_mode_and_jump
 *
 * Set mstatus.mpp, sets mepc to passed function pointer and then issues mret
 * Note: the hart will continue running on the same stack
 */
static inline void set_mode_and_jump(unsigned mode, void (*fn)(void))
{
    assert(mode <= PRV_U);
    write_csr(mstatus, set_field(read_csr(mstatus), MSTATUS_MPP, mode));
    write_csr(mepc, fn);
    mret();
}

/*
 * set_mode_and_continue
 *
 * Set mstatus.mpp, sets mepc to instruction after mret and then issues mret
 * Note: the hart will continue running on the same stack
 */
static inline void set_mode_and_continue(unsigned mode)
{
    assert(mode <= PRV_U);
    write_csr(mstatus, set_field(read_csr(mstatus), MSTATUS_MPP, mode));
    asm volatile (
        "lla t0, 1f\n"
        "csrw mepc, t0\n"
        "mret\n"
        "1:"
        ::: "t0"
    );
}

#ifdef __cplusplus
}
#endif
