#include "femto.h"
#ifdef __riscv
#include "arch/riscv/encoding.h"
#include "arch/riscv/machine.h"
#endif

extern char _memory_start;

int main(int argc, char **argv)
{
#ifdef __riscv
	memory_info_t info = memory_probe();
	printf("memory_start=0x%lx - 0x%lx\n", info.start, info.end);
#else
	puts("architecture-not-supported");
#endif
}
