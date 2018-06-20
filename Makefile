CC_32=riscv64-unknown-elf-gcc -march=rv32imac -mabi=ilp32
CC_64=riscv64-unknown-elf-gcc
AR=riscv64-unknown-elf-ar

CFLAGS=-mcmodel=medany
LDFLAGS=-nostartfiles -nostdlib -static

PROBE_OBJ = probe.o
PROBE_RV32_OBJ = $(addprefix obj/riscv32/,$(PROBE_OBJ))
PROBE_RV64_OBJ = $(addprefix obj/riscv64/,$(PROBE_OBJ))

MBI_CORE_OBJS = mbi_entry.o mbi_trap.o mbi_csr.o snprintf.o
MBI_CORE_LIB = libmbi_core.a
MBI_CORE_RV32_OBJ = $(addprefix obj/riscv32/,$(MBI_CORE_OBJS))
MBI_CORE_RV64_OBJ = $(addprefix obj/riscv64/,$(MBI_CORE_OBJS))

MBI_HTIF_OBJS = mbi_htif.o
MBI_HTIF_LIB = libmbi_htif.a
MBI_HTIF_RV32_OBJ = $(addprefix obj/riscv32/,$(MBI_HTIF_OBJS))
MBI_HTIF_RV64_OBJ = $(addprefix obj/riscv64/,$(MBI_HTIF_OBJS))

MBI_UART_SIFIVE_OBJS = mbi_uart_sifive.o
MBI_UART_SIFIVE_LIB = libmbi_uart_sifive.a
MBI_UART_SIFIVE_RV32_OBJ = $(addprefix obj/riscv32/,$(MBI_UART_SIFIVE_OBJS))
MBI_UART_SIFIVE_RV64_OBJ = $(addprefix obj/riscv64/,$(MBI_UART_SIFIVE_OBJS))

MBI_UART_16550_OBJS = mbi_uart_16550.o
MBI_UART_16550_LIB = libmbi_uart_16550.a
MBI_UART_16550_RV32_OBJ = $(addprefix obj/riscv32/,$(MBI_UART_16550_OBJS))
MBI_UART_16550_RV64_OBJ = $(addprefix obj/riscv64/,$(MBI_UART_16550_OBJS))

SPIKE_LD_SCRIPT=conf/htif_0x80000000.lds
VIRT_LD_SCRIPT=conf/dram_0x80000000.lds
SIFIVE_U_LD_SCRIPT=conf/dram_0x80000000.lds
SIFIVE_E_LD_SCRIPT=conf/nvram_0x20400000.lds

ALL_PROGRAMS =	bin/riscv32/probe-spike \
				bin/riscv64/probe-spike \
				bin/riscv32/probe-virt \
				bin/riscv64/probe-virt \
				bin/riscv32/probe-sifive_e \
				bin/riscv64/probe-sifive_e \
				bin/riscv32/probe-sifive_u \
				bin/riscv64/probe-sifive_u

all: programs

programs: $(ALL_PROGRAMS)

clean:
	rm -fr bin lib obj

backup: clean
	tar czf ../$(shell basename $(shell pwd)).tar.gz .

obj/riscv32/%.o: src/%.S
	@echo AS.32 $@ ; mkdir -p $(@D) ; $(CC_32) $(CFLAGS) -c $^ -o $@

obj/riscv64/%.o: src/%.S
	@echo AS.64 $@ ; mkdir -p $(@D) ; $(CC_64) $(CFLAGS) -c $^ -o $@

obj/riscv32/%.o: src/%.c
	@echo CC.32 $@ ; mkdir -p $(@D) ; $(CC_32) $(CFLAGS) -c $^ -o $@

obj/riscv64/%.o: src/%.c
	@echo CC.64 $@ ; mkdir -p $(@D) ; $(CC_64) $(CFLAGS) -c $^ -o $@

lib/riscv32/$(MBI_CORE_LIB): $(MBI_CORE_RV32_OBJ)
	@echo AR.32 $@ ; mkdir -p $(@D) ; $(AR) cr $@ $^

lib/riscv64/$(MBI_CORE_LIB): $(MBI_CORE_RV64_OBJ)
	@echo AR.64 $@ ; mkdir -p $(@D) ; $(AR) cr $@ $^

lib/riscv32/$(MBI_HTIF_LIB): $(MBI_HTIF_RV32_OBJ)
	@echo AR.32 $@ ; mkdir -p $(@D) ; $(AR) cr $@ $^

lib/riscv64/$(MBI_HTIF_LIB): $(MBI_HTIF_RV64_OBJ)
	@echo AR.64 $@ ; mkdir -p $(@D) ; $(AR) cr $@ $^

lib/riscv32/$(MBI_UART_SIFIVE_LIB): $(MBI_UART_SIFIVE_RV32_OBJ)
	@echo AR.32 $@ ; mkdir -p $(@D) ; $(AR) cr $@ $^

lib/riscv64/$(MBI_UART_SIFIVE_LIB): $(MBI_UART_SIFIVE_RV64_OBJ)
	@echo AR.64 $@ ; mkdir -p $(@D) ; $(AR) cr $@ $^

lib/riscv32/$(MBI_UART_16550_LIB): $(MBI_UART_16550_RV32_OBJ)
	@echo AR.32 $@ ; mkdir -p $(@D) ; $(AR) cr $@ $^

lib/riscv64/$(MBI_UART_16550_LIB): $(MBI_UART_16550_RV64_OBJ)
	@echo AR.64 $@ ; mkdir -p $(@D) ; $(AR) cr $@ $^

bin/riscv32/probe-spike: $(PROBE_RV32_OBJ) lib/riscv32/$(MBI_CORE_LIB) lib/riscv32/$(MBI_HTIF_LIB)
	@echo LD.32 $@ ; mkdir -p $(@D) ; $(CC_32) $(LDFLAGS) -T ${SPIKE_LD_SCRIPT} $^ -o $@

bin/riscv64/probe-spike: $(PROBE_RV64_OBJ) lib/riscv64/$(MBI_CORE_LIB) lib/riscv64/$(MBI_HTIF_LIB)
	@echo LD.64 $@ ; mkdir -p $(@D) ; $(CC_64) $(LDFLAGS) -T ${SPIKE_LD_SCRIPT} $^ -o $@

bin/riscv32/probe-virt: $(PROBE_RV32_OBJ) lib/riscv32/$(MBI_CORE_LIB) lib/riscv32/$(MBI_UART_16550_LIB)
	@echo LD.32 $@ ; mkdir -p $(@D) ; $(CC_32) $(LDFLAGS) -T ${VIRT_LD_SCRIPT} $^ -o $@

bin/riscv64/probe-virt: $(PROBE_RV64_OBJ) lib/riscv64/$(MBI_CORE_LIB) lib/riscv64/$(MBI_UART_16550_LIB)
	@echo LD.64 $@ ; mkdir -p $(@D) ; $(CC_64) $(LDFLAGS) -T ${VIRT_LD_SCRIPT} $^ -o $@

bin/riscv32/probe-sifive_e: $(PROBE_RV32_OBJ) lib/riscv32/$(MBI_CORE_LIB) lib/riscv32/$(MBI_UART_SIFIVE_LIB)
	@echo LD.32 $@ ; mkdir -p $(@D) ; $(CC_32) $(LDFLAGS) -T ${SIFIVE_E_LD_SCRIPT} $^ -o $@

bin/riscv64/probe-sifive_e: $(PROBE_RV64_OBJ) lib/riscv64/$(MBI_CORE_LIB) lib/riscv64/$(MBI_UART_SIFIVE_LIB)
	@echo LD.64 $@ ; mkdir -p $(@D) ; $(CC_64) $(LDFLAGS) -T ${SIFIVE_E_LD_SCRIPT} $^ -o $@

bin/riscv32/probe-sifive_u: $(PROBE_RV32_OBJ) lib/riscv32/$(MBI_CORE_LIB) lib/riscv32/$(MBI_UART_SIFIVE_LIB)
	@echo LD.32 $@ ; mkdir -p $(@D) ; $(CC_32) $(LDFLAGS) -T ${SIFIVE_U_LD_SCRIPT} $^ -o $@

bin/riscv64/probe-sifive_u: $(PROBE_RV64_OBJ) lib/riscv64/$(MBI_CORE_LIB) lib/riscv64/$(MBI_UART_SIFIVE_LIB)
	@echo LD.64 $@ ; mkdir -p $(@D) ; $(CC_64) $(LDFLAGS) -T ${SIFIVE_U_LD_SCRIPT} $^ -o $@
