/* linux/arch/arm/plat-s5pv2xx/include/plat/gpio-bank-j4.h
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

#define S5PV2XX_GPJ4CON			(S5PV2XX_GPJ4_BASE + 0x00)
#define S5PV2XX_GPJ4DAT			(S5PV2XX_GPJ4_BASE + 0x04)
#define S5PV2XX_GPJ4PUD			(S5PV2XX_GPJ4_BASE + 0x08)
#define S5PV2XX_GPJ4DRV			(S5PV2XX_GPJ4_BASE + 0x0c)
#define S5PV2XX_GPJ4CONPDN		(S5PV2XX_GPJ4_BASE + 0x10)
#define S5PV2XX_GPJ4PUDPDN		(S5PV2XX_GPJ4_BASE + 0x14)

#define S5PV2XX_GPJ4_CONMASK(__gpio)	(0xf << ((__gpio) * 4))
#define S5PV2XX_GPJ4_INPUT(__gpio)	(0x0 << ((__gpio) * 4))
#define S5PV2XX_GPJ4_OUTPUT(__gpio)	(0x1 << ((__gpio) * 4))

#define S5PV2XX_GPJ4_0_MSM_CSn		(0x2 << 0)
#define S5PV2XX_GPJ4_0_KP_ROW_9		(0x3 << 0)
#define S5PV2XX_GPJ4_0_CF_CSn_0		(0x4 << 0)
#define S5PV2XX_GPJ4_0_MHL_D23		(0x5 << 0)
#define S5PV2XX_GPJ4_0_GPIO_INT22_0	(0xf << 0)

#define S5PV2XX_GPJ4_1_MSM_WEn		(0x2 << 4)
#define S5PV2XX_GPJ4_1_KP_ROW_10	(0x3 << 4)
#define S5PV2XX_GPJ4_1_CF_CSn_1		(0x4 << 4)
#define S5PV2XX_GPJ4_1_MHL_HSYNC	(0x5 << 4)
#define S5PV2XX_GPJ4_1_GPIO_INT22_1	(0xf << 4)

#define S5PV2XX_GPJ4_2_MSM_Rn		(0x2 << 8)
#define S5PV2XX_GPJ4_2_KP_ROW_11	(0x3 << 8)
#define S5PV2XX_GPJ4_2_CF_IORN		(0x4 << 8)
#define S5PV2XX_GPJ4_2_MHL_IDCK		(0x5 << 8)
#define S5PV2XX_GPJ4_2_GPIO_INT22_2	(0xf << 8)

#define S5PV2XX_GPJ4_3_MSM_IRQn		(0x2 << 12)
#define S5PV2XX_GPJ4_3_KP_ROW_12	(0x3 << 12)
#define S5PV2XX_GPJ4_3_CF_IOWN		(0x4 << 12)
#define S5PV2XX_GPJ4_3_MHL_VSYNC	(0x5 << 12)
#define S5PV2XX_GPJ4_3_GPIO_INT22_3	(0xf << 12)

#define S5PV2XX_GPJ4_4_MSM_ADVN		(0x2 << 16)
#define S5PV2XX_GPJ4_4_KP_ROW_13	(0x3 << 16)
#define S5PV2XX_GPJ4_4_SROM_ADDR_16to22_6	(0x4 << 16)
#define S5PV2XX_GPJ4_4_MHL_DE		(0x5 << 16)
#define S5PV2XX_GPJ4_4_GPIO_INT22_3	(0xf << 16)

