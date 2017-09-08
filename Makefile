# SPDX-License-Identifier: Apache-2.0

BOARD = hifive1

include include.mk

obj-y += $(patsubst %.S,%.o,$(wildcard *.S))
obj-y += $(patsubst %.c,%.o,$(wildcard *.c))
