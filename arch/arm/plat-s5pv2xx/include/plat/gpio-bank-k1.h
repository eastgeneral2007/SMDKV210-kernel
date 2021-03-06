/* linux/arch/arm/plat-s5pv2xx/include/plat/gpio-bank-k1.h
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

#define S5PV2XX_GPK1CON			(S5PV2XX_GPK1_BASE + 0x00)
#define S5PV2XX_GPK1DAT			(S5PV2XX_GPK1_BASE + 0x04)
#define S5PV2XX_GPK1PUD			(S5PV2XX_GPK1_BASE + 0x08)
#define S5PV2XX_GPK1DRV			(S5PV2XX_GPK1_BASE + 0x0c)
#define S5PV2XX_GPK1CONPDN		(S5PV2XX_GPK1_BASE + 0x10)
#define S5PV2XX_GPK1PUDPDN		(S5PV2XX_GPK1_BASE + 0x14)

#define S5PV2XX_GPK1_CONMASK(__gpio)	(0xf << ((__gpio) * 4))
#define S5PV2XX_GPK1_INPUT(__gpio)	(0x0 << ((__gpio) * 4))
#define S5PV2XX_GPK1_OUTPUT(__gpio)	(0x1 << ((__gpio) * 4))

#define S5PV2XX_GPK1_0_EBI_BEn0		(0x2 << 0)
#define S5PV2XX_GPK1_1_EBI_BEn1		(0x2 << 4)
#define S5PV2XX_GPK1_2_SROM_WAITn	(0x2 << 8)
#define S5PV2XX_GPK1_3_EBI_DATA_RDn	(0x2 << 12)
#define S5PV2XX_GPK1_4_CF_OEn		(0x2 << 16)
#define S5PV2XX_GPK1_5_CF_WEn		(0x2 << 20)

