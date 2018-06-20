#ifndef _RISCV_MTRAP_H
#define _RISCV_MTRAP_H

#ifdef __riscv_atomic
# define MAX_HARTS 2 // arbitrary
#else
# define MAX_HARTS 1
#endif

#define REGBYTES (1 << LOG_REGBYTES)
#define MACHINE_STACK_SIZE RISCV_PGSIZE
#define INTEGER_CONTEXT_SIZE (32 * REGBYTES)
#define MENTRY_FRAME_SIZE INTEGER_CONTEXT_SIZE

#ifndef __ASSEMBLER__

#define MACHINE_STACK_TOP() ({ \
  register uintptr_t sp asm ("sp"); \
  (void*)((sp + RISCV_PGSIZE) & -RISCV_PGSIZE); })

#else

#if __riscv_xlen == 64
# define SLL32    sllw
# define STORE    sd
# define LOAD     ld
# define LWU      lwu
# define LOG_REGBYTES 3
#else
# define SLL32    sll
# define STORE    sw
# define LOAD     lw
# define LWU      lw
# define LOG_REGBYTES 2
#endif

#endif // !__ASSEMBLER__

#endif
