# See LICENSE for license details.

.include "macros.s"
.include "constants.s"

#
# start of trap handler
#

.section .text.init,"ax",@progbits
.globl reset_vector

reset_vector:
    la      sp, stacks + STACK_SIZE
    jal     init
    jal     main
    j       poweroff

    .bss
    .align 4
stacks:
    .skip STACK_SIZE
