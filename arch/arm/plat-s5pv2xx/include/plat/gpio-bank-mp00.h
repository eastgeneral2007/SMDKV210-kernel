/* linux/arch/arm/plat-s5pv2xx/include/plat/gpio-bank-mp00.h
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

#define S5PV2XX_MP00CON			(S5PV2XX_MP00_BASE + 0x00)
#define S5PV2XX_MP00DAT			(S5PV2XX_MP00_BASE + 0x04)
#define S5PV2XX_MP00PUD			(S5PV2XX_MP00_BASE + 0x08)
#define S5PV2XX_MP00DRV			(S5PV2XX_MP00_BASE + 0x0c)
#define S5PV2XX_MP00CONPDN		(S5PV2XX_MP00_BASE + 0x10)
#define S5PV2XX_MP00PUDPDN		(S5PV2XX_MP00_BASE + 0x14)

#define S5PV2XX_MP00_CONMASK(__gpio)	(0xf << ((__gpio) * 4))
#define S5PV2XX_MP00_INPUT(__gpio)	(0x0 << ((__gpio) * 4))
#define S5PV2XX_MP00_OUTPUT(__gpio)	(0x1 << ((__gpio) * 4))

#define S5PV2XX_MP00_0_EBI_ADDR_0	(0x2 << 0)
#define S5PV2XX_MP00_1_EBI_ADDR_1	(0x2 << 4)
#define S5PV2XX_MP00_2_EBI_ADDR_2	(0x2 << 8)
#define S5PV2XX_MP00_3_EBI_ADDR_3	(0x2 << 12)
#define S5PV2XX_MP00_4_EBI_ADDR_4	(0x2 << 16)
#define S5PV2XX_MP00_5_EBI_ADDR_5	(0x2 << 20)
#define S5PV2XX_MP00_6_EBI_ADDR_6	(0x2 << 24)
#define S5PV2XX_MP00_7_EBI_ADDR_7	(0x2 << 28)

