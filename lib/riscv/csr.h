// SPDX-License-Identifier: Apache-2.0
#ifndef _RISCV_CSR_H
#define _RISCV_CSR_H

#ifdef __GNUC__
#define _decl_csrr(x, typ) \
static inline typ csr_##x(void)\
{\
	typ ret;\
	__asm__ __volatile__ ( "csrr %0, " #x : "=r"(ret) );\
	return ret;\
}
#define _decl_csrw(x, typ) \
static inline void csr_##x##_set(typ val)\
{\
	if (__builtin_constant_p(val) && (unsigned long)(val) < 32)\
		__asm__ __volatile__ ( "csrwi " #x ", %0" :: "i"(val) );\
	else\
		__asm__ __volatile__ ( "csrw " #x ", %0" :: "r"(val) );\
}\
static inline void csr_##x##_setbit(typ val)\
{\
	if (__builtin_constant_p(val) && (unsigned long)(val) < 32)\
		__asm__ __volatile__ ( "csrsi " #x ", %0" :: "i"(val) );\
	else\
		__asm__ __volatile__ ( "csrs " #x ", %0" :: "r"(val) );\
}\
static inline void csr_##x##_clearbit(typ val)\
{\
	if (__builtin_constant_p(val) && (unsigned long)(val) < 32)\
		__asm__ __volatile__ ( "csrci " #x ", %0" :: "i"(val) );\
	else\
		__asm__ __volatile__ ( "csrc " #x ", %0" :: "r"(val) );\
}
#define _decl_csrrw(x, typ) \
_decl_csrr(x, typ)\
_decl_csrw(x, typ)\
static inline typ csr_##x##_swap(typ val)\
{\
	typ ret;\
	if (__builtin_constant_p(val) && (unsigned long)(val) < 32)\
		__asm__ __volatile__ ( "csrrwi %0, " #x ", %1" : "=r"(ret) : "i"(val) );\
	else\
		__asm__ __volatile__ ( "csrrw %0, " #x ", %1" : "=r"(ret) : "r"(val) );\
	return ret;\
}
#else
#error csr.h only works with GCC
#endif

typedef void (*trap_handler_t)(void);

_decl_csrrw(ustatus, unsigned long)
_decl_csrrw(uie, unsigned long)
_decl_csrrw(utvec, trap_handler_t)

_decl_csrrw(uscratch, unsigned long)
_decl_csrrw(uepc, unsigned long)
_decl_csrrw(ucause, unsigned long)
_decl_csrrw(utval, unsigned long)
_decl_csrrw(uip, unsigned long)

_decl_csrr(mcycle, unsigned long)
_decl_csrr(mtime, unsigned long)
_decl_csrr(minstret, unsigned long)
#if __riscv_xlen == 32
_decl_csrr(mcycleh, unsigned long)
_decl_csrr(mtimeh, unsigned long)
_decl_csrr(minstreth, unsigned long)
#endif

_decl_csrr(mvendorid, unsigned long)
_decl_csrr(marchid, unsigned long)
_decl_csrr(mimpid, unsigned long)
_decl_csrr(mhartid, unsigned long)

_decl_csrrw(mstatus, unsigned long)
_decl_csrrw(misa, unsigned long)
_decl_csrrw(medeleg, unsigned long)
_decl_csrrw(mideleg, unsigned long)
_decl_csrrw(mie, unsigned long)
_decl_csrrw(mtvec, trap_handler_t)
_decl_csrrw(mcounteren, unsigned int)

_decl_csrrw(mscratch, unsigned long)
_decl_csrrw(mepc, unsigned long)
_decl_csrrw(mcause, unsigned long)
_decl_csrrw(mtval, unsigned long)
_decl_csrrw(mip, unsigned long)

#undef _decl_csrr
#undef _decl_csrw
#undef _decl_csrrw
#endif
