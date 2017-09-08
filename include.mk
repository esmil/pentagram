# SPDX-License-Identifier: Apache-2.0

NAME       = code
OUTDIR     = out

MAKEFLAGS  = -rR
TOPDIR    := $(dir $(lastword $(MAKEFILE_LIST)))
VPATH      = .:$(TOPDIR)boards/$(BOARD):$(TOPDIR)lib

CROSS_COMPILE = riscv64-unknown-elf-
RISCV_ARCH    = rv32i
RISCV_ABI     = ilp32
RISCV_MODEL   = medlow

AS         = $(CROSS_COMPILE)gcc
CC         = $(CROSS_COMPILE)gcc -std=gnu99
OBJCOPY    = $(CROSS_COMPILE)objcopy
OBJDUMP    = $(CROSS_COMPILE)objdump
HEX        = $(OBJCOPY) -O ihex
BIN        = $(OBJCOPY) -O binary -S
DIS        = $(OBJDUMP) -d -j .init -j .text -j .fini -j .rodata -j .ctors -j .dtors -j .lalign
OPENOCD    = riscv-openocd
PAGER     ?= less

COMMENT    = \#
MKDIR_P    = mkdir -p
RM_RF      = rm -rf
FILESIZE   = stat --printf '    %s bytes\n'

OPT        = -Os
LTO        = -flto
ARCHFLAGS  = -march=$(RISCV_ARCH) -mabi=$(RISCV_ABI) -mcmodel=$(RISCV_MODEL)
CFLAGS     = $(ARCHFLAGS) $(OPT) -ggdb -pipe $(LTO) -fdata-sections -ffunction-sections
CFLAGS    += -Wall -Wextra -Wno-unused-parameter
ASFLAGS    = $(ARCHFLAGS)
CPPFLAGS   = -iquote '$(TOPDIR)boards/$(BOARD)' -iquote '$(TOPDIR)lib'
LIBS       = -lc -lm -lnosys
LDFLAGS    = $(LTO) $(ARCHFLAGS) $(OPT) -nostartfiles -Wl,-O1,--gc-sections -T '$(LDSCRIPT)'

ifdef ENABLE_EXIT
CPPFLAGS += -DENABLE_EXIT
endif

ifdef ENABLE_CXX
CPPFLAGS += -DENABLE_CXX
endif

include $(TOPDIR)boards/$(BOARD)/settings.mk

ifdef R
CPPFLAGS += -DNDEBUG
objects = $(patsubst %,$(OUTDIR)/%,$(obj-y))
else
objects = $(patsubst %,$(OUTDIR)/%,$(obj-y) $(obj-d))
endif

ifdef V
E=@$(COMMENT)
Q=
else
E=@echo
Q=@
endif

.SECONDEXPANSION:
.PHONY: all dis clean flash
.PRECIOUS: %.o $(OUTDIR)/ $(OUTDIR)%/

all: $(OUTDIR)/$(NAME).bin

$(OUTDIR)/:
	$E '  MKDIR   $@'
	$Q$(MKDIR_P) $@

$(OUTDIR)%/:
	$E '  MKDIR   $@'
	$Q$(MKDIR_P) $@

$(OUTDIR)/%.o: %.S $(MAKEFILE_LIST) | $$(@D)/
	$E '  AS      $@'
	$Q$(AS) -o $@ -c $(ASFLAGS) $(CPPFLAGS) $<

$(OUTDIR)/%.o: %.c $(MAKEFILE_LIST) | $$(@D)/
	$E '  CC      $@'
	$Q$(CC) -o $@ -c $(CFLAGS) $(CPPFLAGS) $<

$(OUTDIR)/$(NAME).elf: $$(objects) $(MAKEFILE_LIST)
	$E '  LD      $@'
	$Q$(CC) -o $@ $(LDFLAGS) $(objects) $(LIBS)

$(OUTDIR)/$(NAME).hex: $(OUTDIR)/$(NAME).elf $(MAKEFILE_LIST)
	$E '  OBJCOPY $@'
	$Q$(HEX) $< $@

$(OUTDIR)/$(NAME).bin: $(OUTDIR)/$(NAME).elf $(MAKEFILE_LIST)
	$E '  OBJCOPY $@'
	$Q$(BIN) $< $@
	-$Q$(FILESIZE) $@ 2>/dev/null

$(OUTDIR)/%.lss: $(OUTDIR)/%.elf $(MAKEFILE_LIST)
	$E '  OBJDUMP $@'
	$Q$(DIS) $< > $@

dis: $(OUTDIR)/$(NAME).lss
	$(PAGER) $<

clean:
	$E '  RM      $(OUTDIR)'
	$Q$(RM_RF) $(OUTDIR)

flash: $(OUTDIR)/$(NAME).elf
	$(OPENOCD) \
	  -f '$(TOPDIR)boards/$(BOARD)/openocd.cfg' \
	  -c $(call OPENOCD_PROGRAM,$<)

openocd:
	$(OPENOCD) -f '$(TOPDIR)boards/$(BOARD)/openocd.cfg'
