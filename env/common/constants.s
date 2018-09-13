# See LICENSE for license details.

.equ MAX_HARTS,    4
.equ SAVE_REGS,    16
.equ STACK_SIZE,   1024
.equ STACK_SHIFT,  10
.equ CONTEXT_SIZE, (SAVE_REGS * REGBYTES)

.globl _text_start
.globl _text_end
.globl _rodata_start
.globl _rodata_end
.globl _data_start
.globl _data_end
.globl _bss_start
.globl _bss_end
.global _memory_start;
.global _memory_end;
