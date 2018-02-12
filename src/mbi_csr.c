#include "mbi.h"

static int all_csr_enums[] = {
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
	//mbi_csr_mtval,
	mbi_csr_mip,
	mbi_csr_sstatus,
	//mbi_csr_sedeleg,
	//mbi_csr_sideleg,
	mbi_csr_sie,
	mbi_csr_stvec,
	mbi_csr_scounteren,
	mbi_csr_sscratch,
	mbi_csr_sepc,
	mbi_csr_scause,
	//mbi_csr_stval,
	mbi_csr_sip,
	//mbi_csr_satp,
	mbi_csr_none,
};

static const char* all_csr_names[] = {
	"none",
	"fflags",
	"frm",
	"fcsr",
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
		case mbi_csr_fflags:     result = mbi_read_csr(fflags);     break;
		case mbi_csr_frm:        result = mbi_read_csr(frm);        break;
		case mbi_csr_fcsr:       result = mbi_read_csr(fcsr);       break;
		case mbi_csr_cycle:      result = mbi_read_csr(cycle);      break;
		case mbi_csr_time:       result = mbi_read_csr(time);       break;
		case mbi_csr_instret:    result = mbi_read_csr(instret);    break;
		case mbi_csr_cycleh:     result = mbi_read_csr(cycleh);     break;
		case mbi_csr_timeh:      result = mbi_read_csr(timeh);      break;
		case mbi_csr_instreth:   result = mbi_read_csr(instreth);   break;
		case mbi_csr_mvendorid:  result = mbi_read_csr(mvendorid);  break;
		case mbi_csr_marchid:    result = mbi_read_csr(marchid);    break;
		case mbi_csr_mimpid:     result = mbi_read_csr(mimpid);     break;
		case mbi_csr_mhartid:    result = mbi_read_csr(mhartid);    break;
		case mbi_csr_mstatus:    result = mbi_read_csr(mstatus);    break;
		case mbi_csr_misa:       result = mbi_read_csr(misa);       break;
		case mbi_csr_medeleg:    result = mbi_read_csr(medeleg);    break;
		case mbi_csr_mideleg:    result = mbi_read_csr(mideleg);    break;
		case mbi_csr_mie:        result = mbi_read_csr(mie);        break;
		case mbi_csr_mtvec:      result = mbi_read_csr(mtvec);      break;
		case mbi_csr_mcounteren: result = mbi_read_csr(mcounteren); break;
		case mbi_csr_mscratch:   result = mbi_read_csr(mscratch);   break;
		case mbi_csr_mepc:       result = mbi_read_csr(mepc);       break;
		case mbi_csr_mcause:     result = mbi_read_csr(mcause);     break;
		//case mbi_csr_mtval:      result = mbi_read_csr(mtval);      break;
		case mbi_csr_mip:        result = mbi_read_csr(mip);        break;
		case mbi_csr_sstatus:    result = mbi_read_csr(sstatus);    break;
		//case mbi_csr_sedeleg:    result = mbi_read_csr(sedeleg);    break;
		//case mbi_csr_sideleg:    result = mbi_read_csr(sideleg);    break;
		case mbi_csr_sie:        result = mbi_read_csr(sie);        break;
		case mbi_csr_stvec:      result = mbi_read_csr(stvec);      break;
		case mbi_csr_scounteren: result = mbi_read_csr(scounteren); break;
		case mbi_csr_sscratch:   result = mbi_read_csr(sscratch);   break;
		case mbi_csr_sepc:       result = mbi_read_csr(sepc);       break;
		case mbi_csr_scause:     result = mbi_read_csr(scause);     break;
		//case mbi_csr_stval:      result = mbi_read_csr(stval);      break;
		case mbi_csr_sip:        result = mbi_read_csr(sip);        break;
		//case mbi_csr_satp:       result = mbi_read_csr(satp);       break;
		default: break;
	}
	return result;
}

void mbi_write_csr_enum(int csrenum, long value)
{
	switch (csrenum) {
		case mbi_csr_fflags:     mbi_write_csr(fflags, value);     break;
		case mbi_csr_frm:        mbi_write_csr(frm, value);        break;
		case mbi_csr_fcsr:       mbi_write_csr(fcsr, value);       break;
		case mbi_csr_cycle:      mbi_write_csr(cycle, value);      break;
		case mbi_csr_time:       mbi_write_csr(time, value);       break;
		case mbi_csr_instret:    mbi_write_csr(instret, value);    break;
		case mbi_csr_cycleh:     mbi_write_csr(cycleh, value);     break;
		case mbi_csr_timeh:      mbi_write_csr(timeh, value);      break;
		case mbi_csr_instreth:   mbi_write_csr(instreth, value);   break;
		case mbi_csr_mvendorid:  mbi_write_csr(mvendorid, value);  break;
		case mbi_csr_marchid:    mbi_write_csr(marchid, value);    break;
		case mbi_csr_mimpid:     mbi_write_csr(mimpid, value);     break;
		case mbi_csr_mhartid:    mbi_write_csr(mhartid, value);    break;
		case mbi_csr_mstatus:    mbi_write_csr(mstatus, value);    break;
		case mbi_csr_misa:       mbi_write_csr(misa, value);       break;
		case mbi_csr_medeleg:    mbi_write_csr(medeleg, value);    break;
		case mbi_csr_mideleg:    mbi_write_csr(mideleg, value);    break;
		case mbi_csr_mie:        mbi_write_csr(mie, value);        break;
		case mbi_csr_mtvec:      mbi_write_csr(mtvec, value);      break;
		case mbi_csr_mcounteren: mbi_write_csr(mcounteren, value); break;
		case mbi_csr_mscratch:   mbi_write_csr(mscratch, value);   break;
		case mbi_csr_mepc:       mbi_write_csr(mepc, value);       break;
		case mbi_csr_mcause:     mbi_write_csr(mcause, value);     break;
		//case mbi_csr_mtval:      mbi_write_csr(mtval, value);      break;
		case mbi_csr_mip:        mbi_write_csr(mip, value);        break;
		case mbi_csr_sstatus:    mbi_write_csr(sstatus, value);    break;
		//case mbi_csr_sedeleg:    mbi_write_csr(sedeleg, value);    break;
		//case mbi_csr_sideleg:    mbi_write_csr(sideleg, value);    break;
		case mbi_csr_sie:        mbi_write_csr(sie, value);        break;
		case mbi_csr_stvec:      mbi_write_csr(stvec, value);      break;
		case mbi_csr_scounteren: mbi_write_csr(scounteren, value); break;
		case mbi_csr_sscratch:   mbi_write_csr(sscratch, value);   break;
		case mbi_csr_sepc:       mbi_write_csr(sepc, value);       break;
		case mbi_csr_scause:     mbi_write_csr(scause, value);     break;
		//case mbi_csr_stval:      mbi_write_csr(stval, value);      break;
		case mbi_csr_sip:        mbi_write_csr(sip, value);        break;
		//case mbi_csr_satp:       mbi_write_csr(satp, value);       break;
		default: break;
	}
}
