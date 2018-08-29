RISCV_PREFIX                ?= riscv64-unknown-elf-

CC_32                        = $(RISCV_PREFIX)gcc -march=rv32imac -mabi=ilp32 -Ienv/common/rv32
CC_64                        = $(RISCV_PREFIX)gcc -march=rv64imac -mabi=lp64  -Ienv/common/rv64
AR                           = $(RISCV_PREFIX)ar

CFLAGS                       = -mcmodel=medany -Os
LDFLAGS                      = -nostartfiles -nostdlib -static -Wl,--nmagic
INCLUDES                     = -Ienv/common -Ilibfemto

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


#
# make rules
#

all: all_programs

clean:
	rm -fr build

backup: clean
	tar czf ../$(shell basename $(shell pwd)).tar.gz .

#
# To view commands use: make V=1
#

ifdef V
cmd = @mkdir -p $2 ; echo "$3"; $3
else
cmd = @echo "$1"; mkdir -p $2 ; $3
endif

#
# Generic pattern rules
#

build/obj/rv32/%.o: %.s
	$(call cmd,AS.32 $@,$(@D),$(CC_32) $(CFLAGS) $(INCLUDES) -c $^ -o $@)

build/obj/rv64/%.o: %.s
	$(call cmd,AS.64 $@,$(@D),$(CC_64) $(CFLAGS) $(INCLUDES) -c $^ -o $@)

build/obj/rv32/%.o: %.c
	$(call cmd,CC.32 $@,$(@D),$(CC_32) $(CFLAGS) $(INCLUDES) -c $^ -o $@)

build/obj/rv64/%.o: %.c
	$(call cmd,CC.64 $@,$(@D),$(CC_64) $(CFLAGS) $(INCLUDES) -c $^ -o $@)

#
# libfemto build rules
#

build/lib/rv32/$(LIBFEMTO_LIB): $(LIBFEMTO_RV32_OBJ)
	$(call cmd,AR.32 $@,$(@D),$(AR) cr $@ $^)

build/lib/rv64/$(LIBFEMTO_LIB): $(LIBFEMTO_RV64_OBJ)
	$(call cmd,AR.64 $@,$(@D),$(AR) cr $@ $^)

#
# libuart build rules
#

build/lib/rv32/$(UART_SPIKE_HTIF_LIB): $(UART_SPIKE_HTIF_RV32_OBJ)
	$(call cmd,AR.32 $@,$(@D),$(AR) cr $@ $^)

build/lib/rv64/$(UART_SPIKE_HTIF_LIB): $(UART_SPIKE_HTIF_RV64_OBJ)
	$(call cmd,AR.64 $@,$(@D),$(AR) cr $@ $^)

build/lib/rv32/$(UART_QEMU_SIFIVE_LIB): $(UART_QEMU_SIFIVE_RV32_OBJ)
	$(call cmd,AR.32 $@,$(@D),$(AR) cr $@ $^)

build/lib/rv64/$(UART_QEMU_SIFIVE_LIB): $(UART_QEMU_SIFIVE_RV64_OBJ)
	$(call cmd,AR.64 $@,$(@D),$(AR) cr $@ $^)

build/lib/rv32/$(UART_VIRT_16550_LIB): $(UART_VIRT_16550_RV32_OBJ)
	$(call cmd,AR.32 $@,$(@D),$(AR) cr $@ $^)

build/lib/rv64/$(UART_VIRT_16550_LIB): $(UART_VIRT_16550_RV64_OBJ)
	$(call cmd,AR.64 $@,$(@D),$(AR) cr $@ $^)

build/lib/rv32/$(UART_COREIP_E2_ARTY_LIB): $(UART_COREIP_E2_ARTY_RV32_OBJ)
	$(call cmd,AR.32 $@,$(@D),$(AR) cr $@ $^)

build/lib/rv64/$(UART_COREIP_E2_ARTY_LIB): $(UART_COREIP_E2_ARTY_RV64_OBJ)
	$(call cmd,AR.64 $@,$(@D),$(AR) cr $@ $^)

#
# Environment specific linker scripts
#

ALL_CONFIGS = build/bin/rv32/spike/ \
              build/bin/rv64/spike/ \
              build/bin/rv32/virt/ \
              build/bin/rv64/virt/ \
              build/bin/rv32/qemu-sifive_e/ \
              build/bin/rv64/qemu-sifive_e/ \
              build/bin/rv32/qemu-sifive_u/ \
              build/bin/rv64/qemu-sifive_u/ \
              build/bin/rv32/coreip-e2-arty/

define module =
project_names += $(2)
program_names += $(foreach cfg,$(ALL_CONFIGS),$(addprefix $(cfg),$(2)))

$(2)_objs := $(addprefix $(1)/,$($(2)_objs))
$(2)_rv32_objs := $(addprefix build/obj/rv32/$(1)/,$($(2)_objs))
$(2)_rv64_objs := $(addprefix build/obj/rv64/$(1)/,$($(2)_objs))

build/bin/rv32/spike/$(2): $$($(2)_rv32_objs) build/lib/rv32/$(LIBFEMTO_LIB) build/lib/rv32/$(UART_SPIKE_HTIF_LIB)
	$$(call cmd,LD.32 $$@,$$(@D),$$(CC_32) $$(LDFLAGS) -T env/spike/default.lds $$^ -o $$@)

build/bin/rv64/spike/$(2): $$($(2)_rv64_objs) build/lib/rv64/$(LIBFEMTO_LIB) build/lib/rv64/$(UART_SPIKE_HTIF_LIB)
	$$(call cmd,LD.64 $$@,$$(@D),$$(CC_64) $$(LDFLAGS) -T env/spike/default.lds $$^ -o $$@)

build/bin/rv32/virt/$(2): $$($(2)_rv32_objs) build/lib/rv32/$(LIBFEMTO_LIB) build/lib/rv32/$(UART_VIRT_16550_LIB)
	$$(call cmd,LD.32 $$@,$$(@D),$$(CC_32) $$(LDFLAGS) -T env/virt/default.lds $$^ -o $$@)

build/bin/rv64/virt/$(2): $$($(2)_rv64_objs) build/lib/rv64/$(LIBFEMTO_LIB) build/lib/rv64/$(UART_VIRT_16550_LIB)
	$$(call cmd,LD.64 $$@,$$(@D),$$(CC_64) $$(LDFLAGS) -T env/virt/default.lds $$^ -o $$@)

build/bin/rv32/qemu-sifive_e/$(2): $$($(2)_rv32_objs) build/lib/rv32/$(LIBFEMTO_LIB) build/lib/rv32/$(UART_QEMU_SIFIVE_LIB)
	$$(call cmd,LD.32 $$@,$$(@D),$$(CC_32) $$(LDFLAGS) -T env/qemu-sifive_e/default.lds $$^ -o $$@)

build/bin/rv64/qemu-sifive_e/$(2): $$($(2)_rv64_objs) build/lib/rv64/$(LIBFEMTO_LIB) build/lib/rv64/$(UART_QEMU_SIFIVE_LIB)
	$$(call cmd,LD.64 $$@,$$(@D),$$(CC_64) $$(LDFLAGS) -T env/qemu-sifive_e/default.lds $$^ -o $$@)

build/bin/rv32/qemu-sifive_u/$(2): $$($(2)_rv32_objs) build/lib/rv32/$(LIBFEMTO_LIB) build/lib/rv32/$(UART_QEMU_SIFIVE_LIB)
	$$(call cmd,LD.32 $$@,$$(@D),$$(CC_32) $$(LDFLAGS) -T env/qemu-sifive_u/default.lds $$^ -o $$@)

build/bin/rv64/qemu-sifive_u/$(2): $$($(2)_rv64_objs) build/lib/rv64/$(LIBFEMTO_LIB) build/lib/rv64/$(UART_QEMU_SIFIVE_LIB)
	$$(call cmd,LD.64 $$@,$$(@D),$$(CC_64) $$(LDFLAGS) -T env/qemu-sifive_u/default.lds $$^ -o $$@)

build/bin/rv32/coreip-e2-arty/$(2): $$($(2)_rv32_objs) build/lib/rv32/$(LIBFEMTO_LIB) build/lib/rv32/$(UART_COREIP_E2_ARTY_LIB)
	$$(call cmd,LD.32 $$@,$$(@D),$$(CC_32) $$(LDFLAGS) -T env/coreip-e2-arty/default.lds $$^ -o $$@)
endef

build_dirs = example
sub_makes := $(foreach dir,$(build_dirs),$(wildcard ${dir}/*/rules.mk))
$(foreach makefile,$(sub_makes),$(eval include $(makefile)))
sub_dirs := $(foreach m,$(sub_makes),$(m:/rules.mk=))
module_name = $(lastword $(subst /, ,$(1)))
$(foreach d,$(sub_dirs), $(eval $(call module,$(d),$(call module_name,$(d)))))

all_programs: $(program_names)
