# See LICENSE for license details.

.equ REGBYTES, 4

.macro lx a, b
lw \a, \b
.endm

.macro sx a, b
sw \a, \b
.endm

.macro lxsp a, b
lw \a, ((\b)*REGBYTES)(sp)
.endm

.macro sxsp a, b
sw \a, ((\b)*REGBYTES)(sp)
.endm

.macro .ptr a
.4byte \a
.endm
