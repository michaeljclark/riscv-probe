# See LICENSE for license details.

.equ MAX_HARTS,    4
.equ SAVE_REGS,    16
.equ STACK_SIZE,   1024
.equ STACK_SHIFT,  10
.equ CONTEXT_SIZE, (SAVE_REGS * REGBYTES)
