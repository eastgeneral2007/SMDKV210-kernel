/* linux/arch/arm/plat-s5pv2xx/include/plat/gpio-bank-mp01.h
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

#define S5PV2XX_MP01CON			(S5PV2XX_MP01_BASE + 0x00)
#define S5PV2XX_MP01DAT			(S5PV2XX_MP01_BASE + 0x04)
#define S5PV2XX_MP01PUD			(S5PV2XX_MP01_BASE + 0x08)
#define S5PV2XX_MP01DRV			(S5PV2XX_MP01_BASE + 0x0c)
#define S5PV2XX_MP01CONPDN		(S5PV2XX_MP01_BASE + 0x10)
#define S5PV2XX_MP01PUDPDN		(S5PV2XX_MP01_BASE + 0x14)

#define S5PV2XX_MP01_CONMASK(__gpio)	(0xf << ((__gpio) * 4))
#define S5PV2XX_MP01_INPUT(__gpio)	(0x0 << ((__gpio) * 4))
#define S5PV2XX_MP01_OUTPUT(__gpio)	(0x1 << ((__gpio) * 4))

#define S5PV2XX_MP01_0_SROM_CSn_0	(0x2 << 0)

#define S5PV2XX_MP01_1_SROM_CSn_1	(0x2 << 4)

#define S5PV2XX_MP01_2_SROM_CSn_2	(0x2 << 8)
#define S5PV2XX_MP01_2_NFCSn_0		(0x3 << 8)

#define S5PV2XX_MP01_3_SROM_CSn_3	(0x2 << 12)
#define S5PV2XX_MP01_3_NFCSn_1		(0x3 << 12)

#define S5PV2XX_MP01_4_SROM_CSn_4	(0x2 << 16)
#define S5PV2XX_MP01_4_NFCSn_2		(0x3 << 16)
#define S5PV2XX_MP01_4_ONANDXL_CSn_0	(0x5 << 16)

#define S5PV2XX_MP01_5_SROM_CSn_5	(0x2 << 20)
#define S5PV2XX_MP01_5_NFCSn_3		(0x3 << 20)
#define S5PV2XX_MP01_5_ONANDXL_CSn_1	(0x5 << 20)

#define S5PV2XX_MP01_6_EBI_OEn		(0x2 << 24)
#define S5PV2XX_MP01_7_EBI_WEn		(0x2 << 28)

