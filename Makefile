RISCV_PREFIX       ?= riscv64-unknown-elf-

AR                 = $(RISCV_PREFIX)ar

CFLAGS             = -mcmodel=medany -ffunction-sections -fdata-sections
LDFLAGS            = -nostartfiles -nostdlib -nostdinc -static -lgcc \
                     -Wl,--nmagic -Wl,--gc-sections
INCLUDES           = -Ienv/common -Ilibfemto/include

LIBFEMTO_DIRS      = libfemto/std libfemto/drivers libfemto/arch/riscv
LIBFEMTO_SRCS      = $(sort $(foreach d,$(LIBFEMTO_DIRS),$(wildcard $(d)/*.c)))
LIBFEMTO_ASM       = $(sort $(foreach d,$(LIBFEMTO_DIRS),$(wildcard $(d)/*.s)))
LIBFEMTO_OBJS      = $(patsubst %.s,%.o,$(LIBFEMTO_ASM)) \
                     $(patsubst %.c,%.o,$(LIBFEMTO_SRCS))

#
# Compiler configuration
#

configs            = rv32imac rv64imac

CC_rv32imac        = $(RISCV_PREFIX)gcc
CFLAGS_rv32imac    = -Os -march=rv32imac -mabi=ilp32 -Ienv/common/rv32
LDFLAGS_rv32imac   =

CC_rv64imac        = $(RISCV_PREFIX)gcc
CFLAGS_rv64imac    = -Os -march=rv64imac -mabi=lp64  -Ienv/common/rv64
LDFLAGS_rv64imac   =

#
# Target environment definitions
#

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
	$(INCLUDES) -c $$^ -o $$@)
endef

$(foreach c,$(configs),$(eval $(call pattern,CC,$(c),c)))
$(foreach c,$(configs),$(eval $(call pattern,AS,$(c),s)))

#
# Build system functions to generate libraries
#

define archive =
build/lib/$(2)/$(3): $(addprefix build/obj/$(2)/,$(4))
	$(call cmd,$(1).$(2) $$@,$$(@D),$(AR) cr $$@ $$^)
endef

$(foreach c,$(configs),$(eval $(call archive,AR,$(c),libfemto.a,$(LIBFEMTO_OBJS))))

#
# Build system functions to generate build rules for all targets
#

build_dirs = examples
sub_makes := $(foreach dir,$(build_dirs),$(wildcard ${dir}/*/rules.mk))
$(foreach makefile,$(sub_makes),$(eval include $(makefile)))
sub_dirs := $(foreach m,$(sub_makes),$(m:/rules.mk=))
module_name = $(lastword $(subst /, ,$(1)))
module_objs = $(addprefix build/obj/$(3)/,$(addprefix $(2)/,$($(1)_objs)))
config_arch = $(word 1,$(subst :, ,$(1)))
config_env = $(word 2,$(subst :, ,$(1)))

define rule =
build/bin/$(3)/$(4)/$(1): build/obj/$(3)/env/$(4)/setup.o $(2) \
build/lib/$(3)/libfemto.a
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
