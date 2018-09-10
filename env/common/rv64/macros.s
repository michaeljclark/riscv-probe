# See LICENSE for license details.

.equ REGBYTES, 8

.macro lx a, b
ld \a, \b
.endm

.macro sx a, b
sd \a, \b
.endm

.macro lxsp a, b
ld \a, ((\b)*REGBYTES)(sp)
.endm

.macro sxsp a, b
sd \a, ((\b)*REGBYTES)(sp)
.endm

.macro .ptr a
.8byte \a
.endm
