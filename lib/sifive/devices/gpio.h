// SPDX-License-Identifier: Apache-2.0
#ifndef _SIFIVE_GPIO_H
#define _SIFIVE_GPIO_H

#include "sifive/const.h"

#define GPIO_VALUE      _AC(0x00,UL)
#define GPIO_INPUT_EN   _AC(0x04,UL)
#define GPIO_OUTPUT_EN  _AC(0x08,UL)
#define GPIO_PORT       _AC(0x0c,UL)
#define GPIO_PUE        _AC(0x10,UL)
#define GPIO_DS         _AC(0x14,UL)
#define GPIO_RISE_IE    _AC(0x18,UL)
#define GPIO_RISE_IP    _AC(0x1c,UL)
#define GPIO_FALL_IE    _AC(0x20,UL)
#define GPIO_FALL_IP    _AC(0x24,UL)
#define GPIO_HIGH_IE    _AC(0x28,UL)
#define GPIO_HIGH_IP    _AC(0x2c,UL)
#define GPIO_LOW_IE     _AC(0x30,UL)
#define GPIO_LOW_IP     _AC(0x34,UL)
#define GPIO_IOF_EN     _AC(0x38,UL)
#define GPIO_IOF_SEL    _AC(0x3c,UL)
#define GPIO_OUT_XOR    _AC(0x40,UL)

#ifndef __ASSEMBLER__
#include <stdint.h>
struct gpio {
	volatile uint32_t value;
	volatile uint32_t input_en;
	volatile uint32_t output_en;
	volatile uint32_t port;
	volatile uint32_t pue;
	volatile uint32_t ds;
	volatile uint32_t rise_ie;
	volatile uint32_t rise_ip;
	volatile uint32_t fall_ie;
	volatile uint32_t fall_ip;
	volatile uint32_t high_ie;
	volatile uint32_t high_ip;
	volatile uint32_t low_ie;
	volatile uint32_t low_ip;
	volatile uint32_t iof_en;
	volatile uint32_t iof_sel;
	volatile uint32_t out_xor;
};
#endif
#endif
