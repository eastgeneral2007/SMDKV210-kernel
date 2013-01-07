/* linux/arch/arm/plat-s5pc1xx/include/plat/gpio-bank-mp07.h
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

#define S5PV2XX_MP07CON			(S5PV2XX_MP07_BASE + 0x00)
#define S5PV2XX_MP07DAT			(S5PV2XX_MP07_BASE + 0x04)
#define S5PV2XX_MP07PUD			(S5PV2XX_MP07_BASE + 0x08)
#define S5PV2XX_MP07DRV			(S5PV2XX_MP07_BASE + 0x0c)
#define S5PV2XX_MP07CONPDN		(S5PV2XX_MP07_BASE + 0x10)
#define S5PV2XX_MP07PUDPDN		(S5PV2XX_MP07_BASE + 0x14)

#define S5PV2XX_MP07_CONMASK(__gpio)	(0xf << ((__gpio) * 4))
#define S5PV2XX_MP07_INPUT(__gpio)	(0x0 << ((__gpio) * 4))
#define S5PV2XX_MP07_OUTPUT(__gpio)	(0x1 << ((__gpio) * 4))

#define S5PV2XX_MP07_0_EBI_DATA_8	(0x2 << 0)
#define S5PV2XX_MP07_1_EBI_DATA_9	(0x2 << 4)
#define S5PV2XX_MP07_2_EBI_DATA_10	(0x2 << 8)
#define S5PV2XX_MP07_3_EBI_DATA_11	(0x2 << 12)
#define S5PV2XX_MP07_4_EBI_DATA_12	(0x2 << 16)
#define S5PV2XX_MP07_5_EBI_DATA_13	(0x2 << 20)
#define S5PV2XX_MP07_6_EBI_DATA_14	(0x2 << 24)
#define S5PV2XX_MP07_7_EBI_DATA_15	(0x2 << 28)

