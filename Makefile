RISCV_PREFIX       ?= riscv64-unknown-elf-

CFLAGS_rv32        = -march=rv32imac -mabi=ilp32 -Ienv/common/rv32
CFLAGS_rv64        = -march=rv64imac -mabi=lp64  -Ienv/common/rv64

CC_rv32            = $(RISCV_PREFIX)gcc $(CFLAGS_rv32)
CC_rv64            = $(RISCV_PREFIX)gcc $(CFLAGS_rv64)
AR                 = $(RISCV_PREFIX)ar

CFLAGS             = -mcmodel=medany -Os -ffunction-sections
LDFLAGS            = -nostartfiles -nostdlib -static \
                     -Wl,--nmagic -Wl,--gc-sections
INCLUDES           = -Ienv/common -Ilibfemto

LIBFEMTO_SRCS      = $(sort $(wildcard libfemto/*.c))
LIBFEMTO_ASM       = $(sort $(wildcard libfemto/*.s))
LIBFEMTO_OBJS      = $(patsubst %.s,%.o,$(LIBFEMTO_ASM)) \
                     $(patsubst %.c,%.o,$(LIBFEMTO_SRCS))
LIBFEMTO_RV32_OBJ  = $(addprefix build/obj/rv32/,$(LIBFEMTO_OBJS))
LIBFEMTO_RV64_OBJ  = $(addprefix build/obj/rv64/,$(LIBFEMTO_OBJS))

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
	$(call cmd,AS.rv32 $@,$(@D),$(CC_rv32) $(CFLAGS) $(INCLUDES) -c $^ -o $@)

build/obj/rv64/%.o: %.s
	$(call cmd,AS.rv64 $@,$(@D),$(CC_rv64) $(CFLAGS) $(INCLUDES) -c $^ -o $@)

build/obj/rv32/%.o: %.c
	$(call cmd,CC.rv32 $@,$(@D),$(CC_rv32) $(CFLAGS) $(INCLUDES) -c $^ -o $@)

build/obj/rv64/%.o: %.c
	$(call cmd,CC.rv64 $@,$(@D),$(CC_rv64) $(CFLAGS) $(INCLUDES) -c $^ -o $@)

#
# libfemto build rules
#

build/lib/rv32/libfemto.a: $(LIBFEMTO_RV32_OBJ)
	$(call cmd,AR.rv32 $@,$(@D),$(AR) cr $@ $^)

build/lib/rv64/libfemto.a: $(LIBFEMTO_RV64_OBJ)
	$(call cmd,AR.rv64 $@,$(@D),$(AR) cr $@ $^)

#
# libuart build rules
#

build/lib/rv32/libuart_spike_htif.a: build/obj/rv32/libuart/uart_spike_htif.o
	$(call cmd,AR.rv32 $@,$(@D),$(AR) cr $@ $^)

build/lib/rv64/libuart_spike_htif.a: build/obj/rv64/libuart/uart_spike_htif.o
	$(call cmd,AR.rv64 $@,$(@D),$(AR) cr $@ $^)

build/lib/rv32/libuart_qemu_sifive.a: build/obj/rv32/libuart/uart_qemu_sifive.o
	$(call cmd,AR.rv32 $@,$(@D),$(AR) cr $@ $^)

build/lib/rv64/libuart_qemu_sifive.a: build/obj/rv64/libuart/uart_qemu_sifive.o
	$(call cmd,AR.rv64 $@,$(@D),$(AR) cr $@ $^)

build/lib/rv32/libuart_virt_16550.a: build/obj/rv32/libuart/uart_virt_16550.o
	$(call cmd,AR.rv32 $@,$(@D),$(AR) cr $@ $^)

build/lib/rv64/libuart_virt_16550.a: build/obj/rv64/libuart/uart_virt_16550.o
	$(call cmd,AR.rv64 $@,$(@D),$(AR) cr $@ $^)

build/lib/rv32/libuart_coreip_e2_arty.a: build/obj/rv32/libuart/uart_coreip_e2_arty.o
	$(call cmd,AR.rv32 $@,$(@D),$(AR) cr $@ $^)

#
# Target environment definitions
#

configs = rv32:spike:libuart_spike_htif.a \
          rv64:spike:libuart_spike_htif.a \
          rv32:virt:libuart_virt_16550.a \
          rv64:virt:libuart_virt_16550.a \
          rv32:qemu-sifive_e:libuart_qemu_sifive.a \
          rv64:qemu-sifive_e:libuart_qemu_sifive.a \
          rv32:qemu-sifive_u:libuart_qemu_sifive.a \
          rv64:qemu-sifive_u:libuart_qemu_sifive.a \
          rv32:coreip-e2-arty::libuart_coreip_e2_arty.a

#
# Build system functions to generate build rules for examples
#

build_dirs = examples
sub_makes := $(foreach dir,$(build_dirs),$(wildcard ${dir}/*/rules.mk))
$(foreach makefile,$(sub_makes),$(eval include $(makefile)))
sub_dirs := $(foreach m,$(sub_makes),$(m:/rules.mk=))
module_name = $(lastword $(subst /, ,$(1)))
module_objs = $(addprefix build/obj/$(3)/,$(addprefix $(2)/,$($(1)_objs)))
config_arch = $(word 1,$(subst :, ,$(1)))
config_env = $(word 2,$(subst :, ,$(1)))
config_lib = $(word 3,$(subst :, ,$(1)))

define rule =
build/bin/$(3)/$(4)/$(1): $(2) build/lib/$(3)/libfemto.a build/lib/$(3)/$(5)
	$$(call cmd,LD.$(3) $$@,$$(@D),$(CC_$(3)) $$(LDFLAGS) \
	-T env/$(4)/default.lds $$^ -o $$@)
endef

define module =
program_names += $(foreach cfg,$(configs),build/bin/$(call \
  config_arch,$(cfg))/$(call config_env,$(cfg))/$(1))

$(foreach cfg,$(configs),$(eval $(call rule,$(1),$(call \
  module_objs,$(1),$(2),$(call config_arch,$(cfg))),$(call \
  config_arch,$(cfg)),$(call config_env,$(cfg)),$(call config_lib,$(cfg)))))
endef

$(foreach d,$(sub_dirs),$(eval $(call module,$(call module_name,$(d)),$(d))))

all_programs: $(program_names)
