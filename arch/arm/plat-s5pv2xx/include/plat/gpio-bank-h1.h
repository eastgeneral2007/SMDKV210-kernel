/* linux/arch/arm/plat-s5pv2xx/include/plat/gpio-bank-h1.h
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

#define S5PV2XX_GPH1CON			(S5PV2XX_GPH1_BASE + 0x00)
#define S5PV2XX_GPH1DAT			(S5PV2XX_GPH1_BASE + 0x04)
#define S5PV2XX_GPH1PUD			(S5PV2XX_GPH1_BASE + 0x08)
#define S5PV2XX_GPH1DRV			(S5PV2XX_GPH1_BASE + 0x0c)
#define S5PV2XX_GPH1CONPDN		(S5PV2XX_GPH1_BASE + 0x10)
#define S5PV2XX_GPH1PUDPDN		(S5PV2XX_GPH1_BASE + 0x14)

#define S5PV2XX_GPH1_CONMASK(__gpio)	(0xf << ((__gpio) * 4))
#define S5PV2XX_GPH1_INPUT(__gpio)	(0x0 << ((__gpio) * 4))
#define S5PV2XX_GPH1_OUTPUT(__gpio)	(0x1 << ((__gpio) * 4))

#define S5PV2XX_GPH1_0_EXT_INT31_0	(0xf << 0)

#define S5PV2XX_GPH1_1_EXT_INT31_1	(0xf << 4)

#define S5PV2XX_GPH1_2_EXT_INT31_2	(0xf << 8)

#define S5PV2XX_GPH1_3_EXT_INT31_3	(0xf << 12)

#define S5PV2XX_GPH1_4_HDMI_CEC		(0x4 << 16)
#define S5PV2XX_GPH1_4_EXT_INT31_4	(0xf << 16)

#define S5PV2XX_GPH1_5_HDMI_HPD		(0x4 << 20)
#define S5PV2XX_GPH1_5_EXT_INT31_5	(0xf << 20)

#define S5PV2XX_GPH1_6_EXT_INT31_6	(0xf << 24)

#define S5PV2XX_GPH1_7_EXT_INT31_7	(0xf << 28)

