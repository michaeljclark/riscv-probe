// See LICENSE for license details.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

int* csr_enum_array();
const char** csr_name_array();
long read_csr_enum(int csrenum);
void write_csr_enum(int csrenum, long value);

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
    csr_satp,
    csr_pmpcfg0,
    csr_pmpcfg1,
    csr_pmpcfg2,
    csr_pmpcfg3,
    csr_pmpaddr0,
    csr_pmpaddr1,
    csr_pmpaddr2,
    csr_pmpaddr3,
    csr_pmpaddr4,
    csr_pmpaddr5,
    csr_pmpaddr6,
    csr_pmpaddr7,
    csr_pmpaddr8,
    csr_pmpaddr9,
    csr_pmpaddr10,
    csr_pmpaddr11,
    csr_pmpaddr12,
    csr_pmpaddr13,
    csr_pmpaddr14,
    csr_pmpaddr15
};

#ifdef __cplusplus
}
#endif
