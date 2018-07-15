#include "encoding.h"
#include "trap.h"
#include "common.h"

static trap_fn tfn = 0;

void register_trap_fn(trap_fn fn)
{
	tfn = fn;
}

void trap_handler(uintptr_t* regs, uintptr_t mcause, uintptr_t mepc)
{
	if (tfn) {
		tfn(regs, mcause, mepc);
	} else {
	  	die("machine mode: unhandlable trap %d @ %p", mcause, mepc);
	}
}
