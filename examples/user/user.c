#include "femto.h"

#ifdef __riscv
#include "arch/riscv/encoding.h"
#include "arch/riscv/machine.h"
#endif

int main(int argc, char **argv)
{
	/*
	 * Set up PMP (Physical Memory Protection)
	 *
	 * PMP is optional; bit if implemented enforcement is mandatory
	 * and user-mode is prevented access to all memory by default.
	 * We should change this code to restrict user mode to its .text
	 * .rodata, .data, .bss and devices.
	 */
#ifdef __riscv
	if (pmp_entry_count() > 0) {
		pmp_allow_all();
	}
	mode_set_and_continue(PRV_U);
	puts("riscv-user-mode");
#else
	puts("architecture-not-supported");
#endif
}
