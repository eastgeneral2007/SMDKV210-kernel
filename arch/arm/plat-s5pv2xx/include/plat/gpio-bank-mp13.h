/* linux/arch/arm/plat-s5pc1xx/include/plat/gpio-bank-mp13.h
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

#define S5PV2XX_MP13CON			(S5PV2XX_MP13_BASE + 0x00)
#define S5PV2XX_MP13DAT			(S5PV2XX_MP13_BASE + 0x04)
#define S5PV2XX_MP13PUD			(S5PV2XX_MP13_BASE + 0x08)
#define S5PV2XX_MP13DRV			(S5PV2XX_MP13_BASE + 0x0c)
#define S5PV2XX_MP13CONPDN		(S5PV2XX_MP13_BASE + 0x10)
#define S5PV2XX_MP13PUDPDN		(S5PV2XX_MP13_BASE + 0x14)

#define S5PV2XX_MP13_CONMASK(__gpio)	(0xf << ((__gpio) * 4))
#define S5PV2XX_MP13_INPUT(__gpio)	(0x0 << ((__gpio) * 4))
#define S5PV2XX_MP13_OUTPUT(__gpio)	(0x1 << ((__gpio) * 4))

#define S5PV2XX_MP13_0_LD0_DATA_8	(0x2 << 0)
#define S5PV2XX_MP13_1_LD0_DATA_9	(0x2 << 4)
#define S5PV2XX_MP13_2_LD0_DATA_10	(0x2 << 8)
#define S5PV2XX_MP13_3_LD0_DATA_11	(0x2 << 12)
#define S5PV2XX_MP13_4_LD0_DATA_12	(0x2 << 16)
#define S5PV2XX_MP13_5_LD0_DATA_13	(0x2 << 20)
#define S5PV2XX_MP13_6_LD0_DATA_14	(0x2 << 24)
#define S5PV2XX_MP13_7_LD0_DATA_15	(0x2 << 28)

