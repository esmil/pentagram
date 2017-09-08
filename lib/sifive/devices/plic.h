// SPDX-License-Identifier: Apache-2.0
#ifndef _SIFIVE_PLIC_H
#define _SIFIVE_PLIC_H

#include "sifive/const.h"

/* register offsets */
#define PLIC_PRIORITY                   _AC(0x000000,UL)
#define PLIC_PENDING                    _AC(0x001000,UL)
#define PLIC_ENABLE                     _AC(0x002000,UL)
#define PLIC_THRESHOLD                  _AC(0x200000,UL)
#define PLIC_CLAIM_COMPLETE             _AC(0x200004,UL)

#ifndef __ASSEMBLER__
#include <stdint.h>
struct plic {
	volatile uint32_t priority[256];
	uint32_t reserved1[768];
	volatile uint32_t pending[8];
	uint32_t reserved2[1016];
	volatile uint32_t enable[8];
	uint32_t reserved3[522232];
	volatile uint32_t priority_threshold;
	volatile uint32_t claim_complete;
};

static inline void
plic_enable(struct plic *const plic, unsigned int nr)
{
	plic->enable[nr >> 5] |= 1U << (nr & 0x1FU);
}

static inline void
plic_disable(struct plic *const plic, unsigned int nr)
{
	plic->enable[nr >> 5] &= ~(1U << (nr & 0x1FU));
}

static inline uint32_t
plic_pending(struct plic *const plic, unsigned int nr)
{
	return plic->pending[nr >> 5] & (1U << (nr & 0x1FU));
}
#endif
#endif
