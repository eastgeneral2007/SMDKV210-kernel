/* linux/arch/arm/plat-s5pc1xx/include/plat/gpio-bank-mp22.h
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

#define S5PV2XX_MP22CON			(S5PV2XX_MP22_BASE + 0x00)
#define S5PV2XX_MP22DAT			(S5PV2XX_MP22_BASE + 0x04)
#define S5PV2XX_MP22PUD			(S5PV2XX_MP22_BASE + 0x08)
#define S5PV2XX_MP22DRV			(S5PV2XX_MP22_BASE + 0x0c)
#define S5PV2XX_MP22CONPDN		(S5PV2XX_MP22_BASE + 0x10)
#define S5PV2XX_MP22PUDPDN		(S5PV2XX_MP22_BASE + 0x14)

#define S5PV2XX_MP22_CONMASK(__gpio)	(0xf << ((__gpio) * 4))
#define S5PV2XX_MP22_INPUT(__gpio)	(0x0 << ((__gpio) * 4))
#define S5PV2XX_MP22_OUTPUT(__gpio)	(0x1 << ((__gpio) * 4))

#define S5PV2XX_MP22_0_LD1_DATA_0	(0x2 << 0)
#define S5PV2XX_MP22_1_LD1_DATA_1	(0x2 << 4)
#define S5PV2XX_MP22_2_LD1_DATA_2	(0x2 << 8)
#define S5PV2XX_MP22_3_LD1_DATA_3	(0x2 << 12)
#define S5PV2XX_MP22_4_LD1_DATA_4	(0x2 << 16)
#define S5PV2XX_MP22_5_LD1_DATA_5	(0x2 << 20)
#define S5PV2XX_MP22_6_LD1_DATA_6	(0x2 << 24)
#define S5PV2XX_MP22_7_LD1_DATA_7	(0x2 << 28)

