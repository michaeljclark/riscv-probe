RISCV_PREFIX                ?= riscv64-unknown-elf-

CC_32                        = $(RISCV_PREFIX)gcc -march=rv32imac -mabi=ilp32 -Ienv/common/rv32
CC_64                        = $(RISCV_PREFIX)gcc -march=rv64imac -mabi=lp64  -Ienv/common/rv64
AR                           = $(RISCV_PREFIX)ar

CFLAGS                       = -mcmodel=medany -Os
LDFLAGS                      = -nostartfiles -nostdlib -static -Wl,--nmagic
INCLUDES                     = -Ienv/common -Ilibfemto

EXAMPLE_PROBE_OBJ            = probe.o
EXAMPLE_PROBE_RV32_OBJ       = $(addprefix build/obj/rv32/example/,$(EXAMPLE_PROBE_OBJ))
EXAMPLE_PROBE_RV64_OBJ       = $(addprefix build/obj/rv64/example/,$(EXAMPLE_PROBE_OBJ))

LIBFEMTO_LIB                 = libfemto.a
LIBFEMTO_SRCS                = $(sort $(wildcard libfemto/*.c))
LIBFEMTO_ASM                 = $(sort $(wildcard libfemto/*.s))
LIBFEMTO_OBJS                = $(patsubst %.s,%.o,$(LIBFEMTO_ASM)) $(patsubst %.c,%.o,$(LIBFEMTO_SRCS))
LIBFEMTO_RV32_OBJ            = $(addprefix build/obj/rv32/,$(LIBFEMTO_OBJS))
LIBFEMTO_RV64_OBJ            = $(addprefix build/obj/rv64/,$(LIBFEMTO_OBJS))

UART_SPIKE_HTIF_OBJS         = uart_spike_htif.o
UART_SPIKE_HTIF_LIB          = libuart_spike_htif.a
UART_SPIKE_HTIF_RV32_OBJ     = $(addprefix build/obj/rv32/libuart/,$(UART_SPIKE_HTIF_OBJS))
UART_SPIKE_HTIF_RV64_OBJ     = $(addprefix build/obj/rv64/libuart/,$(UART_SPIKE_HTIF_OBJS))

UART_QEMU_SIFIVE_OBJS        = uart_qemu_sifive.o
UART_QEMU_SIFIVE_LIB         = libuart_qemu_sifive.a
UART_QEMU_SIFIVE_RV32_OBJ    = $(addprefix build/obj/rv32/libuart/,$(UART_QEMU_SIFIVE_OBJS))
UART_QEMU_SIFIVE_RV64_OBJ    = $(addprefix build/obj/rv64/libuart/,$(UART_QEMU_SIFIVE_OBJS))

UART_COREIP_E2_ARTY_OBJS     = uart_coreip_e2_arty.o
UART_COREIP_E2_ARTY_LIB      = libuart_coreip_e2_arty.a
UART_COREIP_E2_ARTY_RV32_OBJ = $(addprefix build/obj/rv32/libuart/,$(UART_COREIP_E2_ARTY_OBJS))
UART_COREIP_E2_ARTY_RV64_OBJ = $(addprefix build/obj/rv64/libuart/,$(UART_COREIP_E2_ARTY_OBJS))

UART_VIRT_16550_OBJS         = uart_virt_16550.o
UART_VIRT_16550_LIB          = libuart_virt_16550.a
UART_VIRT_16550_RV32_OBJ     = $(addprefix build/obj/rv32/libuart/,$(UART_VIRT_16550_OBJS))
UART_VIRT_16550_RV64_OBJ     = $(addprefix build/obj/rv64/libuart/,$(UART_VIRT_16550_OBJS))

ENV_SPIKE_LD_SCRIPT          = env/spike/default.lds
ENV_VIRT_LD_SCRIPT           = env/virt/default.lds
ENV_QEMU_SIFIVE_U_LD_SCRIPT  = env/qemu-sifive_u/default.lds
ENV_QEMU_SIFIVE_E_LD_SCRIPT  = env/qemu-sifive_e/default.lds
ENV_COREIP_E2_ARTY_LD_SCRIPT = env/coreip-e2-arty/default.lds

ALL_EXAMPLES                 = build/bin/rv32/probe-spike \
							   build/bin/rv64/probe-spike \
							   build/bin/rv32/probe-virt \
							   build/bin/rv64/probe-virt \
							   build/bin/rv32/probe-qemu-sifive_e \
							   build/bin/rv64/probe-qemu-sifive_e \
							   build/bin/rv32/probe-qemu-sifive_u \
							   build/bin/rv64/probe-qemu-sifive_u \
							   build/bin/rv32/probe-coreip-e2-arty

all: programs

programs: $(ALL_EXAMPLES)

clean:
	rm -fr build

backup: clean
	tar czf ../$(shell basename $(shell pwd)).tar.gz .

spike: all
	spike --isa=RV32IMAFDC build/bin/rv32/probe-spike
	spike --isa=RV64IMAFDC build/bin/rv64/probe-spike

qemu: all
	qemu-system-riscv32 -nographic -machine spike_v1.10 -kernel build/bin/rv32/probe-spike
	qemu-system-riscv64 -nographic -machine spike_v1.10 -kernel build/bin/rv64/probe-spike
	qemu-system-riscv32 -nographic -machine virt -kernel build/bin/rv32/probe-virt
	qemu-system-riscv64 -nographic -machine virt -kernel build/bin/rv64/probe-virt
	qemu-system-riscv32 -nographic -machine sifive_e -kernel build/bin/rv32/probe-qemu-sifive_e
	qemu-system-riscv64 -nographic -machine sifive_e -kernel build/bin/rv64/probe-qemu-sifive_e
	qemu-system-riscv32 -nographic -machine sifive_u -kernel build/bin/rv32/probe-qemu-sifive_u
	qemu-system-riscv64 -nographic -machine sifive_u -kernel build/bin/rv64/probe-qemu-sifive_u

ifdef V
cmd = @mkdir -p $2 ; echo "$3"; $3
else
cmd = @echo "$1"; mkdir -p $2 ; $3
endif

build/obj/rv32/%.o: %.s
	$(call cmd,AS.32 $@,$(@D),$(CC_32) $(CFLAGS) $(INCLUDES) -c $^ -o $@)

build/obj/rv64/%.o: %.s
	$(call cmd,AS.64 $@,$(@D),$(CC_64) $(CFLAGS) $(INCLUDES) -c $^ -o $@)

build/obj/rv32/%.o: %.c
	$(call cmd,CC.32 $@,$(@D),$(CC_32) $(CFLAGS) $(INCLUDES) -c $^ -o $@)

build/obj/rv64/%.o: %.c
	$(call cmd,CC.64 $@,$(@D),$(CC_64) $(CFLAGS) $(INCLUDES) -c $^ -o $@)

build/lib/rv32/$(LIBFEMTO_LIB): $(LIBFEMTO_RV32_OBJ)
	$(call cmd,AR.32 $@,$(@D),$(AR) cr $@ $^)

build/lib/rv64/$(LIBFEMTO_LIB): $(LIBFEMTO_RV64_OBJ)
	$(call cmd,AR.64 $@,$(@D),$(AR) cr $@ $^)

build/lib/rv32/$(UART_SPIKE_HTIF_LIB): $(UART_SPIKE_HTIF_RV32_OBJ)
	$(call cmd,AR.32 $@,$(@D),$(AR) cr $@ $^)

build/lib/rv64/$(UART_SPIKE_HTIF_LIB): $(UART_SPIKE_HTIF_RV64_OBJ)
	$(call cmd,AR.64 $@,$(@D),$(AR) cr $@ $^)

build/lib/rv32/$(UART_QEMU_SIFIVE_LIB): $(UART_QEMU_SIFIVE_RV32_OBJ)
	$(call cmd,AR.32 $@,$(@D),$(AR) cr $@ $^)

build/lib/rv32/$(UART_COREIP_E2_ARTY_LIB): $(UART_COREIP_E2_ARTY_RV32_OBJ)
	$(call cmd,AR.32 $@,$(@D),$(AR) cr $@ $^)

build/lib/rv64/$(UART_QEMU_SIFIVE_LIB): $(UART_QEMU_SIFIVE_RV64_OBJ)
	$(call cmd,AR.64 $@,$(@D),$(AR) cr $@ $^)

build/lib/rv32/$(UART_VIRT_16550_LIB): $(UART_VIRT_16550_RV32_OBJ)
	$(call cmd,AR.32 $@,$(@D),$(AR) cr $@ $^)

build/lib/rv64/$(UART_VIRT_16550_LIB): $(UART_VIRT_16550_RV64_OBJ)
	$(call cmd,AR.64 $@,$(@D),$(AR) cr $@ $^)

build/bin/rv32/probe-spike: $(EXAMPLE_PROBE_RV32_OBJ) build/lib/rv32/$(LIBFEMTO_LIB) build/lib/rv32/$(UART_SPIKE_HTIF_LIB)
	$(call cmd,LD.32 $@,$(@D),$(CC_32) $(LDFLAGS) -T ${ENV_SPIKE_LD_SCRIPT} $^ -o $@)

build/bin/rv64/probe-spike: $(EXAMPLE_PROBE_RV64_OBJ) build/lib/rv64/$(LIBFEMTO_LIB) build/lib/rv64/$(UART_SPIKE_HTIF_LIB)
	$(call cmd,LD.64 $@,$(@D),$(CC_64) $(LDFLAGS) -T ${ENV_SPIKE_LD_SCRIPT} $^ -o $@)

build/bin/rv32/probe-virt: $(EXAMPLE_PROBE_RV32_OBJ) build/lib/rv32/$(LIBFEMTO_LIB) build/lib/rv32/$(UART_VIRT_16550_LIB)
	$(call cmd,LD.32 $@,$(@D),$(CC_32) $(LDFLAGS) -T ${ENV_VIRT_LD_SCRIPT} $^ -o $@)

build/bin/rv64/probe-virt: $(EXAMPLE_PROBE_RV64_OBJ) build/lib/rv64/$(LIBFEMTO_LIB) build/lib/rv64/$(UART_VIRT_16550_LIB)
	$(call cmd,LD.64 $@,$(@D),$(CC_64) $(LDFLAGS) -T ${ENV_VIRT_LD_SCRIPT} $^ -o $@)

build/bin/rv32/probe-qemu-sifive_e: $(EXAMPLE_PROBE_RV32_OBJ) build/lib/rv32/$(LIBFEMTO_LIB) build/lib/rv32/$(UART_QEMU_SIFIVE_LIB)
	$(call cmd,LD.32 $@,$(@D),$(CC_32) $(LDFLAGS) -T ${ENV_QEMU_SIFIVE_E_LD_SCRIPT} $^ -o $@)

build/bin/rv64/probe-qemu-sifive_e: $(EXAMPLE_PROBE_RV64_OBJ) build/lib/rv64/$(LIBFEMTO_LIB) build/lib/rv64/$(UART_QEMU_SIFIVE_LIB)
	$(call cmd,LD.64 $@,$(@D),$(CC_64) $(LDFLAGS) -T ${ENV_QEMU_SIFIVE_E_LD_SCRIPT} $^ -o $@)

build/bin/rv32/probe-qemu-sifive_u: $(EXAMPLE_PROBE_RV32_OBJ) build/lib/rv32/$(LIBFEMTO_LIB) build/lib/rv32/$(UART_QEMU_SIFIVE_LIB)
	$(call cmd,LD.32 $@,$(@D),$(CC_32) $(LDFLAGS) -T ${ENV_QEMU_SIFIVE_U_LD_SCRIPT} $^ -o $@)

build/bin/rv64/probe-qemu-sifive_u: $(EXAMPLE_PROBE_RV64_OBJ) build/lib/rv64/$(LIBFEMTO_LIB) build/lib/rv64/$(UART_QEMU_SIFIVE_LIB)
	$(call cmd,LD.64 $@,$(@D),$(CC_64) $(LDFLAGS) -T ${ENV_QEMU_SIFIVE_U_LD_SCRIPT} $^ -o $@)

build/bin/rv32/probe-coreip-e2-arty: $(EXAMPLE_PROBE_RV32_OBJ) build/lib/rv32/$(LIBFEMTO_LIB) build/lib/rv32/$(UART_COREIP_E2_ARTY_LIB)
	$(call cmd,LD.32 $@,$(@D),$(CC_32) $(LDFLAGS) -T ${ENV_COREIP_E2_ARTY_LD_SCRIPT} $^ -o $@)
