#include "femto.h"
#ifdef __riscv
#include "arch/riscv/encoding.h"
#include "arch/riscv/machine.h"
#endif

extern char _memory_start;

int main(int argc, char **argv)
{
#ifdef __riscv
	uintptr_t memory_limit = memory_probe((uintptr_t)&_memory_start, -1UL);
	printf("memory_start=0x%lx - 0x%lx\n", &_memory_start, memory_limit);
#else
	puts("architecture-not-supported");
#endif
}
