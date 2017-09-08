// SPDX-License-Identifier: Apache-2.0

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>

#include "riscv/csr.h"
#include "riscv/bits.h"
#include "platform.h"

#include "uart0.h"

static const char pentagram_msg[] = "\n"
	"\n"
	"         5555555555555555555555555\n"
	"        55555                 55555\n"
	"       555555555           555555555\n"
	"      5555 55   5555   5555   55 5555\n"
	"     5555   55      555      55   5555\n"
	"    5555     55 5555   5555 55     5555\n"
	"   5555     5555           5555     5555\n"
	"  5555   555  55           55  555   5555\n"
	" 5555 555      55         55      555 5555\n"
	"5555555555555555555555555555555555555555555\n"
	" 55555          55       55          55555\n"
	"   55555         55     55         55555\n"
	"     55555       55     55       55555\n"
	"       55555      55   55      55555\n"
	"         55555     55 55     55555\n"
	"           55555   55 55   55555\n"
	"             55555  555  55555\n"
	"               5555  5  5555\n"
	"                 555555555\n"
	"                   55555\n"
	"                     5\n"
	"\n";

static void
plic_init(void)
{
	volatile uint32_t *p;

	for (p = plic->enable; p < ARRAY_END(plic->enable); p++)
		*p = 0;
	for (p = plic->priority; p < ARRAY_END(plic->priority); p++)
		*p = 0;
	plic->priority_threshold = 0;
}

static uint32_t
ecall2(uint32_t a0, uint32_t a1)
{
	register uint32_t _a0 __asm__ ("a0") = a0;
	register uint32_t _a1 __asm__ ("a1") = a1;
	register uint32_t ret __asm__ ("a0");
	__asm__ __volatile__ ("ecall" : "=r"(ret) : "r"(_a0), "r"(_a1));
	return ret;
}

void
fault_handler(long cause, struct fault_handler_args *args)
{
	unsigned long addr;

	switch (cause) {
	case 3: /* breakpoint */
		addr = csr_mepc();

		uart0_printf("BREAK: mepc=0x%08lx\n", addr);

		csr_mepc_set(addr+2);
		break;
	case 11: /* machine ecall */
		addr = csr_mepc();

		uart0_printf("ECALL: a0=0x%lx a1=0x%lx\n",
				args->a0, args->a1);
		args->a0 = args->a0 + args->a1;

		csr_mepc_set(addr+4);
		break;
	default:
		uart0_printf("FAULT: %ld\n", cause);
		while (1)
			/* spin forever */;
	}
}

void
mtimer_handler(void)
{
	static uint32_t r = 0xff;
	static uint32_t g = 0;
	static uint32_t b = 0;

	if (r > 0 && b == 0) {
		r--;
		g++;
	}
	if (g > 0 && r == 0) {
		g--;
		b++;
	}
	if (b > 0 && g == 0) {
		r++;
		b--;
	}

	/* PWM is low on the left
	 * GPIO is low on the left side
	 * LED is ON on the left */
	pwm1->cmp1  = g << 4;
	/* PWM is high on the middle
	 * GPIO is low in the middle
	 * LED is ON in the middle */
	pwm1->cmp2  = (b << 1) << 4;
	/* PWM is low on the left
	 * GPIO is low on the right
	 * LED is on on the right */
	pwm1->cmp3  = 0xFFFF - (r << 4);

	clint->mtimecmp += 100;
}

static uint32_t lastcycle;

void
rtccmp_handler(void)
{
	uint32_t now = csr_mcycle();

	aon->rtccmp += 1;
	(void)aon->rtccfg; /* this seems to make interrupt more stable */
	uart0_printf("tick! cycles/sec=%lu\n", now - lastcycle);
	lastcycle = now;
}

void
gpio0_handler(void)
{
	gpio->fall_ip = PIN_8; /* clear interrupt */
	uart0_printf("click!\n");
}

static void
clock_init(void)
{
	/* make sure HFXOSC is enabled */
	prci->hfxosccfg = PRCI_HFXOSCCFG_EN;
#define FAST
#ifdef FAST
#define HFCLK 200000000UL
	/* make sure we don't divide pllout further */
	prci->plloutdiv = PRCI_PLLOUTDIV_DIVBY1;

	/* configure pll:
	 * - refsel set       => pllref from HFXOSC  => pllref = 16MHz
	 * - r =  1 = 2-1     => divide refsel by 2  => refr   = 8MHz
	 * - f = 24 = 50/2-1  => multiply refr by 50 => vco    = 400MHz
	 * - q =  1 = log2(2) => divide vco by 2     => pllout = 200MHz
	 */
	prci->pllcfg = PRCI_PLLCFG_REFSEL
	             | PRCI_PLLCFG_R(1)
	             | PRCI_PLLCFG_F(24)
	             | PRCI_PLLCFG_Q(1);

	/* wait for PLL to be ready */
	while (!(prci->pllcfg & PRCI_PLLCFG_LOCK))
		/* wait */;

	/* switch to running off the PLL */
	prci->pllcfg |= PRCI_PLLCFG_SEL;
#else
#define HFCLK HFXOSC_FREQ
	/* wait for HFXOSC to be ready */
	while (!(prci->hfxosccfg & PRCI_HFXOSCCFG_RDY))
		/* wait */;

	/* bypass pll, but run off 16MHz HFXOSC */
	prci->pllcfg = PRCI_PLLCFG_SEL | PRCI_PLLCFG_REFSEL | PRCI_PLLCFG_BYPASS;
#endif
	/* turn off HFROSC to save power */
	prci->hfrosccfg = 0;
	/* the Hifive1 board uses an external 32kHz oscillator,
	 * so turn off LFROSC to save power */
	aon->lfrosccfg = 0;
}

int
main(void)
{
	clock_init();
	plic_init();
	uart0_init(HFCLK, 115200, 1);

	/* wait a second to avoid corruption on the UART
	 * (in some cases, switching to the IOF can lead
	 * to output glitches, so need to let the UART
	 * reciever time out and resynchronize to the real
	 * start of the stream */
	csr_mie_set(0x880U); /* enable mexternal and mtimer interrupts */
	clint->mtimecmp = clint->mtime + RTC_FREQ;
	while (!(csr_mip() & 0x80U))
		__wfi();
	/* disable mtimer interrupts again */
	csr_mie_clearbit(0x80U);
	/* set trap handler */
	csr_mtvec_set(&trap_handler);
	/* enable mie bit to call trap handler on interrupts and faults */
	csr_mstatus_setbit(0x8U);

	uart0_printf("%s"
			"config string (0x%08lx):\n%s"
			"0x20004   %#08lx\n"
			"misa      %#08lx\n"
			"mvendorid %#08lx\n"
			"marchid   %#08lx\n"
			"mimpid    %#08lx\n"
			"mstatus   %#08lx\n"
			"mtvec     %#08lx\n"
			"mie       %#08lx\n"
			"mip       %#08lx\n"
			"mtime     %#016llx\n",
			pentagram_msg,
			*((unsigned long *)0x100c),
			*((const char **)0x100c),
			*((unsigned long *)0x20004),
			csr_misa(),
			csr_mvendorid(),
			csr_marchid(),
			csr_mimpid(),
			csr_mstatus(),
			(unsigned long)csr_mtvec(),
			csr_mie(),
			csr_mip(),
			clint->mtime);

	/* configure pin 8 as "button" */
	gpio->pue      |= PIN_8; /* enable pull-up */
	gpio->input_en |= PIN_8; /* enable input */
	gpio->fall_ip   = PIN_8; /* clear pending falling edge interrupt */
	gpio->fall_ie  |= PIN_8; /* enable falling edge interrupt */
	plic->priority[PIN_8_INT] = 1; /* set PLIC priority */
	plic_enable(plic, PIN_8_INT); /* enable gpio0 interrupt */

	/* set up RGB PWM */
	pwm1->cfg   = 0;
	/* to balance the power consumption, make one left, one right, and one center aligned */
	pwm1->cfg   = PWM_CFG_ENALWAYS | PWM_CFG_CMP2CENTER;
	pwm1->count = 0;

	/* period is approximately 244 Hz
	 * the LEDs are intentionally left somewhat dim,
	 * as the full brightness can be painful to look at */
	pwm1->cmp0  = 0;

	gpio->iof_sel |= LED_GREEN | LED_BLUE | LED_RED;
	gpio->iof_en  |= LED_GREEN | LED_BLUE | LED_RED;
	gpio->out_xor = (gpio->out_xor & ~(LED_GREEN | LED_BLUE)) | LED_RED;
	clint->mtimecmp = clint->mtime;
	csr_mie_setbit(0x80U); /* enable mtimer interrupt */

	aon->rtccfg = AON_RTCCFG_ENALWAYS | AON_RTCCFG_SCALE(15);
	aon->rtccount = 0;
	aon->rtccmp = 0;
	plic->priority[PLIC_INT_RTCCMP] = 1;
	lastcycle = csr_mcycle();
	plic_enable(plic, PLIC_INT_RTCCMP);

	while (1) {
		char c = uart0_getc();

		switch (c) {
		case '\r':
			uart0_printf(
					"mstatus       %#08lx\n"
					"mtvec         %#08lx\n"
					"mie           %#08lx\n"
					"mip           %#08lx\n"
					"mtime         %#016llx\n"
					"gpio.value    %#08lx\n"
					"gpio.fall_ie  %#08lx\n"
					"plic.enable0  %#08lx\n"
					"plic.pending0 %#08lx\n",
					csr_mstatus(),
					(unsigned long)csr_mtvec(),
					csr_mie(),
					csr_mip(),
					clint->mtime,
					gpio->value,
					gpio->fall_ie,
					plic->enable[0],
					plic->pending[0]);
			break;
		case 'b':
			__asm__ __volatile__ ("ebreak");
			break;
		case 'c':
			uart0_printf("ecall(0x13, 0x37)=0x%02lx\n",
					ecall2(0x13, 0x37));
			break;
		default:
			uart0_putc(c);
		}
	}
}
