#include <stdio.h>

#ifndef __riscv

void probe_all()
{
	puts("architecture-not-supported");
}

#endif
