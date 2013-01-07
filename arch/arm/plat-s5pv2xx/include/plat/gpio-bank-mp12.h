/* linux/arch/arm/plat-s5pc1xx/include/plat/gpio-bank-mp12.h
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

#define S5PV2XX_MP12CON			(S5PV2XX_MP12_BASE + 0x00)
#define S5PV2XX_MP12DAT			(S5PV2XX_MP12_BASE + 0x04)
#define S5PV2XX_MP12PUD			(S5PV2XX_MP12_BASE + 0x08)
#define S5PV2XX_MP12DRV			(S5PV2XX_MP12_BASE + 0x0c)
#define S5PV2XX_MP12CONPDN		(S5PV2XX_MP12_BASE + 0x10)
#define S5PV2XX_MP12PUDPDN		(S5PV2XX_MP12_BASE + 0x14)

#define S5PV2XX_MP12_CONMASK(__gpio)	(0xf << ((__gpio) * 4))
#define S5PV2XX_MP12_INPUT(__gpio)	(0x0 << ((__gpio) * 4))
#define S5PV2XX_MP12_OUTPUT(__gpio)	(0x1 << ((__gpio) * 4))

#define S5PV2XX_MP12_0_LD0_DATA_0	(0x2 << 0)
#define S5PV2XX_MP12_1_LD0_DATA_1	(0x2 << 4)
#define S5PV2XX_MP12_2_LD0_DATA_2	(0x2 << 8)
#define S5PV2XX_MP12_3_LD0_DATA_3	(0x2 << 12)
#define S5PV2XX_MP12_4_LD0_DATA_4	(0x2 << 16)
#define S5PV2XX_MP12_5_LD0_DATA_5	(0x2 << 20)
#define S5PV2XX_MP12_6_LD0_DATA_6	(0x2 << 24)
#define S5PV2XX_MP12_7_LD0_DATA_7	(0x2 << 28)

