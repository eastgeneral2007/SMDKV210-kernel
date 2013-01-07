/* linux/arch/arm/plat-s5pv2xx/include/plat/gpio-bank-b.h
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

#define S5PV2XX_GPBCON			(S5PV2XX_GPB_BASE + 0x00)
#define S5PV2XX_GPBDAT			(S5PV2XX_GPB_BASE + 0x04)
#define S5PV2XX_GPBPUD			(S5PV2XX_GPB_BASE + 0x08)
#define S5PV2XX_GPBDRV			(S5PV2XX_GPB_BASE + 0x0c)
#define S5PV2XX_GPBCONPDN		(S5PV2XX_GPB_BASE + 0x10)
#define S5PV2XX_GPBPUDPDN		(S5PV2XX_GPB_BASE + 0x14)

#define S5PV2XX_GPB_CONMASK(__gpio)	(0xf << ((__gpio) * 4))
#define S5PV2XX_GPB_INPUT(__gpio)	(0x0 << ((__gpio) * 4))
#define S5PV2XX_GPB_OUTPUT(__gpio)	(0x1 << ((__gpio) * 4))

#define S5PV2XX_GPB0_SPI_0_CLK		(0x2 << 0)
#define S5PV2XX_GPB0_GPIO_INT_0		(0xf << 0)

#define S5PV2XX_GPB1_SPI_0_nSS		(0x2 << 4)
#define S5PV2XX_GPB1_GPIO_INT_1		(0xf << 4)

#define S5PV2XX_GPB2_SPI_0_MISO		(0x2 << 8)
#define S5PV2XX_GPB2_GPIO_INT_2		(0xf << 8)

#define S5PV2XX_GPB3_SPI_0_MOSI		(0x2 << 12)
#define S5PV2XX_GPB3_GPIO_INT_3		(0xf << 12)

#define S5PV2XX_GPB4_SPI_1_CLK		(0x2 << 16)
#define S5PV2XX_GPB4_GPIO_INT_4		(0xf << 16)

#define S5PV2XX_GPB5_SPI_1_nSS		(0x2 << 20)
#define S5PV2XX_GPB5_GPIO_INT_5		(0xf << 20)

#define S5PV2XX_GPB6_SPI_1_MISO		(0x2 << 24)
#define S5PV2XX_GPB6_GPIO_INT_6		(0xf << 24)

#define S5PV2XX_GPB7_SPI_1_MOSI		(0x2 << 28)
#define S5PV2XX_GPB7_GPIO_INT_7		(0xf << 28)

