/* linux/arch/arm/plat-s5pv2xx/include/plat/gpio-bank-k3.h
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

#define S5PV2XX_GPK3CON			(S5PV2XX_GPK3_BASE + 0x00)
#define S5PV2XX_GPK3DAT			(S5PV2XX_GPK3_BASE + 0x04)
#define S5PV2XX_GPK3PUD			(S5PV2XX_GPK3_BASE + 0x08)
#define S5PV2XX_GPK3DRV			(S5PV2XX_GPK3_BASE + 0x0c)
#define S5PV2XX_GPK3CONPDN		(S5PV2XX_GPK3_BASE + 0x10)
#define S5PV2XX_GPK3PUDPDN		(S5PV2XX_GPK3_BASE + 0x14)

#define S5PV2XX_GPK3_CONMASK(__gpio)	(0xf << ((__gpio) * 4))
#define S5PV2XX_GPK3_INPUT(__gpio)	(0x0 << ((__gpio) * 4))
#define S5PV2XX_GPK3_OUTPUT(__gpio)	(0x1 << ((__gpio) * 4))

#define S5PV2XX_GPK3_0_CF_IORDY		(0x2 << 0)
#define S5PV2XX_GPK3_1_CF_INTRQ		(0x2 << 4)
#define S5PV2XX_GPK3_2_CF_RESET		(0x2 << 8)
#define S5PV2XX_GPK3_3_CF_INPACKn	(0x2 << 12)
#define S5PV2XX_GPK3_4_CF_REG		(0x2 << 16)
#define S5PV2XX_GPK3_5_CF_CDn		(0x2 << 20)
#define S5PV2XX_GPK3_6_CF_IORD_CFn	(0x2 << 24)
#define S5PV2XX_GPK3_7_CF_IOWR_CFn	(0x2 << 28)
