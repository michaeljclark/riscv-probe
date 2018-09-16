CROSS_COMPILE      ?= riscv64-unknown-elf-

AR                 = $(CROSS_COMPILE)ar

CFLAGS             = -mcmodel=medany -ffunction-sections -fdata-sections
LDFLAGS            = -nostartfiles -nostdlib -nostdinc -static -lgcc \
                     -Wl,--nmagic -Wl,--gc-sections
INCLUDES           = -Ienv/common

libfemto_dirs      = libfemto/std libfemto/drivers libfemto/arch/riscv
libfemto_src       = $(sort $(foreach d,$(libfemto_dirs),$(wildcard $(d)/*.c)))
libfemto_asm       = $(sort $(foreach d,$(libfemto_dirs),$(wildcard $(d)/*.s)))
libfemto_objs      = $(patsubst %.s,%.o,$(libfemto_asm)) \
                     $(patsubst %.c,%.o,$(libfemto_src))

#
# Compiler configurations and target environment definitions
#

subdirs            = examples

libs               = libfemto

configs            = rv32imac rv64imac

CC_rv32imac        = $(CROSS_COMPILE)gcc
CFLAGS_rv32imac    = -Os -march=rv32imac -mabi=ilp32 -Ienv/common/rv32
LDFLAGS_rv32imac   =

CC_rv64imac        = $(CROSS_COMPILE)gcc
CFLAGS_rv64imac    = -Os -march=rv64imac -mabi=lp64  -Ienv/common/rv64
LDFLAGS_rv64imac   =

targets            = rv32imac:default \
                     rv64imac:default \
                     rv32imac:spike \
                     rv64imac:spike \
                     rv32imac:virt \
                     rv64imac:virt \
                     rv32imac:qemu-sifive_e \
                     rv64imac:qemu-sifive_e \
                     rv32imac:qemu-sifive_u \
                     rv64imac:qemu-sifive_u \
                     rv32imac:coreip-e2-arty

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
# Build system functions to generate pattern rules for all configs
#

define pattern =
build/obj/$(2)/%.o: %.$(3)
	$(call cmd,$(1).$(2) $$@,$$(@D),$(CC_$(2)) $(CFLAGS_$(2)) $(CFLAGS) \
	$$(INCLUDES) -c $$^ -o $$@)
endef

$(foreach c,$(configs),$(eval $(call pattern,CC,$(c),c)))
$(foreach c,$(configs),$(eval $(call pattern,AS,$(c),s)))

#
# Build system functions to generate library rules for all configs
#

define archive =
build/lib/$(2)/$(3).a: $(addprefix build/obj/$(2)/,$($(3)_objs))
	$(call cmd,$(1).$(2) $$@,$$(@D),$(AR) cr $$@ $$^)
LIBS_$(2) += build/lib/$(2)/$(3).a
endef

define lib =
$(foreach c,$(configs),$(eval $(call archive,AR,$(c),$(1))))
INCLUDES += -I$(1)/include
endef

$(foreach l,$(libs),$(eval $(call lib,$(l))))

#
# Build system functions to generate build rules for all subdirs
#

sub_makes := $(foreach dir,$(subdirs),$(wildcard ${dir}/*/rules.mk))
$(foreach makefile,$(sub_makes),$(eval include $(makefile)))
sub_dirs := $(foreach m,$(sub_makes),$(m:/rules.mk=))
module_name = $(lastword $(subst /, ,$(1)))
module_objs = $(addprefix build/obj/$(3)/,$(addprefix $(2)/,$($(1)_objs)))
config_arch = $(word 1,$(subst :, ,$(1)))
config_env = $(word 2,$(subst :, ,$(1)))

define rule =
build/bin/$(3)/$(4)/$(1): \
build/obj/$(3)/env/$(4)/crt.o build/obj/$(3)/env/$(4)/setup.o $(2) $$(LIBS_$(3))
	$$(call cmd,LD.$(3) $$@,$$(@D),$(CC_$(3)) $(CFLAGS_$(3)) $$(CFLAGS) \
	$$(LDFLAGS_$(3)) $$(LDFLAGS) -T env/$(4)/default.lds $$^ -o $$@)
endef

define module =
program_names += $(foreach cfg,$(targets),build/bin/$(call \
  config_arch,$(cfg))/$(call config_env,$(cfg))/$(1))

$(foreach cfg,$(targets),$(eval $(call rule,$(1),$(call \
  module_objs,$(1),$(2),$(call config_arch,$(cfg))),$(call \
  config_arch,$(cfg)),$(call config_env,$(cfg)))))
endef

$(foreach d,$(sub_dirs),$(eval $(call module,$(call module_name,$(d)),$(d))))

all_programs: $(program_names)
