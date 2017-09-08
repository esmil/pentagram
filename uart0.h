// SPDX-License-Identifier: Apache-2.0
#ifndef UART0_H
#define UART0_H

#include <stdarg.h>

void uart0_handler(void);

char uart0_getc(void);
void uart0_putc(char c);
void uart0_puts(const char *s);
void uart0_vprintf(const char *fmt, va_list ap);
void __attribute__((format(printf,1, 2))) uart0_printf(const char *fmt, ...);

void uart0_init(uint32_t tlclk, uint32_t target, uint32_t priority);

#endif
