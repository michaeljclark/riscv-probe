// See LICENSE for license details.

#include "encoding.h"
#include "trap.h"

  .section .text.init,"ax",@progbits
  .globl reset_vector

reset_vector:
  j do_reset

  .align 2
trap_vector:
  addi sp, sp, -INTEGER_CONTEXT_SIZE

  # Save registers.
  STORE ra,0*REGBYTES(sp)
  STORE a0,1*REGBYTES(sp)
  STORE a1,2*REGBYTES(sp)
  STORE a2,3*REGBYTES(sp)
  STORE a3,4*REGBYTES(sp)
  STORE a4,5*REGBYTES(sp)
  STORE a5,6*REGBYTES(sp)
  STORE a6,7*REGBYTES(sp)
  STORE a7,8*REGBYTES(sp)
  STORE t0,9*REGBYTES(sp)
  STORE t1,10*REGBYTES(sp)
  STORE t2,11*REGBYTES(sp)
  STORE t3,12*REGBYTES(sp)
  STORE t4,13*REGBYTES(sp)
  STORE t5,14*REGBYTES(sp)
  STORE t6,15*REGBYTES(sp)

  mv a0, sp                        # a0 <- regs
  csrr a1, mcause                  # a1 <- mcause
  csrr a2, mepc                    # a2 <- mepc

  # Invoke the handler.
  jal trap_handler

  # ReLOAD registers.
  LOAD ra,0*REGBYTES(sp)
  LOAD a0,1*REGBYTES(sp)
  LOAD a1,2*REGBYTES(sp)
  LOAD a2,3*REGBYTES(sp)
  LOAD a3,4*REGBYTES(sp)
  LOAD a4,5*REGBYTES(sp)
  LOAD a5,6*REGBYTES(sp)
  LOAD a6,7*REGBYTES(sp)
  LOAD a7,8*REGBYTES(sp)
  LOAD t0,9*REGBYTES(sp)
  LOAD t1,10*REGBYTES(sp)
  LOAD t2,11*REGBYTES(sp)
  LOAD t3,12*REGBYTES(sp)
  LOAD t4,13*REGBYTES(sp)
  LOAD t5,14*REGBYTES(sp)
  LOAD t6,15*REGBYTES(sp)

  addi sp, sp, INTEGER_CONTEXT_SIZE
  mret

do_reset:
  li x1, 0
  li x2, 0
  li x3, 0
  li x4, 0
  li x5, 0
  li x6, 0
  li x7, 0
  li x8, 0
  li x9, 0
  li x10, 0
  li x11, 0
  li x12, 0
  li x13, 0
  li x14, 0
  li x15, 0
  li x16, 0
  li x17, 0
  li x18, 0
  li x19, 0
  li x20, 0
  li x21, 0
  li x22, 0
  li x23, 0
  li x24, 0
  li x25, 0
  li x26, 0
  li x27, 0
  li x28, 0
  li x29, 0
  li x30, 0
  li x31, 0
  csrw mscratch, x0

  # write mtvec
  la t0, trap_vector
  csrw mtvec, t0

  # load stack pointer and jump to start_c
  la sp, stacks + RISCV_PGSIZE - MENTRY_FRAME_SIZE
  j start_c

  .bss
  .align 4
stacks:
  .skip RISCV_PGSIZE * MAX_HARTS
