#include "femto.h"

int main()
{
	/*
	 * Set up PMP (Physical Memory Protection)
	 *
	 * Enforcement is optional; enforcement is mandatory if implemented.
	 * Read the Privileged ISA specification v1.10. It makes sense.
	 * We should change this code to restrict user mode to just a little
	 * bit of .text, a smattering of .rodata, a pinch of .data, some .bss
	 * and a wee bit of UART. This is why it is optional and mandatory.
	 */
	pmp_allow_all();

	/* and then ... */
	set_mode_and_continue(PRV_U);

	/* rolls dice ... */
	puts("user");

	/* any luck? */
}
