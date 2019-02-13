# libfemto

libfemto is a lightweight bare-metal C library for embedded RISC-V development.
libfemto provides:

- Reduced set of the _POSIX.1-2017 / IEEE 1003.1-2017_ standard
- Simple lightweight hardware configuration mechanism
- RISC-V machine mode functions and macros
- Console and power device drivers

libfemto implements a reduced set of the _POSIX.1-2017 / IEEE 1003.1-2017_
standard, with the addition of glibc's `getauxval` API to access hardware
configuration in an auxiliary vector (`__auxv`) that contains tuples
describing the target environment. The auxiliary vector is intended as a
lightweight mechanism to pass dynamic configuration information on embedded
targets, serving as an alternative to compile time constants used during
hardware initialization. The auxiliary vector API has been repurposed to
allow retrieval of hardware configuration parameters such as clock
frequencies and device base addresses for use as a compact alternative to
(DTB) Device Tree Binary, which is not available on small embedded targets.

libfemto contains the following device drivers:

- HTIF (Host Target Interface)
- NS16550A UART Console
- SiFive UART Console
- SiFive Test Device
- Semihosting Syscalls
