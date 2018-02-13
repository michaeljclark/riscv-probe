#include "mbi.h"

static int all_csr_enums[] = {
	mbi_csr_fflags,
	mbi_csr_frm,
	mbi_csr_fcsr,
	mbi_csr_mcycle,
	mbi_csr_minstret,
	mbi_csr_mcycleh,
	mbi_csr_minstreth,
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
	mbi_csr_satp,
	mbi_csr_none,
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
};

int* mbi_csr_enum_array()
{
	return all_csr_enums;
}

const char** mbi_csr_name_array()
{
	return all_csr_names;
}

long mbi_read_csr_enum(int csrenum)
{
	long result = -1;
	switch (csrenum) {
		case mbi_csr_fflags:     result = mbi_read_csr(0x001); break;
		case mbi_csr_frm:        result = mbi_read_csr(0x002); break;
		case mbi_csr_fcsr:       result = mbi_read_csr(0x003); break;
		case mbi_csr_mcycle:     result = mbi_read_csr(0xB00); break;
		case mbi_csr_minstret:   result = mbi_read_csr(0xB02); break;
		case mbi_csr_mcycleh:    result = mbi_read_csr(0xB80); break;
		case mbi_csr_minstreth:  result = mbi_read_csr(0xB82); break;
		case mbi_csr_cycle:      result = mbi_read_csr(0xC00); break;
		case mbi_csr_time:       result = mbi_read_csr(0xC01); break;
		case mbi_csr_instret:    result = mbi_read_csr(0xC02); break;
		case mbi_csr_cycleh:     result = mbi_read_csr(0xC80); break;
		case mbi_csr_timeh:      result = mbi_read_csr(0xC81); break;
		case mbi_csr_instreth:   result = mbi_read_csr(0xC82); break;
		case mbi_csr_mvendorid:  result = mbi_read_csr(0xF11); break;
		case mbi_csr_marchid:    result = mbi_read_csr(0xF12); break;
		case mbi_csr_mimpid:     result = mbi_read_csr(0xF13); break;
		case mbi_csr_mhartid:    result = mbi_read_csr(0xF14); break;
		case mbi_csr_mstatus:    result = mbi_read_csr(0x300); break;
		case mbi_csr_misa:       result = mbi_read_csr(0x301); break;
		case mbi_csr_medeleg:    result = mbi_read_csr(0x302); break;
		case mbi_csr_mideleg:    result = mbi_read_csr(0x303); break;
		case mbi_csr_mie:        result = mbi_read_csr(0x304); break;
		case mbi_csr_mtvec:      result = mbi_read_csr(0x305); break;
		case mbi_csr_mcounteren: result = mbi_read_csr(0x306); break;
		case mbi_csr_mscratch:   result = mbi_read_csr(0x340); break;
		case mbi_csr_mepc:       result = mbi_read_csr(0x341); break;
		case mbi_csr_mcause:     result = mbi_read_csr(0x342); break;
		case mbi_csr_mtval:      result = mbi_read_csr(0x343); break;
		case mbi_csr_mip:        result = mbi_read_csr(0x344); break;
		case mbi_csr_sstatus:    result = mbi_read_csr(0x100); break;
		case mbi_csr_sedeleg:    result = mbi_read_csr(0x102); break;
		case mbi_csr_sideleg:    result = mbi_read_csr(0x103); break;
		case mbi_csr_sie:        result = mbi_read_csr(0x104); break;
		case mbi_csr_stvec:      result = mbi_read_csr(0x105); break;
		case mbi_csr_scounteren: result = mbi_read_csr(0x106); break;
		case mbi_csr_sscratch:   result = mbi_read_csr(0x140); break;
		case mbi_csr_sepc:       result = mbi_read_csr(0x141); break;
		case mbi_csr_scause:     result = mbi_read_csr(0x142); break;
		case mbi_csr_stval:      result = mbi_read_csr(0x143); break;
		case mbi_csr_sip:        result = mbi_read_csr(0x144); break;
		case mbi_csr_satp:       result = mbi_read_csr(0x180); break;
		default: break;
	}
	return result;
}

void mbi_write_csr_enum(int csrenum, long value)
{
	switch (csrenum) {
		case mbi_csr_fflags:     mbi_write_csr(0x001, value); break;
		case mbi_csr_frm:        mbi_write_csr(0x002, value); break;
		case mbi_csr_fcsr:       mbi_write_csr(0x003, value); break;
		case mbi_csr_mcycle:     mbi_write_csr(0xB00, value); break;
		case mbi_csr_minstret:   mbi_write_csr(0xB02, value); break;
		case mbi_csr_mcycleh:    mbi_write_csr(0xB80, value); break;
		case mbi_csr_minstreth:  mbi_write_csr(0xB82, value); break;
		case mbi_csr_cycle:      mbi_write_csr(0xC00, value); break;
		case mbi_csr_time:       mbi_write_csr(0xC01, value); break;
		case mbi_csr_instret:    mbi_write_csr(0xC02, value); break;
		case mbi_csr_cycleh:     mbi_write_csr(0xC80, value); break;
		case mbi_csr_timeh:      mbi_write_csr(0xC81, value); break;
		case mbi_csr_instreth:   mbi_write_csr(0xC82, value); break;
		case mbi_csr_mvendorid:  mbi_write_csr(0xF11, value); break;
		case mbi_csr_marchid:    mbi_write_csr(0xF12, value); break;
		case mbi_csr_mimpid:     mbi_write_csr(0xF13, value); break;
		case mbi_csr_mhartid:    mbi_write_csr(0xF14, value); break;
		case mbi_csr_mstatus:    mbi_write_csr(0x300, value); break;
		case mbi_csr_misa:       mbi_write_csr(0x301, value); break;
		case mbi_csr_medeleg:    mbi_write_csr(0x302, value); break;
		case mbi_csr_mideleg:    mbi_write_csr(0x303, value); break;
		case mbi_csr_mie:        mbi_write_csr(0x304, value); break;
		case mbi_csr_mtvec:      mbi_write_csr(0x305, value); break;
		case mbi_csr_mcounteren: mbi_write_csr(0x306, value); break;
		case mbi_csr_mscratch:   mbi_write_csr(0x340, value); break;
		case mbi_csr_mepc:       mbi_write_csr(0x341, value); break;
		case mbi_csr_mcause:     mbi_write_csr(0x342, value); break;
		case mbi_csr_mtval:      mbi_write_csr(0x343, value); break;
		case mbi_csr_mip:        mbi_write_csr(0x344, value); break;
		case mbi_csr_sstatus:    mbi_write_csr(0x100, value); break;
		case mbi_csr_sedeleg:    mbi_write_csr(0x102, value); break;
		case mbi_csr_sideleg:    mbi_write_csr(0x103, value); break;
		case mbi_csr_sie:        mbi_write_csr(0x104, value); break;
		case mbi_csr_stvec:      mbi_write_csr(0x105, value); break;
		case mbi_csr_scounteren: mbi_write_csr(0x106, value); break;
		case mbi_csr_sscratch:   mbi_write_csr(0x140, value); break;
		case mbi_csr_sepc:       mbi_write_csr(0x141, value); break;
		case mbi_csr_scause:     mbi_write_csr(0x142, value); break;
		case mbi_csr_stval:      mbi_write_csr(0x143, value); break;
		case mbi_csr_sip:        mbi_write_csr(0x144, value); break;
		case mbi_csr_satp:       mbi_write_csr(0x180, value); break;
		default: break;
	}
}
