// SPDX-License-Identifier: Apache-2.0

.macro laa rd, addr
	lui	\rd, %hi(\addr)
	addi	\rd, \rd, %lo(\addr)
.endm

.section .init
.global _start
.type _start, %function
.func _start
_start:
.cfi_startproc
.cfi_undefined ra
	csrci	mstatus, 0xf
.option push
.option norelax
	laa	gp, __global_pointer$
.option pop
	laa	sp, _sp

	/* load data section */
	laa	a0, _data_lma
	laa	a1, _data
	laa	a2, _edata
	bgeu	a1, a2, 2f
1:
	lw	a3, 0(a0)
	sw	a3, 0(a1)
	addi	a0, a0, 4
	addi	a1, a1, 4
	bltu	a1, a2, 1b
2:
	/* clear bss section */
	laa	a0, __bss_start
	laa	a1, _end
	bgeu	a0, a1, 2f
1:
	sw	zero, (a0)
	addi	a0, a0, 4
	bltu	a0, a1, 1b
2:

#ifndef __riscv_float_abi_soft
	/* enable FPU */
	li	t0, MSTATUS_FS
	csrs	mstatus, t0
	csrr	t1, mstatus
	and	t1, t1, t0
	beqz	t1, 1f
	fssr	zero
1:
#endif

#ifdef ENABLE_CXX
#ifdef ENABLE_EXIT
	/* call global constructors */
	la	a0, __libc_fini_array
	call	atexit
#endif
	call	__libc_init_array
#endif

	/* argc = argv = 0 */
	li	a0, 0
	li	a1, 0
	call	main
#ifdef ENABLE_EXIT
	tail	exit
#endif
1:
	j	1b

.cfi_endproc
.size _start, . - _start
.endfunc

/* vim: set ft=asm: */
