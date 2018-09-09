# riscv-probe

Simple machine mode program to probe RISC-V control and status registers.

riscv-probe currently works with:
[Spike](https://github.com/riscv/riscv-isa-sim),
[QEMU](https://github.com/riscv/riscv-qemu) and the
[SiFive E21](https://www.sifive.com/products/risc-v-core-ip/e2/e21/) core.
It can be used to compare control and status registers.
riscv-probe contains libfemto which is a lightweight bare-metal C library that can
be used as a starting point for bare metal RISC-V programs that need printf,
interrupt handling, basic string routines, getchar and putchar.

## Build

To build the examples:

```
make
```

## Invocation

To invoke the probe example in spike and RISC-V QEMU:

- `$ spike --isa=RV32IMAFDC build/bin/rv32/spike/probe`
- `$ spike --isa=RV64IMAFDC build/bin/rv64/spike/probe`
- `$ qemu-system-riscv32 -nographic -machine spike_v1.10 -kernel build/bin/rv32/spike/probe`
- `$ qemu-system-riscv64 -nographic -machine spike_v1.10 -kernel build/bin/rv64/spike/probe`
- `$ qemu-system-riscv32 -nographic -machine virt -kernel build/bin/rv32/virt/probe`
- `$ qemu-system-riscv64 -nographic -machine virt -kernel build/bin/rv64/virt/probe`
- `$ qemu-system-riscv32 -nographic -machine sifive_e -kernel build/bin/rv32/qemu-sifive_e/probe`
- `$ qemu-system-riscv64 -nographic -machine sifive_e -kernel build/bin/rv64/qemu-sifive_e/probe`
- `$ qemu-system-riscv32 -nographic -machine sifive_u -kernel build/bin/rv32/qemu-sifive_u/probe`
- `$ qemu-system-riscv64 -nographic -machine sifive_u -kernel build/bin/rv64/qemu-sifive_u/probe`


### riscv-probe in qemu-system-riscv32

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

### riscv-probe in qemu-system-riscv64

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
