#include "encoding.h"
#include "mbi_trap.h"
#include "mbi.h"

static mbi_trap_fn trap_fn = 0;

void mbi_register_trap_fn(mbi_trap_fn fn)
{
	trap_fn = fn;
}

void trap_handler(uintptr_t* regs, uintptr_t mcause, uintptr_t mepc)
{
	if (trap_fn) {
		trap_fn(regs, mcause, mepc);
	} else {
	  	mbi_die("machine mode: unhandlable trap %d @ %p", mcause, mepc);
	}
}
