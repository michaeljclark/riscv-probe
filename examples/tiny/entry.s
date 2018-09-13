# See LICENSE for license details.

.include "macros.s"
.include "constants.s"

#
# start of trap handler
#

.section .text.init,"ax",@progbits
.globl _start

_start:
    la      sp, stacks + STACK_SIZE
    j       libfemto_start_main

    .bss
    .align 4
stacks:
    .skip STACK_SIZE
