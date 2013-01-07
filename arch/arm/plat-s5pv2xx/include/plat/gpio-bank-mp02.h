/* linux/arch/arm/plat-s5pv2xx/include/plat/gpio-bank-mp02.h
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

#define S5PV2XX_MP02CON			(S5PV2XX_MP02_BASE + 0x00)
#define S5PV2XX_MP02DAT			(S5PV2XX_MP02_BASE + 0x04)
#define S5PV2XX_MP02PUD			(S5PV2XX_MP02_BASE + 0x08)
#define S5PV2XX_MP02DRV			(S5PV2XX_MP02_BASE + 0x0c)
#define S5PV2XX_MP02CONPDN		(S5PV2XX_MP02_BASE + 0x10)
#define S5PV2XX_MP02PUDPDN		(S5PV2XX_MP02_BASE + 0x14)

#define S5PV2XX_MP02_CONMASK(__gpio)	(0xf << ((__gpio) * 4))
#define S5PV2XX_MP02_INPUT(__gpio)	(0x0 << ((__gpio) * 4))
#define S5PV2XX_MP02_OUTPUT(__gpio)	(0x1 << ((__gpio) * 4))

#define S5PV2XX_MP02_0_EBI_BEn_0	(0x2 << 0)
#define S5PV2XX_MP02_1_EBI_BEn_1	(0x2 << 4)
#define S5PV2XX_MP02_2_SROM_WAITn_	(0x2 << 8)
#define S5PV2XX_MP02_3_EBI_DATA_RDn	(0x2 << 12)

