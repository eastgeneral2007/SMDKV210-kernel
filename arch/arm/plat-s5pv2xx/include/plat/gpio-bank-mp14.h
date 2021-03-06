/* linux/arch/arm/plat-s5pc1xx/include/plat/gpio-bank-mp14.h
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

#define S5PV2XX_MP14CON			(S5PV2XX_MP14_BASE + 0x00)
#define S5PV2XX_MP14DAT			(S5PV2XX_MP14_BASE + 0x04)
#define S5PV2XX_MP14PUD			(S5PV2XX_MP14_BASE + 0x08)
#define S5PV2XX_MP14DRV			(S5PV2XX_MP14_BASE + 0x0c)
#define S5PV2XX_MP14CONPDN		(S5PV2XX_MP14_BASE + 0x10)
#define S5PV2XX_MP14PUDPDN		(S5PV2XX_MP14_BASE + 0x14)

#define S5PV2XX_MP14_CONMASK(__gpio)	(0xf << ((__gpio) * 4))
#define S5PV2XX_MP14_INPUT(__gpio)	(0x0 << ((__gpio) * 4))
#define S5PV2XX_MP14_OUTPUT(__gpio)	(0x1 << ((__gpio) * 4))

#define S5PV2XX_MP14_0_LD0_DATA_16	(0x2 << 0)
#define S5PV2XX_MP14_1_LD0_DATA_17	(0x2 << 4)
#define S5PV2XX_MP14_2_LD0_DATA_18	(0x2 << 8)
#define S5PV2XX_MP14_3_LD0_DATA_19	(0x2 << 12)
#define S5PV2XX_MP14_4_LD0_DATA_20	(0x2 << 16)
#define S5PV2XX_MP14_5_LD0_DATA_21	(0x2 << 20)
#define S5PV2XX_MP14_6_LD0_DATA_22	(0x2 << 24)
#define S5PV2XX_MP14_7_LD0_DATA_23	(0x2 << 28)

