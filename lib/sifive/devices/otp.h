// SPDX-License-Identifier: Apache-2.0
#ifndef _SIFIVE_OTP_H
#define _SIFIVE_OTP_H

#include "sifive/const.h"

/* register offsets */
#define OTP_LOCK   _AC(0x00,UL)
#define OTP_CK     _AC(0x04,UL)
#define OTP_OE     _AC(0x08,UL)
#define OTP_SEL    _AC(0x0c,UL)
#define OTP_WE     _AC(0x10,UL)
#define OTP_MR     _AC(0x14,UL)
#define OTP_MRR    _AC(0x18,UL)
#define OTP_MPP    _AC(0x1c,UL)
#define OTP_VRREN  _AC(0x20,UL)
#define OTP_VPPEN  _AC(0x24,UL)
#define OTP_A      _AC(0x28,UL)
#define OTP_D      _AC(0x2c,UL)
#define OTP_Q      _AC(0x30,UL)
#define OTP_RSCTRL _AC(0x34,UL)

/* rsctrl register */
#define OTP_RSCTRL_SCALE_Pos 0
#define OTP_RSCTRL_SCALE_Msk _AC(0x00000007,U)
#define OTP_RSCTRL_SCALE(x)  ((x) << OTP_RSCTRL_SCALE_Pos)
#define OPT_RSCTRL_AS        _AC(0x00000008,U)
#define OPT_RSCTRL_RP        _AC(0x00000010,U)
#define OPT_RSCTRL_RACC      _AC(0x00000020,U)

#ifndef __ASSEMBLER__
#include <stdint.h>
struct otp {
	volatile uint32_t lock;
	volatile uint32_t ck;
	volatile uint32_t oe;
	volatile uint32_t sel;
	volatile uint32_t we;
	volatile uint32_t mr;
	volatile uint32_t mrr;
	volatile uint32_t mpp;
	volatile uint32_t vrren;
	volatile uint32_t vppen;
	volatile uint32_t a;
	volatile uint32_t d;
	volatile uint32_t q;
	volatile uint32_t rsctrl;
};
#endif
#endif
