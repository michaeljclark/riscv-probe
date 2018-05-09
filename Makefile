CC_32=riscv32-unknown-elf-gcc
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

MBI_UART_OBJS = mbi_uart.o
MBI_UART_LIB = libmbi_uart.a
MBI_UART_RV32_OBJ = $(addprefix obj/riscv32/,$(MBI_UART_OBJS))
MBI_UART_RV64_OBJ = $(addprefix obj/riscv64/,$(MBI_UART_OBJS))

all: programs

programs: bin/riscv32/probe-htif bin/riscv64/probe-htif bin/riscv32/probe-uart bin/riscv64/probe-uart

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

lib/riscv32/$(MBI_UART_LIB): $(MBI_UART_RV32_OBJ)
	@echo AR.32 $@ ; mkdir -p $(@D) ; $(AR) cr $@ $^

lib/riscv64/$(MBI_UART_LIB): $(MBI_UART_RV64_OBJ)
	@echo AR.64 $@ ; mkdir -p $(@D) ; $(AR) cr $@ $^

bin/riscv32/probe-htif: $(PROBE_RV32_OBJ) lib/riscv32/$(MBI_CORE_LIB) lib/riscv32/$(MBI_HTIF_LIB)
	@echo LD.32 $@ ; mkdir -p $(@D) ; $(CC_32) $(LDFLAGS) -T src/mbi_htif.lds $^ -o $@

bin/riscv64/probe-htif: $(PROBE_RV64_OBJ) lib/riscv64/$(MBI_CORE_LIB) lib/riscv64/$(MBI_HTIF_LIB)
	@echo LD.64 $@ ; mkdir -p $(@D) ; $(CC_64) $(LDFLAGS) -T src/mbi_htif.lds $^ -o $@

bin/riscv32/probe-uart: $(PROBE_RV32_OBJ) lib/riscv32/$(MBI_CORE_LIB) lib/riscv32/$(MBI_UART_LIB)
	@echo LD.32 $@ ; mkdir -p $(@D) ; $(CC_32) $(LDFLAGS) -T src/mbi_htif.lds $^ -o $@

bin/riscv64/probe-uart: $(PROBE_RV64_OBJ) lib/riscv64/$(MBI_CORE_LIB) lib/riscv64/$(MBI_UART_LIB)
	@echo LD.64 $@ ; mkdir -p $(@D) ; $(CC_64) $(LDFLAGS) -T src/mbi_htif.lds $^ -o $@
