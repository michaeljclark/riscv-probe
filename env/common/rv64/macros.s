# See LICENSE for license details.

.equ REGBYTES, 8
.macro lx a, b
ld \a, \b
.endm
.macro sx a, b
sd \a, \b
.endm
