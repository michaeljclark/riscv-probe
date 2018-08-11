#ifndef _RISCV_MTRAP_H
#define _RISCV_MTRAP_H

#define MAX_HARTS 1
#define REGBYTES (1 << LOG_REGBYTES)
#define MACHINE_STACK_SIZE RISCV_PGSIZE
#define INTEGER_CONTEXT_SIZE (16 * REGBYTES)
#define MENTRY_FRAME_SIZE INTEGER_CONTEXT_SIZE

#ifdef __ASSEMBLER__
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
#endif

#endif
