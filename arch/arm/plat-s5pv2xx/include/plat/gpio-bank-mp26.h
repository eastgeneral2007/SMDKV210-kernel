/* linux/arch/arm/plat-s5pc1xx/include/plat/gpio-bank-mp26.h
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

#define S5PV2XX_MP26CON			(S5PV2XX_MP26_BASE + 0x00)
#define S5PV2XX_MP26DAT			(S5PV2XX_MP26_BASE + 0x04)
#define S5PV2XX_MP26PUD			(S5PV2XX_MP26_BASE + 0x08)
#define S5PV2XX_MP26DRV			(S5PV2XX_MP26_BASE + 0x0c)
#define S5PV2XX_MP26CONPDN		(S5PV2XX_MP26_BASE + 0x10)
#define S5PV2XX_MP26PUDPDN		(S5PV2XX_MP26_BASE + 0x14)

#define S5PV2XX_MP26_CONMASK(__gpio)	(0xf << ((__gpio) * 4))
#define S5PV2XX_MP26_INPUT(__gpio)	(0x0 << ((__gpio) * 4))
#define S5PV2XX_MP26_OUTPUT(__gpio)	(0x1 << ((__gpio) * 4))

#define S5PV2XX_MP26_0_LD1_DQS_0	(0x2 << 0)
#define S5PV2XX_MP26_1_LD1_DQS_1	(0x2 << 4)
#define S5PV2XX_MP26_2_LD1_DQS_2	(0x2 << 8)
#define S5PV2XX_MP26_3_LD1_DQS_3	(0x2 << 12)
#define S5PV2XX_MP26_4_LD1_DQSn_0	(0x2 << 16)
#define S5PV2XX_MP26_5_LD1_DQSn_1	(0x2 << 20)
#define S5PV2XX_MP26_6_LD1_DQSn_2	(0x2 << 24)
#define S5PV2XX_MP26_7_LD1_DQSn_3	(0x2 << 28)

