// SPDX-License-Identifier: Apache-2.0
#ifndef _SIFIVE_AON_H
#define _SIFIVE_AON_H

#include "sifive/const.h"

/* wdt register offsets */
#define AON_WDOGCFG     _AC(0x000,UL)
#define AON_WDOGCOUNT   _AC(0x008,UL)
#define AON_WDOGS       _AC(0x010,UL)
#define AON_WDOGFEED    _AC(0x018,UL)
#define AON_WDOGKEY     _AC(0x01c,UL)
#define AON_WDOGCMP     _AC(0x020,UL)

/* rtc register offsets */
#define AON_RTCCFG      _AC(0x040,UL)
#define AON_RTCLO       _AC(0x048,UL)
#define AON_RTCHI       _AC(0x04c,UL)
#define AON_RTCS        _AC(0x050,UL)
#define AON_RTCCMP      _AC(0x060,UL)

/* lfrosccfg register offset */
#define AON_LFROSCCFG   _AC(0x070,UL)

/* backup register offsets */
#define AON_BACKUP0     _AC(0x080,UL)
#define AON_BACKUP1     _AC(0x084,UL)
#define AON_BACKUP2     _AC(0x088,UL)
#define AON_BACKUP3     _AC(0x08c,UL)
#define AON_BACKUP4     _AC(0x090,UL)
#define AON_BACKUP5     _AC(0x094,UL)
#define AON_BACKUP6     _AC(0x098,UL)
#define AON_BACKUP7     _AC(0x09c,UL)
#define AON_BACKUP8     _AC(0x0a0,UL)
#define AON_BACKUP9     _AC(0x0a4,UL)
#define AON_BACKUP10    _AC(0x0a8,UL)
#define AON_BACKUP11    _AC(0x0ac,UL)
#define AON_BACKUP12    _AC(0x0b0,UL)
#define AON_BACKUP13    _AC(0x0b4,UL)
#define AON_BACKUP14    _AC(0x0b8,UL)
#define AON_BACKUP15    _AC(0x0bc,UL)

/* pmu register offsets */
#define AON_PMUWAKEUPI0 _AC(0x100,UL)
#define AON_PMUWAKEUPI1 _AC(0x104,UL)
#define AON_PMUWAKEUPI2 _AC(0x108,UL)
#define AON_PMUWAKEUPI3 _AC(0x10c,UL)
#define AON_PMUWAKEUPI4 _AC(0x110,UL)
#define AON_PMUWAKEUPI5 _AC(0x114,UL)
#define AON_PMUWAKEUPI6 _AC(0x118,UL)
#define AON_PMUWAKEUPI7 _AC(0x11c,UL)
#define AON_PMUSLEEPI0  _AC(0x120,UL)
#define AON_PMUSLEEPI1  _AC(0x124,UL)
#define AON_PMUSLEEPI2  _AC(0x128,UL)
#define AON_PMUSLEEPI3  _AC(0x12c,UL)
#define AON_PMUSLEEPI4  _AC(0x130,UL)
#define AON_PMUSLEEPI5  _AC(0x134,UL)
#define AON_PMUSLEEPI6  _AC(0x138,UL)
#define AON_PMUSLEEPI7  _AC(0x13c,UL)
#define AON_PMUIE       _AC(0x140,UL)
#define AON_PMUCAUSE    _AC(0x144,UL)
#define AON_PMUSLEEP    _AC(0x148,UL)
#define AON_PMUKEY      _AC(0x14c,UL)

/* wdogcfg register */
#define AON_WDOGCFG_SCALE_Pos            0
#define AON_WDOGCFG_SCALE_Msk            _AC(0x000000ff,U)
#define AON_WDOGCFG_SCALE(x)             ((x) << AON_WDOGCFG_SCALE_Pos)
#define AON_WDOGCFG_RSTEN                _AC(0x00000100,U)
#define AON_WDOGCFG_ZEROCMP              _AC(0x00000200,U)
#define AON_WDOGCFG_ENALWAYS             _AC(0x00001000,U)
#define AON_WDOGCFG_ENCOREAWAKE          _AC(0x00002000,U)
#define AON_WDOGCFG_CMPIP                _AC(0x10000000,U)

/* wdogkey register */
#define AON_WDOGKEY_UNLOCK               _AC(0x0051f15e,U)

/* wdogfeed register */
#define AON_WDOGFEED_FEED                _AC(0x0d09f00d,U)

/* rtccfg register */
#define AON_RTCCFG_SCALE_Pos             0
#define AON_RTCCFG_SCALE_Msk             _AC(0x0000000f,U)
#define AON_RTCCFG_SCALE(x)              ((x) << AON_RTCCFG_SCALE_Pos)
#define AON_RTCCFG_ENALWAYS              _AC(0x00001000,U)
#define AON_RTCCFG_CMPIP                 _AC(0x10000000,U)

/* lfrosccfg register */
#define AON_LFROSCCFG_DIV_Pos            0
#define AON_LFROSCCFG_DIV_Msk            _AC(0x0000001f,U)
#define AON_LFROSCCFG_DIV(x)             ((x) << AON_LFROSCCFG_DIV_Pos)
#define AON_LFROSCCFG_DIV_DEFAULT        _AC(0x00000004,U)
#define AON_LFROSCCFG_TRIM_Pos           16
#define AON_LFROSCCFG_TRIM_Msk           _AC(0x001f0000,U)
#define AON_LFROSCCFG_TRIM(x)            ((x) << AON_LFROSCCFG_TRIM_Pos)
#define AON_LFROSCCFG_TRIM_DEFAULT       _AC(0x00100000,U)
#define AON_LFROSCCFG_EN                 _AC(0x40000000,U)
#define AON_LFROSCCFG_RDY                _AC(0x80000000,U)

/* pmuwakeupi register */
#define AON_PMUWAKEUPI_DELAY_Pos         0
#define AON_PMUWAKEUPI_DELAY_Msk         _AC(0x0000000f,U)
#define AON_PMUWAKEUPI_DELAY(x)          ((x) << AON_PMUWAKEUPI_DELAY_Pos)
#define AON_PMUWAKEUPI_VDDPADEN          _AC(0x00000020,U)
#define AON_PMUWAKEUPI_CORERST           _AC(0x00000080,U)
#define AON_PMUWAKEUPI_HFCLKRST          _AC(0x00000100,U)

/* pmusleepi register */
#define AON_PMUSLEEPI_DELAY_Pos          0
#define AON_PMUSLEEPI_DELAY_Msk          _AC(0x0000000f,U)
#define AON_PMUSLEEPI_DELAY(x)           ((x) << AON_PMUSLEEPI_DELAY_Pos)
#define AON_PMUSLEEPI_VDDPADEN           _AC(0x00000020,U)
#define AON_PMUSLEEPI_CORERST            _AC(0x00000080,U)
#define AON_PMUSLEEPI_HFCLKRST           _AC(0x00000100,U)

/* pmuie register */
#define AON_PMUIE_RTC                    _AC(0x00000002,U)
#define AON_PMUIE_DWAKEUP                _AC(0x00000004,U)
#define AON_PMUIE_AWAKEUP                _AC(0x00000008,U)

/* pmucause register */
#define AON_PMUCAUSE_WAKEUPCAUSE_Pos     0
#define AON_PMUCAUSE_WAKEUPCAUSE_Msk     _AC(0x00000003,U)
#define AON_PMUCAUSE_WAKEUPCAUSE_RESET   _AC(0x00000000,U)
#define AON_PMUCAUSE_WAKEUPCAUSE_RTC     _AC(0x00000001,U)
#define AON_PMUCAUSE_WAKEUPCAUSE_DWAKEUP _AC(0x00000002,U)
#define AON_PMUCAUSE_WAKEUPCAUSE_AWAKEUP _AC(0x00000003,U)
#define AON_PMUCAUSE_RESETCAUSE_Pos      8
#define AON_PMUCAUSE_RESETCAUSE_Msk      _AC(0x00000300,U)
#define AON_PMUCAUSE_RESETCAUSE_POWERON  _AC(0x00000000,U)
#define AON_PMUCAUSE_RESETCAUSE_EXTERNAL _AC(0x00000100,U)
#define AON_PMUCAUSE_RESETCAUSE_WATCHDOG _AC(0x00000200,U)

/* pmukey register */
#define AON_PMUKEY_KEY                   _AC(0x0051f15e,U)

#ifndef __ASSEMBLER__
#include <stdint.h>
struct aon {
	volatile uint32_t wdogcfg;
	uint32_t reserved1;
	volatile uint32_t wdogcount;
	uint32_t reserved2;
	volatile uint32_t wdogs;
	uint32_t reserved3;
	volatile uint32_t wdogfeed;
	volatile uint32_t wdogkey;
	volatile uint32_t wdogcmp;
	uint32_t reserved4[7];
	volatile uint32_t rtccfg;
	uint32_t reserved5;
	union {
		struct {
			volatile uint32_t rtclo;
			volatile uint32_t rtchi;
		};
		volatile uint64_t rtccount;
	};
	volatile uint32_t rtcs;
	uint32_t reserved6[3];
	volatile uint32_t rtccmp;
	uint32_t reserved7[3];
	volatile uint32_t lfrosccfg;
	uint32_t reserved8[3];
	volatile uint32_t backup[16];
	uint32_t reserved9[16];
	volatile uint32_t pmuwakeupi[8];
	volatile uint32_t pmusleepi[8];
	volatile uint32_t pmuie;
	volatile uint32_t pmucause;
	volatile uint32_t pmusleep;
	volatile uint32_t pmukey;
};
#endif
#endif
