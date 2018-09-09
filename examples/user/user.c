#include "femto.h"

int main()
{
	/*
	 * Set up PMP (Physical Memory Protection)
	 *
	 * PMP is optional; bit if implemented enforcement is mandatory
	 * and user-mode is prevented access to all memory by default.
	 * We should change this code to restrict user mode to its .text
	 * .rodata, .data, .bss and devices.
	 */
	pmp_allow_all();
	set_mode_and_continue(PRV_U);
	puts("user");
}
