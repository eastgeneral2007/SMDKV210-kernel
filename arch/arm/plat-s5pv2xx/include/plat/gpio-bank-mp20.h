/* linux/arch/arm/plat-s5pc1xx/include/plat/gpio-bank-mp20.h
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

#define S5PV2XX_MP20CON			(S5PV2XX_MP20_BASE + 0x00)
#define S5PV2XX_MP20DAT			(S5PV2XX_MP20_BASE + 0x04)
#define S5PV2XX_MP20PUD			(S5PV2XX_MP20_BASE + 0x08)
#define S5PV2XX_MP20DRV			(S5PV2XX_MP20_BASE + 0x0c)
#define S5PV2XX_MP20CONPDN		(S5PV2XX_MP20_BASE + 0x10)
#define S5PV2XX_MP20PUDPDN		(S5PV2XX_MP20_BASE + 0x14)

#define S5PV2XX_MP20_CONMASK(__gpio)	(0xf << ((__gpio) * 4))
#define S5PV2XX_MP20_INPUT(__gpio)	(0x0 << ((__gpio) * 4))
#define S5PV2XX_MP20_OUTPUT(__gpio)	(0x1 << ((__gpio) * 4))

#define S5PV2XX_MP20_0_LD1_ADDR_0	(0x2 << 0)
#define S5PV2XX_MP20_1_LD1_ADDR_1	(0x2 << 4)
#define S5PV2XX_MP20_2_LD1_ADDR_2	(0x2 << 8)
#define S5PV2XX_MP20_3_LD1_ADDR_3	(0x2 << 12)
#define S5PV2XX_MP20_4_LD1_ADDR_4	(0x2 << 16)
#define S5PV2XX_MP20_5_LD1_ADDR_5	(0x2 << 20)
#define S5PV2XX_MP20_6_LD1_ADDR_6	(0x2 << 24)
#define S5PV2XX_MP20_7_LD1_ADDR_7	(0x2 << 28)

