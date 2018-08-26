# See LICENSE for license details.

.include "macros.s"
.include "constants.s"

#
# start of trap handler
#

.section .text.init,"ax",@progbits
.globl reset_vector

reset_vector:
    j do_reset

    .align 2
trap_vector:
    addi sp, sp, -CONTEXT_SIZE

    # Save registers.
    sx ra,0*REGBYTES(sp)
    sx a0,1*REGBYTES(sp)
    sx a1,2*REGBYTES(sp)
    sx a2,3*REGBYTES(sp)
    sx a3,4*REGBYTES(sp)
    sx a4,5*REGBYTES(sp)
    sx a5,6*REGBYTES(sp)
    sx a6,7*REGBYTES(sp)
    sx a7,8*REGBYTES(sp)
    sx t0,9*REGBYTES(sp)
    sx t1,10*REGBYTES(sp)
    sx t2,11*REGBYTES(sp)
    sx t3,12*REGBYTES(sp)
    sx t4,13*REGBYTES(sp)
    sx t5,14*REGBYTES(sp)
    sx t6,15*REGBYTES(sp)

    mv a0, sp          # a0 <- regs
    csrr a1, mcause    # a1 <- mcause
    csrr a2, mepc      # a2 <- mepc

    # Invoke the handler.
    jal trap_handler

    # Restore registers.
    lx ra,0*REGBYTES(sp)
    lx a0,1*REGBYTES(sp)
    lx a1,2*REGBYTES(sp)
    lx a2,3*REGBYTES(sp)
    lx a3,4*REGBYTES(sp)
    lx a4,5*REGBYTES(sp)
    lx a5,6*REGBYTES(sp)
    lx a6,7*REGBYTES(sp)
    lx a7,8*REGBYTES(sp)
    lx t0,9*REGBYTES(sp)
    lx t1,10*REGBYTES(sp)
    lx t2,11*REGBYTES(sp)
    lx t3,12*REGBYTES(sp)
    lx t4,13*REGBYTES(sp)
    lx t5,14*REGBYTES(sp)
    lx t6,15*REGBYTES(sp)

    addi sp, sp, CONTEXT_SIZE
    mret

do_reset:
    la      t0, trap_vector
    csrw    mtvec, t0
    csrr    t0, mhartid
    la      sp, stacks + STACK_SIZE
    beqz    t0, 2f
1:  addi    sp, sp, STACK_SIZE
    addi    t0, t0, -1
    bnez    t0, 1b
2:  li      ra, 0
    li      gp, 0
    li      tp, 0
    li      t0, 0
    li      t1, 0
    li      t2, 0
    li      s0, 0
    li      s1, 0
    li      a0, 0
    li      a1, 0
    li      a2, 0
    li      a3, 0
    li      a4, 0
    li      a5, 0
    li      a6, 0
    li      a7, 0
    li      s2, 0
    li      s3, 0
    li      s4, 0
    li      s5, 0
    li      s6, 0
    li      s7, 0
    li      s8, 0
    li      s9, 0
    li      s10, 0
    li      s11, 0
    li      t3, 0
    li      t4, 0
    li      t5, 0
    li      t6, 0
    jal     init
    jal     main
    j       poweroff

    .bss
    .align 4
stacks:
    .skip STACK_SIZE * MAX_HARTS
