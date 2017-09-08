// SPDX-License-Identifier: Apache-2.0

#include "riscv/bits.h"
#include "platform.h"

.section .text._trap_handler
.align 2
.global trap_handler
.weak trap_handler
.type trap_handler, %function
.func trap_handler
trap_handler:
	addi	sp, sp, -ROUNDUP(19*REGBYTES, 16)
	STORE	a0,  0*REGBYTES(sp)
	STORE	a1,  1*REGBYTES(sp)
	STORE	a2,  2*REGBYTES(sp)
	STORE	a3,  3*REGBYTES(sp)
	STORE	a4,  4*REGBYTES(sp)
	STORE	a5,  5*REGBYTES(sp)
	STORE	a6,  6*REGBYTES(sp)
	STORE	a7,  7*REGBYTES(sp)
	STORE	ra,  8*REGBYTES(sp)
	STORE	t0,  9*REGBYTES(sp)
	STORE	t1, 10*REGBYTES(sp)
	STORE	t2, 11*REGBYTES(sp)
	STORE	t3, 12*REGBYTES(sp)
	STORE	t4, 13*REGBYTES(sp)
	STORE	t5, 14*REGBYTES(sp)
	STORE	t6, 15*REGBYTES(sp)

	csrr	a0, mcause
	bgez	a0, 4f /* fault */
	andi	a1, a0, 0x8
	beqz	a1, 5f /* software or timer interrupt */

	/* external interrupts */
	STORE	s0, 16*REGBYTES(sp)
	STORE	s1, 17*REGBYTES(sp)
	STORE	s2, 18*REGBYTES(sp)
	lui	s0, %hi(handlers + REGBYTES)
	lui	s1, %hi(PLIC_CTRL_ADDR + PLIC_CLAIM_COMPLETE)
	j	2f
1:
	slli	a0, s2, LOG_REGBYTES
	add	a0, a0, s0
	LOAD	a0, %lo(handlers + REGBYTES)(a0)
	jalr	a0
	sw	s2, %lo(PLIC_CTRL_ADDR + PLIC_CLAIM_COMPLETE)(s1)
2:
	lw	s2, %lo(PLIC_CTRL_ADDR + PLIC_CLAIM_COMPLETE)(s1)
	bnez	s2, 1b
	LOAD s2, 18*REGBYTES(sp)
	LOAD s1, 17*REGBYTES(sp)
	LOAD s0, 16*REGBYTES(sp)
3:
	LOAD t6, 15*REGBYTES(sp)
	LOAD t5, 14*REGBYTES(sp)
	LOAD t4, 13*REGBYTES(sp)
	LOAD t3, 12*REGBYTES(sp)
	LOAD t2, 11*REGBYTES(sp)
	LOAD t1, 10*REGBYTES(sp)
	LOAD t0, 9*REGBYTES(sp)
	LOAD ra, 8*REGBYTES(sp)
	LOAD a7, 7*REGBYTES(sp)
	LOAD a6, 6*REGBYTES(sp)
	LOAD a5, 5*REGBYTES(sp)
	LOAD a4, 4*REGBYTES(sp)
	LOAD a3, 3*REGBYTES(sp)
	LOAD a2, 2*REGBYTES(sp)
	LOAD a1, 1*REGBYTES(sp)
	LOAD a0, 0*REGBYTES(sp)
	addi sp, sp, ROUNDUP(19*REGBYTES, 16)
	mret

4: /* fault */
	mv	a1, sp
	la	ra, 3b
	tail	fault_handler

5: /* software or timer interrupt */
	andi	a0, a0, 0x4
	lui	a1, %hi(handlers)
	add	a0, a0, a1
	LOAD	a0, %lo(handlers)(a0)
	la	ra, 3b
	jr	a0
.size trap_handler, . - trap_handler
.endfunc

.section .text._default_handler
.weak default_handler
.type default_handler, %function
.func default_handler
default_handler:
1:
	j 1b
.size default_handler, . - default_handler
.endfunc

.weak fault_handler
.set fault_handler, default_handler

.macro interrupt name
	.weak \name\()_handler
	.set \name\()_handler, default_handler
	.long \name\()_handler
.endm

.section .rodata._handlers
.align LOG_REGBYTES
.global handlers
.weak handlers
.type handlers, %object
handlers:
	interrupt msoftware
	interrupt mtimer
	interrupt wdogcmp
	interrupt rtccmp
	interrupt uart0
	interrupt uart1
	interrupt spi0
	interrupt spi1
	interrupt spi2
	interrupt gpio0
	interrupt gpio1
	interrupt gpic2
	interrupt gpio3
	interrupt gpio4
	interrupt gpio5
	interrupt gpio6
	interrupt gpio7
	interrupt gpio8
	interrupt gpio9
	interrupt gpio10
	interrupt gpio11
	interrupt gpic12
	interrupt gpio13
	interrupt gpio14
	interrupt gpio15
	interrupt gpio16
	interrupt gpio17
	interrupt gpio18
	interrupt gpio19
	interrupt gpio20
	interrupt gpio21
	interrupt gpic22
	interrupt gpio23
	interrupt gpio24
	interrupt gpio25
	interrupt gpio26
	interrupt gpio27
	interrupt gpio28
	interrupt gpio29
	interrupt gpio30
	interrupt gpio31
	interrupt pwm0cmp0
	interrupt pwm0cmp1
	interrupt pwm0cmp2
	interrupt pwm0cmp3
	interrupt pwm1cmp0
	interrupt pwm1cmp1
	interrupt pwm1cmp2
	interrupt pwm1cmp3
	interrupt pwm2cmp0
	interrupt pwm2cmp1
	interrupt pwm2cmp2
	interrupt pwm2cmp3
.size handlers, . - handlers
