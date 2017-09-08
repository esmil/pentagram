// SPDX-License-Identifier: Apache-2.0
#ifndef _SIFIVE_CLINT_H
#define _SIFIVE_CLINT_H

#include "sifive/const.h"

#define CLINT_MSIP      _AC(0x0000,UL)
#define CLINT_MTIMECMP  _AC(0x4000,UL)
#define CLINT_MTIMECMPH _AC(0x4004,UL)
#define CLINT_MTIME     _AC(0xbff8,UL)
#define CLINT_MTIMEH    _AC(0xbffc,UL)

#ifndef __ASSEMBLER__
#include <stdint.h>
struct clint {
	volatile uint32_t msip;
	uint32_t reserved1[4095];
	union {
		volatile uint64_t mtimecmp;
		struct {
			volatile uint32_t mtimecmpl;
			volatile uint32_t mtimecmph;
		};
	};
	uint32_t reserved2[8188];
	union {
		volatile uint64_t mtime;
		struct {
			volatile uint32_t mtimel;
			volatile uint32_t mtimeh;
		};
	};
};
#endif
#endif
