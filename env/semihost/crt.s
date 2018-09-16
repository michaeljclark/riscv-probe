# See LICENSE for license details.

.include "macros.s"
.include "constants.s"

#
# start of trap handler
#

.section .text.init,"ax",@progbits
.globl _start

_start:

    # set up stack pointer based on hartid (in a0)
    mv      t0, a0
    slli    t0, t0, STACK_SHIFT
    la      sp, stacks + STACK_SIZE
    add     sp, sp, t0

    # jump to libfemto_start_main
    j       libfemto_start_main

    .bss
    .align 4
    .global stacks
stacks:
    .skip STACK_SIZE * MAX_HARTS
