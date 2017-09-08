# SPDX-License-Identifier: Apache-2.0

RISCV_ARCH = rv32imac
RISCV_ABI  = ilp32

LDSCRIPT = $(TOPDIR)boards/$(BOARD)/flash.ld

OPENOCD_PROGRAM = 'init; reset halt; flash protect 0 64 last off; program $(1) verify; exit'

obj-y = start.o sifive/fe310-g000-interrupts.o
