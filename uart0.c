// SPDX-License-Identifier: Apache-2.0

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#include "riscv/bits.h"
#include "platform.h"

#include "uart0.h"

static struct {
	volatile uint16_t first;
	volatile uint16_t last;
	char buf[2048];
} uart0_output;

void
uart0_handler(void)
{
	unsigned int first = uart0_output.first;
	unsigned int last = uart0_output.last;

	while (first != last) {
		if (uart0->txdata < 0)
			goto out;
		uart0->txdata = uart0_output.buf[first++];
		first %= ARRAY_SIZE(uart0_output.buf);
	}
	uart0->ie &= ~UART_IE_TXWM;
out:
	uart0_output.first = first;
}

char
uart0_getc(void)
{
	int32_t val;

	while ((val = uart0->rxdata) < 0)
		__wfi();

	return val;
}

static unsigned int
uart0__init(void)
{
	return uart0_output.last;
}

static unsigned int
uart0__putc(unsigned int last, char c)
{
	uart0_output.buf[last++] = c;
	return last % ARRAY_SIZE(uart0_output.buf);
}

static void
uart0__commit(unsigned int last)
{
	uart0_output.last = last;
	uart0->ie |= UART_IE_TXWM;
}

void
uart0_putc(char c)
{
	uart0__commit(uart0__putc(uart0__init(), c));
}

static unsigned int
uart0__puts(unsigned int last, const char *s)
{
	bool seenr = false;

	while (1) {
		char c = *s++;

		switch (c) {
		case '\0':
			return last;
		case '\r':
			seenr = true;
			break;
		case '\n':
			if (!seenr)
				last = uart0__putc(last, '\r');
			/* fallthrough */
		default:
			seenr = false;
		}

		last = uart0__putc(last, c);
	}
}

void
uart0_puts(const char *s)
{
	uart0__commit(uart0__puts(uart0__init(), s));
}

static const char xdigit[] = {
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
};

static unsigned int
uart0__u32h(unsigned int last, int width, char pad, uint32_t v)
{
	char buf[8];
	char *p = buf;

	for (; width > 9; width--)
		last = uart0__putc(last, pad);

	do {
		*p++ = xdigit[v & 0xfU];
		width--;
		v >>= 4;
	} while (v);

	for (; width > 0; width--)
		*p++ = pad;

	do {
		last = uart0__putc(last, *--p);
	} while (p > buf);

	return last;
}

static unsigned int
uart0__u32u(unsigned int last, int width, char pad, uint32_t v)
{
	char buf[10];
	char *p = buf;

	for (; width > 10; width--)
		last = uart0__putc(last, pad);

	do {
		*p++ = xdigit[v % 10];
		width--;
		v /= 10;
	} while (v);

	for (; width > 0; width--)
		*p++ = pad;

	do {
		last = uart0__putc(last, *--p);
	} while (p > buf);

	return last;
}

static unsigned int
uart0__u32d(unsigned int last, int width, char pad, int32_t v)
{
	if (v < 0) {
		last = uart0__putc(last, '-');
		v = -v;
	}
	return uart0__u32u(last, width, pad, v);
}

static unsigned int
uart0__u64h(unsigned int last, uint64_t v)
{
	union {
		struct {
			uint32_t low;
			uint32_t high;
		};
		uint64_t v;
	} tmp = { .v = v };

	return uart0__u32h(uart0__u32h(last, 8, '0', tmp.high), 8, '0', tmp.low);
}

void
uart0_vprintf(const char *fmt, va_list ap)
{
	unsigned int last = uart0__init();
	unsigned int size;
	int width;
	char pad;
	bool alt;

fmt:
	alt = false;
	while (1) {
		char c = *fmt++;

		switch (c) {
		case '\0':
			goto out;
		case '%':
			goto arg;
		case '\r':
			alt = true;
			break;
		case '\n':
			if (!alt)
				last = uart0__putc(last, '\r');
			/* fallthrough */
		default:
			alt = false;
		}
		last = uart0__putc(last, c);
	}

arg:
	size = 2;
	width = 0;
	pad = ' ';
	alt = false;
	while (1) {
		char c = *fmt++;

		switch (c) {
		case '\0':
			goto out;
		case '%':
			last = uart0__putc(last, '%');
			goto fmt;
		case '#':
			alt = true;
			break;
		case '0':
			if (width == 0) {
				pad = '0';
				break;
			}
			/* fallthrough */
		case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			width *= 10;
			width += c - '0';
			break;
		case '*':
			width = va_arg(ap, int);
			break;
		case 'h':
			size -= 1;
			break;
		case 'l':
			size += 1;
			break;
		case 's':
			last = uart0__puts(last, va_arg(ap, const char *));
			goto fmt;
		case 'u':
			last = uart0__u32u(last, width, pad, va_arg(ap, uint32_t));
			goto fmt;
		case 'd':
		case 'i':
			last = uart0__u32d(last, width, pad, va_arg(ap, int32_t));
			goto fmt;
		case 'x':
			if (alt)
				last = uart0__puts(last, "0x");
			if (size > 3)
				last = uart0__u64h(last, va_arg(ap, uint64_t));
			else
				last = uart0__u32h(last, width, pad, va_arg(ap, uint32_t));
			goto fmt;
		default:
			goto fmt;
		}
	}
out:
	uart0__commit(last);
}

void __attribute__((format(printf,1, 2)))
uart0_printf(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	uart0_vprintf(fmt, ap);
	va_end(ap);
}

void
uart0_init(uint32_t tlclk, uint32_t target, uint32_t priority)
{
	/* configure UART to print */
	gpio->port      |= IOF_UART0_Msk;
	gpio->output_en |= IOF_UART0_Msk;
	gpio->iof_sel   &= ~IOF_UART0_Msk;
	gpio->iof_en    |= IOF_UART0_Msk;

	uart0->div = uart_div(tlclk, target);
	uart0->txctrl = UART_TXCTRL_TXCNT(1) | UART_TXCTRL_TXEN;
	uart0->rxctrl = UART_RXCTRL_RXCNT(1) | UART_RXCTRL_RXEN;
	uart0->ie     = 0;
	plic->priority[PLIC_INT_UART0] = priority;
	plic_enable(plic, PLIC_INT_UART0);
}
