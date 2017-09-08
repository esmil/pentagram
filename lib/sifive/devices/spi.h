// SPDX-License-Identifier: Apache-2.0
#ifndef _SIFIVE_SPI_H
#define _SIFIVE_SPI_H

#include "sifive/const.h"

/* register offsets */
#define SPI_SCKDIV    _AC(0x00,UL)
#define SPI_SCKMODE   _AC(0x04,UL)
#define SPI_CSID      _AC(0x10,UL)
#define SPI_CSDEF     _AC(0x14,UL)
#define SPI_CSMODE    _AC(0x18,UL)
/*
#define SPI_DCSSCK    _AC(0x28,UL)
*/
#define SPI_DELAY0    _AC(0x28,UL)
#define SPI_DELAY1    _AC(0x2c,UL)
/*
#define SPI_DSCKCS    _AC(0x2a,UL)
#define SPI_DINTERCS  _AC(0x2c,UL)
#define SPI_DINTERXFR _AC(0x2e,UL)
*/
#define SPI_FMT       _AC(0x40,UL)
#define SPI_TXDATA    _AC(0x48,UL)
#define SPI_RXDATA    _AC(0x4c,UL)
#define SPI_TXMARK    _AC(0x50,UL)
#define SPI_RXMARK    _AC(0x54,UL)

#define SPI_FCTRL     _AC(0x60,UL)
#define SPI_FFMT      _AC(0x64,UL)

#define SPI_IE        _AC(0x70,UL)
#define SPI_IP        _AC(0x74,UL)

/* sckmode register */
#define SPI_SCKMODE_POL             _AC(0x00000001,U)
#define SPI_SCKMODE_PHA             _AC(0x00000002,U)

/* csmode register */
#define SPI_CSMODE_MODE_Pos         0
#define SPI_CSMODE_MODE_Msk         _AC(0x00000003,U)
#define SPI_CSMODE_MODE(x)          ((x) << SPI_CSMODE_MODE_Pos)
#define SPI_CSMODE_MODE_AUTO        _AC(0x00000000,U)
#define SPI_CSMODE_MODE_HOLD        _AC(0x00000002,U)
#define SPI_CSMODE_MODE_OFF         _AC(0x00000003,U)

/* delay0 register */
#define SPI_DELAY0_CSSCK_Pos        0
#define SPI_DELAY0_CSSCK_Msk        _AC(0x000000ff,U)
#define SPI_DELAY0_CSSCK(x)         ((x) << SPI_DELAY0_CSSCK_Pos)
#define SPI_DELAY0_CSSCK_DEFAULT    _AC(0x00000001,U)
#define SPI_DELAY0_SCKCS_Pos        16
#define SPI_DELAY0_SCKCS_Msk        _AC(0x00ff0000,U)
#define SPI_DELAY0_SCKCS(x)         ((x) << SPI_DELAY0_SCKCS_Pos)
#define SPI_DELAY0_SCKCS_DEFAULT    _AC(0x00010000,U)

/* delay1 register */
#define SPI_DELAY1_INTERCS_Pos      0
#define SPI_DELAY1_INTERCS_Msk      _AC(0x000000ff,U)
#define SPI_DELAY1_INTERCS(x)       ((x) << SPI_DELAY1_INTERCS_Pos)
#define SPI_DELAY1_INTERCS_DEFAULT  _AC(0x00000001,U)
#define SPI_DELAY1_INTERXFR_Pos     16
#define SPI_DELAY1_INTERXFR_Msk     _AC(0x00ff0000,U)
#define SPI_DELAY1_INTERXFR(x)      ((x) << SPI_DELAY1_INTERXFR_Pos)
#define SPI_DELAY1_INTERXFR_DEFAULT _AC(0x00010000,U)

/* fmt register */
#define SPI_FMT_PROTO_Pos           0
#define SPI_FMT_PROTO_Msk           _AC(0x00000003,U)
#define SPI_FMT_PROTO(x)            ((x) << SPI_FMT_PROTO_Pos)
#define SPI_FMT_PROTO_SINGLE        _AC(0x00000000,U)
#define SPI_FMT_PROTO_DUAL          _AC(0x00000001,U)
#define SPI_FMT_PROTO_QUAD          _AC(0x00000002,U)
#define SPI_FMT_ENDIAN              _AC(0x00000004,U)
#define SPI_FMT_ENDIAN_MSB          _AC(0x00000000,U)
#define SPI_FMT_ENDIAN_LSB          _AC(0x00000004,U)
#define SPI_FMT_DIR                 _AC(0x00000008,U)
#define SPI_FMT_DIR_RX              _AC(0x00000000,U)
#define SPI_FMT_DIR_TX              _AC(0x00000008,U)
#define SPI_FMT_LEN_Pos             16
#define SPI_FMT_LEN_Msk             _AC(0x000f0000,U)
#define SPI_FMT_LEN(x)              ((x) << SPI_FMT_LEN_Pos)

/* txmark register */
#define SPI_TXMARK_TXMARK_Pos       0
#define SPI_TXMARK_TXMARK_Msk       _AC(0x00000007,U)
#define SPI_TXMARK_TXMARK(x)        ((x) << SPI_TXMARK_TXMARK_Pos)

/* rxmark register */
#define SPI_RXMARK_RXMARK_Pos       0
#define SPI_RXMARK_RXMARK_Msk       _AC(0x00000007,U)
#define SPI_RXMARK_RXMARK(x)        ((x) << SPI_RXMARK_RXMARK_Pos)

/* fctrl register */
#define SPI_FCTRL_EN                _AC(0x00000001,U)

/* ffmt register */
#define SPI_FFMT_CMD_EN             _AC(0x00000001,U)
#define SPI_FFMT_ADDR_LEN_Pos       1
#define SPI_FFMT_ADDR_LEN_Msk       _AC(0x0000000e,U)
#define SPI_FFMT_ADDR_LEN(x)        ((x) << SPI_FFMT_ADDR_LEN_Pos)
#define SPI_FFMT_ADDR_LEN_DEFAULT   _AC(0x00000006,U)
#define SPI_FFMT_PAD_CNT_Pos        4
#define SPI_FFMT_PAD_CNT_Msk        _AC(0x000000f0,U)
#define SPI_FFMT_PAD_CNT(x)         ((x) << SPI_FFMT_PAD_CNT_Pos)
#define SPI_FFMT_PAD_CNT_DEFAULT    _AC(0x00000000,U)
#define SPI_FFMT_CMD_PROTO_Pos      8
#define SPI_FFMT_CMD_PROTO_Msk      _AC(0x00000300,U)
#define SPI_FFMT_CMD_PROTO(x)       ((x) << SPI_FFMT_CMD_PROTO_Pos)
#define SPI_FFMT_CMD_PROTO_DEFAULT  _AC(0x00000000,U)
#define SPI_FFMT_ADDR_PROTO_Pos     10
#define SPI_FFMT_ADDR_PROTO_Msk     _AC(0x00000c00,U)
#define SPI_FFMT_ADDR_PROTO(x)      ((x) << SPI_FFMT_ADDR_PROTO_Pos)
#define SPI_FFMT_ADDR_PROTO_DEFAULT _AC(0x00000000,U)
#define SPI_FFMT_DATA_PROTO_Pos     12
#define SPI_FFMT_DATA_PROTO_Msk     _AC(0x00003000,U)
#define SPI_FFMT_DATA_PROTO(x)      ((x) << SPI_FFMT_DATA_PROTO_Pos)
#define SPI_FFMT_DATA_PROTO_DEFAULT _AC(0x00000000,U)
#define SPI_FFMT_CMD_CODE_Pos       16
#define SPI_FFMT_CMD_CODE_Msk       _AC(0x00ff0000,U)
#define SPI_FFMT_CMD_CODE(x)        ((x) << SPI_FFMT_CMD_CODE_Pos)
#define SPI_FFMT_CMD_CODE_DEFAULT   _AC(0x00030000,U)
#define SPI_FFMT_PAD_CODE_Pos       24
#define SPI_FFMT_PAD_CODE_Msk       _AC(0xff000000,U)
#define SPI_FFMT_PAD_CODE(x)        ((x) << SPI_FFMT_PAD_CODE_Pos)
#define SPI_FFMT_PAD_CODE_DEFAULT   _AC(0x00000000,U)

/* ie register */
#define SPI_IE_TXWM                 _AC(0x00000001,U)
#define SPI_IE_RXWM                 _AC(0x00000002,U)

/* ip register */
#define SPI_IP_TXWM                 _AC(0x00000001,U)
#define SPI_IP_RXWM                 _AC(0x00000002,U)

#ifndef __ASSEMBLER__
#include <stdint.h>
struct spi {
	volatile uint32_t sckdiv;
	volatile uint32_t sckmode;
	uint32_t reserved1[2];
	volatile uint32_t csid;
	volatile uint32_t csdef;
	volatile uint32_t csmode;
	uint32_t reserved2[3];
	volatile uint32_t delay0;
	volatile uint32_t delay1;
	volatile uint32_t fmt;
	uint32_t reserved3;
	volatile int32_t txdata;
	volatile int32_t rxdata;
	volatile uint32_t txmark;
	volatile uint32_t rxmark;
	uint32_t reserved4[2];
	volatile uint32_t fctrl;
	volatile uint32_t ffmt;
	uint32_t reserved5[2];
	volatile uint32_t ie;
	volatile uint32_t ip;
};
#endif
#endif
