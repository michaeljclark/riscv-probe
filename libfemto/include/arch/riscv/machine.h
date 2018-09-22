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
 * Memory
 *
 * TODO - improve this API to return a list of memory segments
 */

typedef struct memory_info
{
    uintptr_t start;
    uintptr_t end;
} memory_info_t;


/*
 * memory_probe - return memory_info
 */
memory_info_t memory_probe();

/*
 * memory_probe_range - probe a memory address range
 */
uintptr_t memory_probe_range(uintptr_t start, uintptr_t end);


/*
 * Physical Memory Protection
 *
 * PMP is optional but if implememented, enforcement must be enabled by
 * default, if no PMP entries are set. This means loads, stores or fetches
 * from any mode besides M mode, will fail unless explicitly allowed.
 * PMP must be configured irregardless of whether it is implemented.
 */

typedef struct pmp_info
{
    int width;
    int granularity;
    int count;
} pmp_info_t;

/*
 * pmp_probe - return pmp_info
 */
pmp_info_t pmp_probe();

/*
 * pmp_entry_granularity - return PMP entry width (physical memory width)
 */
int pmp_entry_width();

/*
 * pmp_entry_granularity - return PMP entry granularity (smallest entry size)
 */
int pmp_entry_granularity();

/*
 * pmp_entry_count - return number of PMP entries
 */
int pmp_entry_count();

/*
 * pmp_clear_all - set PMP to disallow mode != PRV_M physical memory accesses
 */
void pmp_clear_all();

/*
 * pmp_allow_all - set PMP to allow mode != PRV_M physical memory accesses
 */
void pmp_allow_all();

/*
 * pmp_entry_set - set one PMP entry
 *
 * - n    : pmp entry number
 * - prot : protection (PMP_R | PMP_W | PMP_X)
 * - addr : start address
 * - len  : power of two length
 */
int pmp_entry_set(unsigned n, uint8_t prot, uint64_t addr, uint64_t len);


/*
 * Privileged modes
 */

/*
 * mode_set_and_jump
 *
 * Set mstatus.mpp, sets mepc to passed function pointer and then issues mret
 * Note: the hart will continue running on the same stack
 */
static inline void mode_set_and_jump(unsigned mode, void (*fn)(void))
{
    assert(mode <= PRV_U);
    write_csr(mstatus, set_field(read_csr(mstatus), MSTATUS_MPP, mode));
    write_csr(mepc, fn);
    mret();
}

/*
 * mode_set_and_continue
 *
 * Set mstatus.mpp, sets mepc to instruction after mret and then issues mret
 * Note: the hart will continue running on the same stack
 */
static inline void mode_set_and_continue(unsigned mode)
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
