// SPDX-License-Identifier: Apache-2.0
#ifndef _SIFIVE_PWM_H
#define _SIFIVE_PWM_H

#include "sifive/const.h"

/* register offsets */
#define PWM_CFG   _AC(0x00,UL)
#define PWM_COUNT _AC(0x08,UL)
#define PWM_S     _AC(0x10,UL)
#define PWM_CMP0  _AC(0x20,UL)
#define PWM_CMP1  _AC(0x24,UL)
#define PWM_CMP2  _AC(0x28,UL)
#define PWM_CMP3  _AC(0x2c,UL)

/* cfg register */
#define PWM_CFG_SCALE_Pos   0
#define PWM_CFG_SCALE_Msk   _AC(0x0000000f,U)
#define PWM_CFG_SCALE(x)    ((x) << PWM_CFG_SCALE_Pos)
#define PWM_CFG_STICKY      _AC(0x00000100,U)
#define PWM_CFG_ZEROCMP     _AC(0x00000200,U)
#define PWM_CFG_DEGLITCH    _AC(0x00000400,U)
#define PWM_CFG_ENALWAYS    _AC(0x00001000,U)
#define PWM_CFG_ONESHOT     _AC(0x00002000,U)
#define PWM_CFG_CMP0CENTER  _AC(0x00010000,U)
#define PWM_CFG_CMP1CENTER  _AC(0x00020000,U)
#define PWM_CFG_CMP2CENTER  _AC(0x00040000,U)
#define PWM_CFG_CMP3CENTER  _AC(0x00080000,U)
#define PWM_CFG_CMP0GANG    _AC(0x01000000,U)
#define PWM_CFG_CMP1GANG    _AC(0x02000000,U)
#define PWM_CFG_CMP2GANG    _AC(0x04000000,U)
#define PWM_CFG_CMP3GANG    _AC(0x08000000,U)
#define PWM_CFG_CMP0IP      _AC(0x10000000,U)
#define PWM_CFG_CMP1IP      _AC(0x20000000,U)
#define PWM_CFG_CMP2IP      _AC(0x40000000,U)
#define PWM_CFG_CMP3IP      _AC(0x80000000,U)

#ifndef __ASSEMBLER__
#include <stdint.h>
struct pwm {
	volatile uint32_t cfg;
	uint32_t reserved1;
	volatile uint32_t count;
	uint32_t reserved2;
	volatile uint32_t s;
	uint32_t reserved3[3];
	union {
		struct {
			volatile uint32_t cmp0;
			volatile uint32_t cmp1;
			volatile uint32_t cmp2;
			volatile uint32_t cmp3;
		};
		volatile uint32_t cmp[4];
	};
};
#endif
#endif
