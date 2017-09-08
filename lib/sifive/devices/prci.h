// SPDX-License-Identifier: Apache-2.0
#ifndef _SIFIVE_PRCI_H
#define _SIFIVE_PRCI_H

#include "sifive/const.h"

/* register offsets */
#define PRCI_HFROSCCFG  _AC(0x00,UL)
#define PRCI_HFXOSCCFG  _AC(0x04,UL)
#define PRCI_PLLCFG     _AC(0x08,UL)
#define PRCI_PLLOUTDIV  _AC(0x0c,UL)
#define PRCI_PROCMONCFG _AC(0xf0,UL)

/* hfrosccfg register */
#define PRCI_HFROSCCFG_DIV_Pos        0
#define PRCI_HFROSCCFG_DIV_Msk        _AC(0x0000001f,U)
#define PRCI_HFROSCCFG_DIV(x)         ((x) << PRCI_HFROSCCFG_DIV_Pos)
#define PRCI_HFROSCCFG_DIV_DEFAULT    _AC(0x00000004,U)
#define PRCI_HFROSCCFG_TRIM_Pos       16
#define PRCI_HFROSCCFG_TRIM_Msk       _AC(0x001f0000,U)
#define PRCI_HFROSCCFG_TRIM(x)        ((x) << PRCI_HFROSCCFG_TRIM_Pos)
#define PRCI_HFROSCCFG_TRIM_DEFAULT   _AC(0x00100000,U)
#define PRCI_HFROSCCFG_EN             _AC(0x40000000,U)
#define PRCI_HFROSCCFG_RDY            _AC(0x80000000,U)

/* hfxosccfg register */
#define PRCI_HFXOSCCFG_EN             _AC(0x40000000,U)
#define PRCI_HFXOSCCFG_RDY            _AC(0x80000000,U)

/* pllcfg register */
#define PRCI_PLLCFG_R_Pos             0
#define PRCI_PLLCFG_R_Msk             _AC(0x00000007,U)
#define PRCI_PLLCFG_R(x)              ((x) << PRCI_PLLCFG_R_Pos)
#define PRCI_PLLCFG_R_DEFAULT         _AC(0x00000001,U)
#define PRCI_PLLCFG_F_Pos             4
#define PRCI_PLLCFG_F_Msk             _AC(0x000003f0,U)
#define PRCI_PLLCFG_F(x)              ((x) << PRCI_PLLCFG_F_Pos)
#define PRCI_PLLCFG_F_DEFAULT         _AC(0x000001f0,U)
#define PRCI_PLLCFG_Q_Pos             10
#define PRCI_PLLCFG_Q_Msk             _AC(0x00000c00,U)
#define PRCI_PLLCFG_Q(x)              ((x) << PRCI_PLLCFG_Q_Pos)
#define PRCI_PLLCFG_Q_DEFAULT         _AC(0x00000c00,U)
#define PRCI_PLLCFG_SEL               _AC(0x00010000,U)
#define PRCI_PLLCFG_REFSEL            _AC(0x00020000,U)
#define PRCI_PLLCFG_BYPASS            _AC(0x00040000,U)
#define PRCI_PLLCFG_LOCK              _AC(0x80000000,U)

/* plldiv register */
#define PRCI_PLLOUTDIV_DIV_Pos        0
#define PRCI_PLLOUTDIV_DIV_Msk        _AC(0x0000003f,U)
#define PRCI_PLLOUTDIV_DIV(x)         ((x) << PRCI_PLLOUTDIV_DIV_Pos)
#define PRCI_PLLOUTDIV_DIV_DEFAULT    _AC(0x00000000,U)
#define PRCI_PLLOUTDIV_DIVBY1         _AC(0x00000100,U)

/* procmoncfg register */
#define PRCI_PROCMONCFG_DIV_Pos       0
#define PRCI_PROCMONCFG_DIV_Msk       _AC(0x0000001f,U)
#define PRCI_PROCMONCFG_DIV(x)        ((x) << PRCI_PROCMONCFG_DIV_Pos)
#define PRCI_PROCMONCFG_TRIM_Pos      8
#define PRCI_PROCMONCFG_TRIM_Msk      _AC(0x00001f00,U)
#define PRCI_PROCMONCFG_TRIM(x)       (((x) & 0x1f) << 8)
#define PRCI_PROCMONCFG_EN            _AC(0x00010000,U)
#define PRCI_PROCMONCFG_SEL_Pos       24
#define PRCI_PROCMONCFG_SEL_Msk       _AC(0x03000000)
#define PRCI_PROCMONCFG_SEL(x)        ((x) << PRCI_PROCMONCFG_SEL_Pos)
#define PRCI_PROCMONCFG_SEL_HFCLK     _AC(0x00000000,U)
#define PRCI_PROCMONCFG_SEL_HFXOSCIN  _AC(0x01000000,U)
#define PRCI_PROCMONCFG_SEL_PLLOUTDIV _AC(0x02000000,U)
#define PRCI_PROCMONCFG_SEL_PROCMON   _AC(0x03000000,U)
#define PRCI_PROCMONCFG_NTEN          _AC(0x10000000,U)

#ifndef __ASSEMBLER__
#include <stdint.h>
struct prci {
	volatile uint32_t hfrosccfg;
	volatile uint32_t hfxosccfg;
	volatile uint32_t pllcfg;
	volatile uint32_t plloutdiv;
	uint32_t reserved[56];
	volatile uint32_t procmoncfg;
};
#endif
#endif
