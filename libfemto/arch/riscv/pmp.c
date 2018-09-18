// See LICENSE for license details.

#include "femto.h"
#include "arch/riscv/csr.h"
#include "arch/riscv/trap.h"
#include "arch/riscv/encoding.h"
#include "arch/riscv/machine.h"

static int pmp_count = -1;

static void trap_save_cause(uintptr_t* regs, uintptr_t mcause, uintptr_t mepc)
{
    write_csr(mepc, mepc + 4);
}

int pmp_entry_count()
{
    trap_fn save;

    /* return cached value */
    if (pmp_count >= 0) {
        return pmp_count;
    }

    /* loop through PMPs checking we can set bit 1 */
    save = get_trap_fn();
    set_trap_fn(trap_save_cause);
    pmp_count = 0;
    for (size_t i = 0; i < PMP_COUNT; i++) {
        int present;
        uintptr_t addrsave = read_csr_enum(csr_pmpaddr0 + i);
        write_csr_enum(csr_pmpaddr0 + i, 0b10);
        present = read_csr_enum(csr_pmpaddr0 + i) == 0b10;
        write_csr_enum(csr_pmpaddr0 + i, addrsave);
        if (present) {
            pmp_count++;
        } else {
            break;
        }
    }
    set_trap_fn(save);

    return pmp_count;
}

int pmp_entry_set(unsigned n, uint8_t prot, uint64_t addr, uint64_t len)
{
    /* check parameters */
    if (n >= PMP_COUNT || len < 4 || !ispow2(len)) {
        return -1;
    }

    /* calculate PMP config register and offset */
    int pmpcfg_csr = (__riscv_xlen == 32) ? csr_pmpcfg0 + (n >> 2) :
                     (__riscv_xlen == 64) ? csr_pmpcfg0 + (n >> 3) << 1 : -1;
    int pmpcfg_shift = (__riscv_xlen == 32) ? (n & 3) << 3 :
                       (__riscv_xlen == 64) ? (n & 7) << 3 : -1;
    if (pmpcfg_csr < 0 || pmpcfg_shift < 0) {
        return -1;
    }

    /* encode config */
    prot |= (len == 4) ? PMP_NA4 : PMP_NAPOT;
    uintptr_t pmpcfg = ((uintptr_t)prot) << pmpcfg_shift;
    uintptr_t cfgmask = ~(0xff << pmpcfg_shift);

    /* encode address */
    int pmpaddr_csr = csr_pmpaddr0 + n;
    uintptr_t pmpmask = (1UL << (ctz(len) - PMP_SHIFT)) - 1;
    uintptr_t pmpaddr = ((addr >> PMP_SHIFT) & ~pmpmask) | (pmpmask >> 1);

    /* write csrs */
    pmpcfg |= (read_csr_enum(pmpcfg_csr) & cfgmask) | pmpcfg;
    write_csr_enum(pmpcfg_csr, pmpcfg);
    write_csr_enum(pmpaddr_csr, pmpaddr);

    return 0;
}
