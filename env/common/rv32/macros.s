# See LICENSE for license details.

.equ REGBYTES, 4
.macro lx a, b
lw \a, \b
.endm
.macro sx a, b
sw \a, \b
.endm
