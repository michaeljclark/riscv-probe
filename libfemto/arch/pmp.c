// See LICENSE for license details.

#include "femto.h"

int pmp_entry_set(unsigned n, uint8_t prot, uint64_t addr, uint64_t len)
{
    /* check parameters */
    if (n >= 16 || len < 4 || !ispow2(len)) {
        return -1;
    }

    /* calculate PMP config register and offset */
#if __riscv_xlen == 32
    int pmpcfg_csr = csr_pmpcfg0 + (n >> 2);
    int pmpcfg_shift = (n & 3) << 3;
#elif __riscv_xlen == 64
    int pmpcfg_csr = csr_pmpcfg0 + (n >> 3) << 1;
    int pmpcfg_shift = (n & 7) << 3;
#else
#error "unsupported xlen"
#endif

    /* encode config */
    prot |= (len == 4) ? PMP_NA4 : PMP_NAPOT;
    uintptr_t pmpcfg = ((uintptr_t)prot) << pmpcfg_shift;
    uintptr_t cfgmask = ~(0xff << pmpcfg_shift);

    /* encode address */
    int pmpaddr_csr = csr_pmpaddr0 + n;
    uintptr_t pmpmask = (1UL << (ctz(len) - PMP_SHIFT)) - 1;
    uintptr_t pmpaddr = ((addr >> PMP_SHIFT) & ~pmpmask) | (pmpmask >> 1);

    /* write csrs */
    write_csr_enum(pmpcfg_csr, (read_csr_enum(pmpcfg_csr) & cfgmask) | pmpcfg);
    write_csr_enum(pmpaddr_csr, pmpaddr);

    return 0;
}
