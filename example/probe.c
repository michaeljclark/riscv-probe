#include "femto.h"

#define MCAUSE_UNSET 0xabbaabba

static uintptr_t save_mcause;

static void trap_save_cause(uintptr_t* regs, uintptr_t mcause, uintptr_t mepc)
{
	save_mcause = mcause;
	write_csr(mepc, mepc + 4);
}

static void append_ext(char *str, char ext)
{
	char *s = str + strlen(str);
	if (has_ext(ext)) {
		*s = ext;
		*(++s) = '\0';
	}
}

static const char* isa_string()
{
	static char str[32];
	snprintf(str, sizeof(str), "rv%d", xlen());
	append_ext(str, 'i');
	append_ext(str, 'm');
	append_ext(str, 'a');
	append_ext(str, 'f');
	append_ext(str, 'd');
	append_ext(str, 'c');
	append_ext(str, 's');
	append_ext(str, 'u');
	return str;
}

static void probe_all_csrs()
{
	int *csrenum = csr_enum_array();
	const char **csrnames = csr_name_array();
	const char* ws = "               ";
	register_trap_fn(trap_save_cause);
	while (*csrenum != csr_none) {
		save_mcause = MCAUSE_UNSET;
		long value = read_csr_enum(*csrenum);
		const char* csrname = csrnames[*csrenum];
		if (save_mcause != MCAUSE_UNSET) {
			int async = save_mcause < 0;
			int cause = save_mcause & (((uintptr_t)-1) >> async);
			printf("csr: %s%s %s cause=0x%x mtval=0x%x\n",
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

int main()
{
	printf("isa: %s\n", isa_string());
	probe_all_csrs();
	printf("\n");
}
