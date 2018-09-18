#include "femto.h"

#ifdef __riscv
#include "arch/riscv/csr.h"
#include "arch/riscv/trap.h"
#include "arch/riscv/encoding.h"
#include "arch/riscv/machine.h"

#define MCAUSE_UNSET 0xabbaabba

static volatile uintptr_t save_mcause;

static void trap_save_cause(uintptr_t* regs, uintptr_t mcause, uintptr_t mepc)
{
	save_mcause = mcause;
	write_csr(mepc, mepc + 4);
}

static const char* isa_string(char *buf, size_t bufsz)
{
	static const char *ext = "iemafdqlcbjtpvnsu";

	const char *p = ext;
	char *q = buf + snprintf(buf, bufsz, "rv%d", xlen());
	do {
		if (has_ext(*p)) {
			*q++ = *p;
		}
	} while (*++p);
	*q = '\0';

	return buf;
}

static void probe_all_csrs()
{
	int *csrenum = csr_enum_array();
	const char **csrnames = csr_name_array();
	const char* ws = "               ";
	set_trap_fn(trap_save_cause);
	while (*csrenum != csr_none) {
		save_mcause = MCAUSE_UNSET;
		long value = read_csr_enum(*csrenum);
		const char* csrname = csrnames[*csrenum];
		if (save_mcause != MCAUSE_UNSET) {
			int async = save_mcause < 0;
			int cause = save_mcause & (((uintptr_t)-1) >> async);
			printf("csr: %s%s %s cause=%ld mtval=0x%lx\n",
				csrname, ws + strlen(csrname), cause < 16
				? (async ? riscv_intr_names : riscv_excp_names)[cause]
				: "(unknown)", save_mcause, read_csr_enum(csr_mtval));
		} else {
			printf("csr: %s%s 0x%lx\n",
				csrname, ws + strlen(csrname), value);
		}
		csrenum++;
	}
}
#endif

int main(int argc, char **argv)
{
#ifdef __riscv
	char buf[32];
	printf("isa: %s\n", isa_string(buf, sizeof(buf)));
	probe_all_csrs();
	printf("\n");
#else
	puts("architecture-not-supported");
#endif
}
