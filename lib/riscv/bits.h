// SPDX-License-Identifier: Apache-2.0
#ifndef _RISCV_BITS_H
#define _RISCV_BITS_H

#define ROUNDUP(a, b) ((((a)-1)/(b)+1)*(b))
#define ROUNDDOWN(a, b) ((a)/(b)*(b))

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define CLAMP(a, lo, hi) MIN(MAX(a, lo), hi)

#define EXTRACT_FIELD(val, which) (((val) & (which)) / ((which) & ~((which)-1)))
#define INSERT_FIELD(val, which, fieldval) (((val) & ~(which)) | ((fieldval) * ((which) & ~((which)-1))))

#define STR(x) XSTR(x)
#define XSTR(x) #x

#ifdef __ASSEMBLER__

#if __riscv_xlen == 64
# define SLL32    sllw
# define STORE    sd
# define LOAD     ld
# define LWU      lwu
# define REGBYTES     8
# define LOG_REGBYTES 3
#else
# define SLL32    sll
# define STORE    sw
# define LOAD     lw
# define LWU      lw
# define REGBYTES     4
# define LOG_REGBYTES 2
#endif

#else /* C */

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))
#define ARRAY_END(x) (&(x)[ARRAY_SIZE(x)])

#define likely(x) __builtin_expect((x), 1)
#define unlikely(x) __builtin_expect((x), 0)

static inline void __wfi(void)
{
	__asm__ __volatile__ ("wfi");
}

#endif
#endif
