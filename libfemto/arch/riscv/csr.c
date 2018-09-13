// See LICENSE for license details.

#include "femto.h"
#include "arch/riscv/csr.h"
#include "arch/riscv/encoding.h"
#include "arch/riscv/machine.h"

static int all_csr_enums[] = {
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
    csr_pmpaddr15,
    csr_none,
};

static const char* all_csr_names[] = {
    "none",
    "fflags",
    "frm",
    "fcsr",
    "mcycle",
    "minstret",
    "mcycleh",
    "minstreth",
    "cycle",
    "time",
    "instret",
    "cycleh",
    "timeh",
    "instreth",
    "mvendorid",
    "marchid",
    "mimpid",
    "mhartid",
    "mstatus",
    "misa",
    "medeleg",
    "mideleg",
    "mie",
    "mtvec",
    "mcounteren",
    "mscratch",
    "mepc",
    "mcause",
    "mtval",
    "mip",
    "sstatus",
    "sedeleg",
    "sideleg",
    "sie",
    "stvec",
    "scounteren",
    "sscratch",
    "sepc",
    "scause",
    "stval",
    "sip",
    "satp",
    "pmpcfg0",
    "pmpcfg1",
    "pmpcfg2",
    "pmpcfg3",
    "pmpaddr0",
    "pmpaddr1",
    "pmpaddr2",
    "pmpaddr3",
    "pmpaddr4",
    "pmpaddr5",
    "pmpaddr6",
    "pmpaddr7",
    "pmpaddr8",
    "pmpaddr9",
    "pmpaddr10",
    "pmpaddr11",
    "pmpaddr12",
    "pmpaddr13",
    "pmpaddr14",
    "pmpaddr15"
};

int* csr_enum_array()
{
    return all_csr_enums;
}

const char** csr_name_array()
{
    return all_csr_names;
}

long read_csr_enum(int csrenum)
{
    long result = -1;
    switch (csrenum) {
    case csr_fflags:     result = read_csr(0x001); break;
    case csr_frm:        result = read_csr(0x002); break;
    case csr_fcsr:       result = read_csr(0x003); break;
    case csr_mcycle:     result = read_csr(0xB00); break;
    case csr_minstret:   result = read_csr(0xB02); break;
    case csr_mcycleh:    result = read_csr(0xB80); break;
    case csr_minstreth:  result = read_csr(0xB82); break;
    case csr_cycle:      result = read_csr(0xC00); break;
    case csr_time:       result = read_csr(0xC01); break;
    case csr_instret:    result = read_csr(0xC02); break;
    case csr_cycleh:     result = read_csr(0xC80); break;
    case csr_timeh:      result = read_csr(0xC81); break;
    case csr_instreth:   result = read_csr(0xC82); break;
    case csr_mvendorid:  result = read_csr(0xF11); break;
    case csr_marchid:    result = read_csr(0xF12); break;
    case csr_mimpid:     result = read_csr(0xF13); break;
    case csr_mhartid:    result = read_csr(0xF14); break;
    case csr_mstatus:    result = read_csr(0x300); break;
    case csr_misa:       result = read_csr(0x301); break;
    case csr_medeleg:    result = read_csr(0x302); break;
    case csr_mideleg:    result = read_csr(0x303); break;
    case csr_mie:        result = read_csr(0x304); break;
    case csr_mtvec:      result = read_csr(0x305); break;
    case csr_mcounteren: result = read_csr(0x306); break;
    case csr_mscratch:   result = read_csr(0x340); break;
    case csr_mepc:       result = read_csr(0x341); break;
    case csr_mcause:     result = read_csr(0x342); break;
    case csr_mtval:      result = read_csr(0x343); break;
    case csr_mip:        result = read_csr(0x344); break;
    case csr_sstatus:    result = read_csr(0x100); break;
    case csr_sedeleg:    result = read_csr(0x102); break;
    case csr_sideleg:    result = read_csr(0x103); break;
    case csr_sie:        result = read_csr(0x104); break;
    case csr_stvec:      result = read_csr(0x105); break;
    case csr_scounteren: result = read_csr(0x106); break;
    case csr_sscratch:   result = read_csr(0x140); break;
    case csr_sepc:       result = read_csr(0x141); break;
    case csr_scause:     result = read_csr(0x142); break;
    case csr_stval:      result = read_csr(0x143); break;
    case csr_sip:        result = read_csr(0x144); break;
    case csr_satp:       result = read_csr(0x180); break;
    case csr_pmpcfg0:    result = read_csr(0x3A0); break;
    case csr_pmpcfg1:    result = read_csr(0x3A1); break;
    case csr_pmpcfg2:    result = read_csr(0x3A2); break;
    case csr_pmpcfg3:    result = read_csr(0x3A3); break;
    case csr_pmpaddr0:   result = read_csr(0x3B0); break;
    case csr_pmpaddr1:   result = read_csr(0x3B1); break;
    case csr_pmpaddr2:   result = read_csr(0x3B2); break;
    case csr_pmpaddr3:   result = read_csr(0x3B3); break;
    case csr_pmpaddr4:   result = read_csr(0x3B4); break;
    case csr_pmpaddr5:   result = read_csr(0x3B5); break;
    case csr_pmpaddr6:   result = read_csr(0x3B6); break;
    case csr_pmpaddr7:   result = read_csr(0x3B7); break;
    case csr_pmpaddr8:   result = read_csr(0x3B8); break;
    case csr_pmpaddr9:   result = read_csr(0x3B9); break;
    case csr_pmpaddr10:  result = read_csr(0x3BA); break;
    case csr_pmpaddr11:  result = read_csr(0x3BB); break;
    case csr_pmpaddr12:  result = read_csr(0x3BC); break;
    case csr_pmpaddr13:  result = read_csr(0x3BD); break;
    case csr_pmpaddr14:  result = read_csr(0x3BE); break;
    case csr_pmpaddr15:  result = read_csr(0x3BF); break;
    default: break;
    }
    return result;
}

void write_csr_enum(int csrenum, long value)
{
    switch (csrenum) {
    case csr_fflags:     write_csr(0x001, value); break;
    case csr_frm:        write_csr(0x002, value); break;
    case csr_fcsr:       write_csr(0x003, value); break;
    case csr_mcycle:     write_csr(0xB00, value); break;
    case csr_minstret:   write_csr(0xB02, value); break;
    case csr_mcycleh:    write_csr(0xB80, value); break;
    case csr_minstreth:  write_csr(0xB82, value); break;
    case csr_cycle:      write_csr(0xC00, value); break;
    case csr_time:       write_csr(0xC01, value); break;
    case csr_instret:    write_csr(0xC02, value); break;
    case csr_cycleh:     write_csr(0xC80, value); break;
    case csr_timeh:      write_csr(0xC81, value); break;
    case csr_instreth:   write_csr(0xC82, value); break;
    case csr_mvendorid:  write_csr(0xF11, value); break;
    case csr_marchid:    write_csr(0xF12, value); break;
    case csr_mimpid:     write_csr(0xF13, value); break;
    case csr_mhartid:    write_csr(0xF14, value); break;
    case csr_mstatus:    write_csr(0x300, value); break;
    case csr_misa:       write_csr(0x301, value); break;
    case csr_medeleg:    write_csr(0x302, value); break;
    case csr_mideleg:    write_csr(0x303, value); break;
    case csr_mie:        write_csr(0x304, value); break;
    case csr_mtvec:      write_csr(0x305, value); break;
    case csr_mcounteren: write_csr(0x306, value); break;
    case csr_mscratch:   write_csr(0x340, value); break;
    case csr_mepc:       write_csr(0x341, value); break;
    case csr_mcause:     write_csr(0x342, value); break;
    case csr_mtval:      write_csr(0x343, value); break;
    case csr_mip:        write_csr(0x344, value); break;
    case csr_sstatus:    write_csr(0x100, value); break;
    case csr_sedeleg:    write_csr(0x102, value); break;
    case csr_sideleg:    write_csr(0x103, value); break;
    case csr_sie:        write_csr(0x104, value); break;
    case csr_stvec:      write_csr(0x105, value); break;
    case csr_scounteren: write_csr(0x106, value); break;
    case csr_sscratch:   write_csr(0x140, value); break;
    case csr_sepc:       write_csr(0x141, value); break;
    case csr_scause:     write_csr(0x142, value); break;
    case csr_stval:      write_csr(0x143, value); break;
    case csr_sip:        write_csr(0x144, value); break;
    case csr_satp:       write_csr(0x180, value); break;
    case csr_pmpcfg0:    write_csr(0x3A0, value); break;
    case csr_pmpcfg1:    write_csr(0x3A1, value); break;
    case csr_pmpcfg2:    write_csr(0x3A2, value); break;
    case csr_pmpcfg3:    write_csr(0x3A3, value); break;
    case csr_pmpaddr0:   write_csr(0x3B0, value); break;
    case csr_pmpaddr1:   write_csr(0x3B1, value); break;
    case csr_pmpaddr2:   write_csr(0x3B2, value); break;
    case csr_pmpaddr3:   write_csr(0x3B3, value); break;
    case csr_pmpaddr4:   write_csr(0x3B4, value); break;
    case csr_pmpaddr5:   write_csr(0x3B5, value); break;
    case csr_pmpaddr6:   write_csr(0x3B6, value); break;
    case csr_pmpaddr7:   write_csr(0x3B7, value); break;
    case csr_pmpaddr8:   write_csr(0x3B8, value); break;
    case csr_pmpaddr9:   write_csr(0x3B9, value); break;
    case csr_pmpaddr10:  write_csr(0x3BA, value); break;
    case csr_pmpaddr11:  write_csr(0x3BB, value); break;
    case csr_pmpaddr12:  write_csr(0x3BC, value); break;
    case csr_pmpaddr13:  write_csr(0x3BD, value); break;
    case csr_pmpaddr14:  write_csr(0x3BE, value); break;
    case csr_pmpaddr15:  write_csr(0x3BF, value); break;
    default: break;
    }
}
