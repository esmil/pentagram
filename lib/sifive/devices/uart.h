// SPDX-License-Identifier: Apache-2.0
#ifndef _SIFIVE_UART_H
#define _SIFIVE_UART_H

#include "sifive/const.h"

/* register offsets */
#define UART_TXDATA _AC(0x00,UL)
#define UART_RXDATA _AC(0x04,UL)
#define UART_TXCTRL _AC(0x08,UL)
#define UART_RXCTRL _AC(0x0c,UL)
#define UART_IE     _AC(0x10,UL)
#define UART_IP     _AC(0x14,UL)
#define UART_DIV    _AC(0x18,UL)

/* txctrl register */
#define UART_TXCTRL_TXEN          _AC(0x00000001,U)
#define UART_TXCTRL_NSTOP         _AC(0x00000002,U)
#define UART_TXCTRL_TXCNT_Pos     16
#define UART_TXCTRL_TXCNT_Msk     _AC(0x00070000,U)
#define UART_TXCTRL_TXCNT(x)      ((x) << UART_TXCTRL_TXCNT_Pos)
#define UART_TXCTRL_TXCNT_DEFAULT _AC(0x00000000,U)

/* rxctrl register */
#define UART_RXCTRL_RXEN          _AC(0x00000001,U)
#define UART_RXCTRL_RXCNT_Pos     16
#define UART_RXCTRL_RXCNT_Msk     _AC(0x00070000,U)
#define UART_RXCTRL_RXCNT(x)      ((x) << UART_RXCTRL_RXCNT_Pos)
#define UART_RXCTRL_RXCNT_DEFAULT _AC(0x00000000,U)

/* ie register */
#define UART_IE_TXWM              _AC(0x00000001,U)
#define UART_IE_RXWM              _AC(0x00000002,U)

/* ip register */
#define UART_IP_TXWM              _AC(0x00000001,U)
#define UART_IP_RXWM              _AC(0x00000002,U)

/* div register */
#define UART_DIV_DIV_Pos          0
#define UART_DIV_DIV_Msk          _AC(0x0000ffff,U)
#define UART_DIV_DIV(x)           ((x) << UART_DIV_DIV_Pos)
#define UART_DIV_DIV_DEFAULT      _AC(0x0000ffff,U)

#ifndef __ASSEMBLER__
#include <stdint.h>
struct uart {
	volatile int32_t txdata;
	volatile int32_t rxdata;
	volatile uint32_t txctrl;
	volatile uint32_t rxctrl;
	volatile uint32_t ie;
	volatile uint32_t ip;
	volatile uint32_t div;
};

static inline __attribute__((const)) uint32_t
uart_div(uint32_t tlclk, uint32_t target)
{
	return ((tlclk + target/2)/target) - 1;
}
#endif
#endif
