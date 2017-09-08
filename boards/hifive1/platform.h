// SPDX-License-Identifier: Apache-2.0
#ifndef _PLATFORM_H
#define _PLATFORM_H

#include "sifive/fe310-g000.h"

/****************************************************************************
 * GPIO Connections
 *****************************************************************************/

/* These are the GPIO bit offsets for the RGB LED on HiFive1 Board.
 * These are also mapped to RGB LEDs on the Freedom E300 Arty FPGA Dev Kit.
 */
#define LED_RED_Pos   22
#define LED_RED       _BITU(LED_RED_Pos)
#define LED_GREEN_Pos 19
#define LED_GREEN     _BITU(LED_GREEN_Pos)
#define LED_BLUE_Pos  21
#define LED_BLUE      _BITU(LED_BLUE_Pos)

/* These are the GPIO bit offsets for the differen digital pins
 * on the headers for both the HiFive1 Board and the Freedom E300 Arty FPGA Dev Kit.
 */
#define PIN_0_Pos  16
#define PIN_0      _BITU(PIN_0_Pos)
#define PIN_0_INT  PLIC_INT_GPIO(PIN_0_Pos)
#define PIN_1_Pos  17
#define PIN_1      _BITU(PIN_1_Pos)
#define PIN_1_INT  PLIC_INT_GPIO(PIN_1_Pos)
#define PIN_2_Pos  18
#define PIN_2      _BITU(PIN_2_Pos)
#define PIN_2_INT  PLIC_INT_GPIO(PIN_2_Pos)
#define PIN_3_Pos  19
#define PIN_3      _BITU(PIN_3_Pos)
#define PIN_3_INT  PLIC_INT_GPIO(PIN_3_Pos)
#define PIN_4_Pos  20
#define PIN_4      _BITU(PIN_4_Pos)
#define PIN_4_INT  PLIC_INT_GPIO(PIN_4_Pos)
#define PIN_5_Pos  21
#define PIN_5      _BITU(PIN_5_Pos)
#define PIN_5_INT  PLIC_INT_GPIO(PIN_5_Pos)
#define PIN_6_Pos  22
#define PIN_6      _BITU(PIN_6_Pos)
#define PIN_6_INT  PLIC_INT_GPIO(PIN_6_Pos)
#define PIN_7_Pos  23
#define PIN_7      _BITU(PIN_7_Pos)
#define PIN_7_INT  PLIC_INT_GPIO(PIN_7_Pos)
#define PIN_8_Pos  0
#define PIN_8      _BITU(PIN_8_Pos)
#define PIN_8_INT  PLIC_INT_GPIO(PIN_8_Pos)
#define PIN_9_Pos  1
#define PIN_9      _BITU(PIN_9_Pos)
#define PIN_9_INT  PLIC_INT_GPIO(PIN_9_Pos)
#define PIN_10_Pos 2
#define PIN_10     _BITU(PIN_10_Pos)
#define PIN_10_INT PLIC_INT_GPIO(PIN_11_Pos)
#define PIN_11_Pos 3
#define PIN_11     _BITU(PIN_11_Pos)
#define PIN_11_INT PLIC_INT_GPIO(PIN_12_Pos)
#define PIN_12_Pos 4
#define PIN_12     _BITU(PIN_12_Pos)
#define PIN_12_INT PLIC_INT_GPIO(PIN_13_Pos)
#define PIN_13_Pos 5
#define PIN_13     _BITU(PIN_13_Pos)
#define PIN_13_INT PLIC_INT_GPIO(PIN_14_Pos)
/* this pin is not connected on either board
#define PIN_14_Pos 8
#define PIN_14     _BITU(PIN_14_Pos)
#define PIN_14_INT PLIC_INT_GPIO(PIN_14_Pos)
*/
#define PIN_15_Pos 9
#define PIN_15     _BITU(PIN_15_Pos)
#define PIN_15_INT PLIC_INT_GPIO(PIN_15_Pos)
#define PIN_16_Pos 10
#define PIN_16     _BITU(PIN_16_Pos)
#define PIN_16_INT PLIC_INT_GPIO(PIN_16_Pos)
#define PIN_17_Pos 11
#define PIN_17     _BITU(PIN_17_Pos)
#define PIN_17_INT PLIC_INT_GPIO(PIN_17_Pos)
#define PIN_18_Pos 12
#define PIN_18     _BITU(PIN_18_Pos)
#define PIN_18_INT PLIC_INT_GPIO(PIN_18_Pos)
#define PIN_19_Pos 13
#define PIN_19     _BITU(PIN_19_Pos)
#define PIN_19_INT PLIC_INT_GPIO(PIN_19_Pos)

/* these are *PIN* numbers, not GPIO Offset Numbers. */
#define PIN_SPI1_SCK   13
#define PIN_SPI1_MISO  12
#define PIN_SPI1_MOSI  11
#define PIN_SPI1_SS0   10
#define PIN_SPI1_SS1   14
#define PIN_SPI1_SS2   15
#define PIN_SPI1_SS3   16

#define SS_PIN_TO_CS_ID(x) \
  ((x == PIN_SPI1_SS0 ? 0 : \
   (x == PIN_SPI1_SS1 ? 1 : \
   (x == PIN_SPI1_SS2 ? 2 : \
   (x == PIN_SPI1_SS3 ? 3 : -1)))))

/* these buttons are present only on the Freedom E300 Arty Dev Kit */
#ifdef HAS_BOARD_BUTTONS
#define BUTTON_0_Pos 15
#define BUTTON_0     _BITU(BUTTON_0_Pos)
#define BUTTON_0_INT PLIC_INT_GPIO(BUTTON_0_Pos)
#define BUTTON_1_Pos 30
#define BUTTON_1     _BITU(BUTTON_1_Pos)
#define BUTTON_1_INT PLIC_INT_GPIO(BUTTON_1_Pos)
#define BUTTON_2_Pos 31
#define BUTTON_2     _BITU(BUTTON_2_Pos)
#define BUTTON_2_INT PLIC_INT_GPIO(BUTTON_2_Pos)
#endif

#define HAS_HFXOSC 1
#define HAS_LFROSC_BYPASS 1

#define HFXOSC_FREQ _AC(16000000,U)
#define RTC_FREQ _AC(32768,U)

#ifndef __ASSEMBLER__
void default_handler(void);

void trap_handler(void);
void msoftware_handler(void);
void mtimer_handler(void);
void mexternal_handler(void);

struct fault_handler_args {
	unsigned long a0;
	unsigned long a1;
	unsigned long a2;
	unsigned long a3;
	unsigned long a4;
	unsigned long a5;
	unsigned long a6;
	unsigned long a7;
};

void fault_handler(long cause, struct fault_handler_args *args);

void wdogcmp_handler(void);
void rtccmp_handler(void);
void uart0_handler(void);
void uart1_handler(void);
void spi0_handler(void);
void spi1_handler(void);
void spi2_handler(void);
void gpio0_handler(void);
void gpio1_handler(void);
void gpic2_handler(void);
void gpio3_handler(void);
void gpio4_handler(void);
void gpio5_handler(void);
void gpio6_handler(void);
void gpio7_handler(void);
void gpio8_handler(void);
void gpio9_handler(void);
void gpio10_handler(void);
void gpio11_handler(void);
void gpic12_handler(void);
void gpio13_handler(void);
void gpio14_handler(void);
void gpio15_handler(void);
void gpio16_handler(void);
void gpio17_handler(void);
void gpio18_handler(void);
void gpio19_handler(void);
void gpio20_handler(void);
void gpio21_handler(void);
void gpic22_handler(void);
void gpio23_handler(void);
void gpio24_handler(void);
void gpio25_handler(void);
void gpio26_handler(void);
void gpio27_handler(void);
void gpio28_handler(void);
void gpio29_handler(void);
void gpio30_handler(void);
void gpio31_handler(void);
void pwm0cmp0_handler(void);
void pwm0cmp1_handler(void);
void pwm0cmp2_handler(void);
void pwm0cmp3_handler(void);
void pwm1cmp0_handler(void);
void pwm1cmp1_handler(void);
void pwm1cmp2_handler(void);
void pwm1cmp3_handler(void);
void pwm2cmp0_handler(void);
void pwm2cmp1_handler(void);
void pwm2cmp2_handler(void);
void pwm2cmp3_handler(void);
#endif
#endif
