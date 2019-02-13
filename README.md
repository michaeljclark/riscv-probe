# riscv-probe

Simple machine mode program to probe RISC-V control and status registers.

riscv-probe currently builds for
[Spike](https://github.com/riscv/riscv-isa-sim),
[QEMU](https://github.com/riscv/riscv-qemu) and the
[SiFive E21](https://www.sifive.com/products/risc-v-core-ip/e2/e21/) core.
riscv-probe is a testing tool designed be used to compare CSRs (Control and
Status Registers) between mutliple RISC-V simulators and RISC-V hardware
implementations.

riscv-probe contains libfemto which is a lightweight bare-metal C library
conforming to a reduced set ot the _POSIX.1-2017 / IEEE 1003.1-2017_ standard.
libfemto can be used as a starting point for bare metal RISC-V programs that
require interrupt handling, basic string routines and printf.

## Dependencies

A recent version of `riscv-tools` with a multilib build of RISC-V GCC.

- [riscv-tools](https://github.com/riscv/riscv-tools)
  - [riscv-isa-sim](https://github.com/riscv/riscv-isa-sim)
  - [riscv-openocd](https://github.com/riscv/riscv-openocd)
  - [riscv-gnu-toolchain](https://github.com/riscv/riscv-gnu-toolchain)
- [riscv-qemu](https://github.com/riscv/riscv-qemu)

## Build

The build system uses `CROSS_COMPILE` as the toolchain prefix and expects
the toolchain to be present in the `PATH` environment variable. The default
value for `CROSS_COMPILE` is `riscv64-unknown-elf-` however this can be
overridden e.g. `make CROSS_COMPILE=riscv64-unknown-linux-gnu-`. The build
system expects a multilib toolchain as it uses the same toolchain to build
for _riscv32_ and _riscv64_. Make sure to use `--enable-multilib` when
configuring [riscv-gnu-toolchain](https://github.com/riscv/riscv-gnu-toolchain).
The examples are all built with `-nostartfiles -nostdlib -nostdinc` so either
the RISC-V GCC Newlib toolchain or RISC-V GCC Glibc Linux toolchain can be used.

To build the examples after environent setup, type:

```
make
```

## Invocation

To invoke the probe example in spike and RISC-V QEMU:

- `$ spike --isa=RV32IMAFDC build/bin/rv32imac/spike/probe`
- `$ spike --isa=RV64IMAFDC build/bin/rv64imac/spike/probe`
- `$ qemu-system-riscv32 -nographic -machine spike_v1.10 -kernel build/bin/rv32imac/spike/probe`
- `$ qemu-system-riscv64 -nographic -machine spike_v1.10 -kernel build/bin/rv64imac/spike/probe`
- `$ qemu-system-riscv32 -nographic -machine virt -kernel build/bin/rv32imac/virt/probe`
- `$ qemu-system-riscv64 -nographic -machine virt -kernel build/bin/rv64imac/virt/probe`
- `$ qemu-system-riscv32 -nographic -machine sifive_e -kernel build/bin/rv32imac/qemu-sifive_e/probe`
- `$ qemu-system-riscv64 -nographic -machine sifive_e -kernel build/bin/rv64imac/qemu-sifive_e/probe`
- `$ qemu-system-riscv32 -nographic -machine sifive_u -kernel build/bin/rv32imac/qemu-sifive_u/probe`
- `$ qemu-system-riscv64 -nographic -machine sifive_u -kernel build/bin/rv64imac/qemu-sifive_u/probe`

## libfemto

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

### Environments

This project contains a simple build system that allows building applications
targeting multiple embedded environments. A distinguishing characteristic of
the build system is that program objects do not need to be recompiled to target
a different environment, rather they are relinked with a different hardware
configuration and setup function. The config object causes the correct drivers
to be linked via compile time dependencies expressed by symbol references.
The following environments are currently supported:

- _default_ - environment where IO defaults to `ebreak`
- _spike_- the RISC-V ISA Simulator Golden Model
- _virt_ - the RISC-V VirtIO Virtual Machine
- _qemu-sifive_e_ - QEMU Functional Model of the SiFive E Series
- _qemu-sifive_u_ - QEMU Functional Model of the SiFive U Series
- _coreip-e2-arty_ - SiFive E2 CoreIP Arty A7 FPGA evaluation image

To create a new environment simply add a directory to `env` with two files:

- `default.lds` - linker script describing the target's memory layout
- `config.c` - environment specific configuration

The following is an example configuration from `env/<boardname>/config.c`
showing the auxiliary vector used by `getauxval` via the `setup` function
called by `_start` before entering `main`.

```
auxval_t __auxv[] = {
    { UART0_CLOCK_FREQ,         32000000   },
    { UART0_BAUD_RATE,          115200     },
    { SIFIVE_UART0_CTRL_ADDR,   0x20000000 },
    { SIFIVE_TEST_CTRL_ADDR,    0x4000     },
    { 0, 0 }
};

void setup()
{
    /*
     * clock setup code should be placed here and should modify the
     * uart clock speed before calling register_console, which calls
     * uart_init and reads the uart clock speed from the config array.
     */
    register_console(&console_sifive_uart);
    register_poweroff(&poweroff_sifive_test);
}
```

## Examples

The build system automatically includes any directory added to `examples`
which contains a `rules.mk` file.

### hello

The following is the `rules.mk` file from the _hello_ example:

```
$ cat examples/hello/rules.mk 
hello_objs = hello.o
```

and `hello.c`

```
$ cat examples/hello/hello.c 
#include <stdio.h>

int main(int argc, char **argv)
{
	printf("hello\n");
}
```

### symbols

libfemto linker scripts define the following special symbols:

Symbol           | Value
------           | -----
`_text_start`    | start of `.text` section
`_text_end`      | end of `.text` section
`_rodata_start`  | start of `.rodata` section
`_rodata_end`    | end of `.rodata` section
`_data_start`    | start of `.data` section
`_data_end`      | end of `.data` section
`_bss_start`     | start of `.bss` section
`_bss_end`       | end of `.bss` section
`_memory_start`  | start of RAM
`_memory_end`    | end of RAM

The symbols example program shows how to access these special symbols. They
can be used for example to locate data section in a flat image in ROM to copy
into memory and to zero the bss section.

### user

Simple example program that sets up PMP (Physical Memory Protection)
to allow all memory accesses and then switches to U mode. The code to
set up PMP to allow all memory access is `pmp_allow_all()` in `machine.h`.
The code is derived from _bbl_.

Note: PMP is enabled by default on systems that implement it, so it is
mandatory to include code to configure PMPs to allow memory access when
switching from M mode to S mode or U mode, otherwise memory accesses will trap.

### enclave

Simple enclave example using RISC-V PMP (Physical Memory Protection)

Physical memory protection is enabled for the program text (RX)
program data (RW), UART, and the hart is switch to U mode, however,
there is only one program and the default trap vector points into
the executable text, so traps are handled in M mode, in the same
executable text segment.

A future example will load a second process and provide ecall APIs
to the process running in the protected enclave.

### probe

`riscv-probe` is a utility that probes the Control and Status Register
address space of a RISC-V emulator, FPGA or board:

#### qemu-system-riscv32

```
$ qemu-system-riscv32 -nographic -machine spike_v1.10 -kernel build/bin/rv32/spike/probe
isa: rv32imafdcsu
csr: fflags          illegal_instruction cause=0x00000002 mtval=0x00000000
csr: frm             illegal_instruction cause=0x00000002 mtval=0x00000000
csr: fcsr            illegal_instruction cause=0x00000002 mtval=0x00000000
csr: mcycle          0xdbfa9cbd
csr: minstret        0xdc03f6a4
csr: mcycleh         0x0007c452
csr: minstreth       0x0007c452
csr: cycle           0xdc1d7e08
csr: time            illegal_instruction cause=0x00000002 mtval=0x00000000
csr: instret         0xdc393bf6
csr: cycleh          0x0007c452
csr: timeh           illegal_instruction cause=0x00000002 mtval=0x00000000
csr: instreth        0x0007c452
csr: mvendorid       0x00000000
csr: marchid         0x00000000
csr: mimpid          0x00000000
csr: mhartid         0x00000000
csr: mstatus         0x00000000
csr: misa            0x4014112d
csr: medeleg         0x00000000
csr: mideleg         0x00000000
csr: mie             0x00000000
csr: mtvec           0x80000004
csr: mcounteren      0x00000000
csr: mscratch        0x00000000
csr: mepc            0x800002a4
csr: mcause          0x00000002
csr: mtval           0x00000000
csr: mip             0x00000000
csr: sstatus         0x00000000
csr: sedeleg         illegal_instruction cause=0x00000002 mtval=0x00000000
csr: sideleg         illegal_instruction cause=0x00000002 mtval=0x00000000
csr: sie             0x00000000
csr: stvec           0x00000000
csr: scounteren      0x00000000
csr: sscratch        0x00000000
csr: sepc            0x00000000
csr: scause          0x00000000
csr: stval           0x00000000
csr: sip             0x00000000
csr: satp            0x00000000
csr: pmpcfg0         0x00000000
csr: pmpcfg1         0x00000000
csr: pmpcfg2         0x00000000
csr: pmpcfg3         0x00000000
csr: pmpaddr0        0x00000000
csr: pmpaddr1        0x00000000
csr: pmpaddr2        0x00000000
csr: pmpaddr3        0x00000000
csr: pmpaddr4        0x00000000
csr: pmpaddr5        0x00000000
csr: pmpaddr6        0x00000000
csr: pmpaddr7        0x00000000
csr: pmpaddr8        0x00000000
csr: pmpaddr9        0x00000000
csr: pmpaddr10       0x00000000
csr: pmpaddr11       0x00000000
csr: pmpaddr12       0x00000000
csr: pmpaddr13       0x00000000
csr: pmpaddr14       0x00000000
csr: pmpaddr15       0x00000000
```

#### qemu-system-riscv64

```
$ qemu-system-riscv64 -nographic -machine spike_v1.10 -kernel build/bin/rv64/spike/probe
isa: rv64imafdcsu
csr: fflags          illegal_instruction cause=0x00000002 mtval=0x00000000
csr: frm             illegal_instruction cause=0x00000002 mtval=0x00000000
csr: fcsr            illegal_instruction cause=0x00000002 mtval=0x00000000
csr: mcycle          0x0007c452dfeeddd3
csr: minstret        0x0007c452dff8a765
csr: mcycleh         illegal_instruction cause=0x00000002 mtval=0x00000000
csr: minstreth       illegal_instruction cause=0x00000002 mtval=0x00000000
csr: cycle           0x0007c452e01f105f
csr: time            illegal_instruction cause=0x00000002 mtval=0x00000000
csr: instret         0x0007c452e03d0a50
csr: cycleh          illegal_instruction cause=0x00000002 mtval=0x00000000
csr: timeh           illegal_instruction cause=0x00000002 mtval=0x00000000
csr: instreth        illegal_instruction cause=0x00000002 mtval=0x00000000
csr: mvendorid       0x0000000000000000
csr: marchid         0x0000000000000000
csr: mimpid          0x0000000000000000
csr: mhartid         0x0000000000000000
csr: mstatus         0x0000000000000000
csr: misa            0x800000000014112d
csr: medeleg         0x0000000000000000
csr: mideleg         0x0000000000000000
csr: mie             0x0000000000000000
csr: mtvec           0x0000000080000004
csr: mcounteren      0x0000000000000000
csr: mscratch        0x0000000000000000
csr: mepc            0x00000000800002f4
csr: mcause          0x0000000000000002
csr: mtval           0x0000000000000000
csr: mip             0x0000000000000000
csr: sstatus         0x0000000000000000
csr: sedeleg         illegal_instruction cause=0x00000002 mtval=0x00000000
csr: sideleg         illegal_instruction cause=0x00000002 mtval=0x00000000
csr: sie             0x0000000000000000
csr: stvec           0x0000000000000000
csr: scounteren      0x0000000000000000
csr: sscratch        0x0000000000000000
csr: sepc            0x0000000000000000
csr: scause          0x0000000000000000
csr: stval           0x0000000000000000
csr: sip             0x0000000000000000
csr: satp            0x0000000000000000
csr: pmpcfg0         0x0000000000000000
csr: pmpcfg1         0x0000000000000000
csr: pmpcfg2         0x0000000000000000
csr: pmpcfg3         0x0000000000000000
csr: pmpaddr0        0x0000000000000000
csr: pmpaddr1        0x0000000000000000
csr: pmpaddr2        0x0000000000000000
csr: pmpaddr3        0x0000000000000000
csr: pmpaddr4        0x0000000000000000
csr: pmpaddr5        0x0000000000000000
csr: pmpaddr6        0x0000000000000000
csr: pmpaddr7        0x0000000000000000
csr: pmpaddr8        0x0000000000000000
csr: pmpaddr9        0x0000000000000000
csr: pmpaddr10       0x0000000000000000
csr: pmpaddr11       0x0000000000000000
csr: pmpaddr12       0x0000000000000000
csr: pmpaddr13       0x0000000000000000
csr: pmpaddr14       0x0000000000000000
csr: pmpaddr15       0x0000000000000000
```
