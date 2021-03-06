/* linux/arch/arm/plat-s5pc1xx/include/plat/gpio-bank-mp18.h
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * S5PV2XX GPIO BANK register
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#define S5PV2XX_MP18CON			(S5PV2XX_MP18_BASE + 0x00)
#define S5PV2XX_MP18DAT			(S5PV2XX_MP18_BASE + 0x04)
#define S5PV2XX_MP18PUD			(S5PV2XX_MP18_BASE + 0x08)
#define S5PV2XX_MP18DRV			(S5PV2XX_MP18_BASE + 0x0c)
#define S5PV2XX_MP18CONPDN		(S5PV2XX_MP18_BASE + 0x10)
#define S5PV2XX_MP18PUDPDN		(S5PV2XX_MP18_BASE + 0x14)

#define S5PV2XX_MP18_CONMASK(__gpio)	(0xf << ((__gpio) * 4))
#define S5PV2XX_MP18_INPUT(__gpio)	(0x0 << ((__gpio) * 4))
#define S5PV2XX_MP18_OUTPUT(__gpio)	(0x1 << ((__gpio) * 4))

#define S5PV2XX_MP18_0_LD0_CSn_0	(0x2 << 0)
#define S5PV2XX_MP18_1_LD0_CSn_1	(0x2 << 4)
#define S5PV2XX_MP18_2_LD0_RASn		(0x2 << 8)
#define S5PV2XX_MP18_3_LD0_CASn		(0x2 << 12)
#define S5PV2XX_MP18_4_LD0_WEn		(0x2 << 16)
#define S5PV2XX_MP18_5_LD0_IOGATE_IN	(0x2 << 20)
#define S5PV2XX_MP18_6_LD0_IOGATE_OUT	(0x2 << 24)

