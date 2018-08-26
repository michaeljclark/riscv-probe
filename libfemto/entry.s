# See LICENSE for license details.

.include "macros.s"
.include "constants.s"

#
# start of trap handler
#

.section .text.init,"ax",@progbits
.globl reset_vector

reset_vector:
    j       do_reset

    .align 2
trap_vector:
    # Save registers.
    addi    sp, sp, -CONTEXT_SIZE
    sxsp    ra, 0
    sxsp    a0, 1
    sxsp    a1, 2
    sxsp    a2, 3
    sxsp    a3, 4
    sxsp    a4, 5
    sxsp    a5, 6
    sxsp    a6, 7
    sxsp    a7, 8
    sxsp    t0, 9
    sxsp    t1, 10
    sxsp    t2, 11
    sxsp    t3, 12
    sxsp    t4, 13
    sxsp    t5, 14
    sxsp    t6, 15

    # Invoke the handler.
    mv      a0, sp
    csrr    a1, mcause
    csrr    a2, mepc
    jal     trap_handler

    # Restore registers.
    lxsp    ra, 0
    lxsp    a0, 1
    lxsp    a1, 2
    lxsp    a2, 3
    lxsp    a3, 4
    lxsp    a4, 5
    lxsp    a5, 6
    lxsp    a6, 7
    lxsp    a7, 8
    lxsp    t0, 9
    lxsp    t1, 10
    lxsp    t2, 11
    lxsp    t3, 12
    lxsp    t4, 13
    lxsp    t5, 14
    lxsp    t6, 15
    addi sp, sp, CONTEXT_SIZE

    # Return
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
