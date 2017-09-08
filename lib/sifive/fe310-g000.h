// SPDX-License-Identifier: Apache-2.0
#ifndef _SIFIVE_FE810_G000_H
#define _SIFIVE_FE810_G000_H

#include "sifive/const.h"
#include "sifive/devices/aon.h"
#include "sifive/devices/clint.h"
#include "sifive/devices/gpio.h"
#include "sifive/devices/otp.h"
#include "sifive/devices/plic.h"
#include "sifive/devices/prci.h"
#include "sifive/devices/pwm.h"
#include "sifive/devices/spi.h"
#include "sifive/devices/uart.h"

/* memory map */
#define MASKROM_MEM_ADDR        _AC(0x00001000,UL)
#define TRAPVEC_TABLE_CTRL_ADDR _AC(0x00001010,UL)
#define OTP_MEM_ADDR            _AC(0x00020000,UL)
#define CLINT_CTRL_ADDR         _AC(0x02000000,UL)
#define PLIC_CTRL_ADDR          _AC(0x0c000000,UL)
#define AON_CTRL_ADDR           _AC(0x10000000,UL)
#define PRCI_CTRL_ADDR          _AC(0x10008000,UL)
#define OTP_CTRL_ADDR           _AC(0x10010000,UL)
#define GPIO0_CTRL_ADDR         _AC(0x10012000,UL)
#define UART0_CTRL_ADDR         _AC(0x10013000,UL)
#define SPI0_CTRL_ADDR          _AC(0x10014000,UL)
#define PWM0_CTRL_ADDR          _AC(0x10015000,UL)
#define UART1_CTRL_ADDR         _AC(0x10023000,UL)
#define SPI1_CTRL_ADDR          _AC(0x10024000,UL)
#define PWM1_CTRL_ADDR          _AC(0x10025000,UL)
#define SPI2_CTRL_ADDR          _AC(0x10034000,UL)
#define PWM2_CTRL_ADDR          _AC(0x10035000,UL)
#define SPI0_MEM_ADDR           _AC(0x20000000,UL)
#define MEM_CTRL_ADDR           _AC(0x80000000,UL)

/* iof masks */
#define IOF_PWM0_Pos            0
#define IOF_PWM0_Msk            _AC(0x0000000f,U)
#define IOF_PWM0_0              _AC(0x00000001,U)
#define IOF_PWM0_1              _AC(0x00000002,U)
#define IOF_PWM0_2              _AC(0x00000004,U)
#define IOF_PWM0_3              _AC(0x00000008,U)

#define IOF_SPI1_Pos            2
#define IOF_SPI1_Msk            _AC(0x000007fc,U)
#define SPI1_NUM_SS             4
#define IOF_SPI1_SS0            _AC(0x00000004,U)
#define IOF_SPI1_SD0            _AC(0x00000008,U)
#define IOF_SPI1_MOSI           _AC(0x00000008,U)
#define IOF_SPI1_SD1            _AC(0x00000010,U)
#define IOF_SPI1_MISO           _AC(0x00000010,U)
#define IOF_SPI1_SCK            _AC(0x00000020,U)
#define IOF_SPI1_SD2            _AC(0x00000040,U)
#define IOF_SPI1_SD3            _AC(0x00000080,U)
#define IOF_SPI1_SS1            _AC(0x00000100,U)
#define IOF_SPI1_SS2            _AC(0x00000200,U)
#define IOF_SPI1_SS3            _AC(0x00000400,U)

#define IOF_PWM2_Pos            10
#define IOF_PWM2_Msk            _AC(0x00003c00,U)
#define IOF_PWM2_0              _AC(0x00000400,U)
#define IOF_PWM2_1              _AC(0x00000800,U)
#define IOF_PWM2_2              _AC(0x00001000,U)
#define IOF_PWM2_3              _AC(0x00002000,U)

#define IOF_UART0_Pos           16
#define IOF_UART0_Msk           _AC(0x00030000,U)
#define IOF_UART0_RX            _AC(0x00010000,U)
#define IOF_UART0_TX            _AC(0x00020000,U)

#define IOF_PWM1_Pos            20
#define IOF_PWM1_Msk            _AC(0x00780000,U)
#define IOF_PWM1_1              _AC(0x00080000,U)
#define IOF_PWM1_0              _AC(0x00100000,U)
#define IOF_PWM1_2              _AC(0x00200000,U)
#define IOF_PWM1_3              _AC(0x00400000,U)

#define IOF_UART1_Pos           24
#define IOF_UART1_Msk           _AC(0x03000000,U)
#define IOF_UART1_RX            _AC(0x01000000,U)
#define IOF_UART1_TX            _AC(0x02000000,U)

#define IOF_SPI2_Pos            26
#define IOF_SPI2_Msk            _AC(0xfc000000,U)
#define SPI2_NUM_SS             1
#define IOF_SPI2_SS0            _AC(0x04000000,U)
#define IOF_SPI2_SD0            _AC(0x08000000,U)
#define IOF_SPI2_MOSI           _AC(0x08000000,U)
#define IOF_SPI2_SD1            _AC(0x10000000,U)
#define IOF_SPI2_MISO           _AC(0x10000000,U)
#define IOF_SPI2_SCK            _AC(0x20000000,U)
#define IOF_SPI2_SD2            _AC(0x40000000,U)
#define IOF_SPI2_SD3            _AC(0x80000000,U)

/* plic interrupt numbers */
#define PLIC_INT_RESERVED       0
#define PLIC_INT_WDOGCMP        1
#define PLIC_INT_RTCCMP         2
#define PLIC_INT_UART0          3
#define PLIC_INT_UART1          4
#define PLIC_INT_SPI0           5
#define PLIC_INT_SPI1           6
#define PLIC_INT_SPI2           7
#define PLIC_INT_GPIO_BASE      8
#define PLIC_INT_GPIO(x)        (PLIC_INT_GPIO_BASE + (x))
#define PLIC_INT_PWM0_BASE      40
#define PLIC_INT_PWM0(x)        (PLIC_INT_PWM0_BASE + (x))
#define PLIC_INT_PWM1_BASE      44
#define PLIC_INT_PWM1(x)        (PLIC_INT_PWM1_BASE + (x))
#define PLIC_INT_PWM2_BASE      48
#define PLIC_INT_PWM2(x)        (PLIC_INT_PWM2_BASE + (x))

#define PLIC_INT_MAX            51
#define PLIC_PRIORITY_MAX       7

#ifndef __ASSEMBLER__

static struct clint *const clint = (struct clint *)CLINT_CTRL_ADDR;
static struct plic  *const plic  = (struct plic *)PLIC_CTRL_ADDR;
static struct aon   *const aon   = (struct aon *)AON_CTRL_ADDR;
static struct prci  *const prci  = (struct prci *)PRCI_CTRL_ADDR;
static struct otp   *const otp   = (struct otp *)OTP_CTRL_ADDR;
static struct gpio  *const gpio  = (struct gpio *)GPIO0_CTRL_ADDR;
static struct uart  *const uart0 = (struct uart *)UART0_CTRL_ADDR;
static struct uart  *const uart1 = (struct uart *)UART1_CTRL_ADDR;
static struct spi   *const spi0  = (struct spi *)SPI0_CTRL_ADDR;
static struct spi   *const spi1  = (struct spi *)SPI1_CTRL_ADDR;
static struct spi   *const spi2  = (struct spi *)SPI2_CTRL_ADDR;
static struct pwm   *const pwm0  = (struct pwm *)PWM0_CTRL_ADDR;
static struct pwm   *const pwm1  = (struct pwm *)PWM1_CTRL_ADDR;
static struct pwm   *const pwm2  = (struct pwm *)PWM2_CTRL_ADDR;

#endif
#endif
