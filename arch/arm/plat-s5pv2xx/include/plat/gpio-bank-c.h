/* linux/arch/arm/plat-s5pv2xx/include/plat/gpio-bank-c.h
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

#define S5PV2XX_GPCCON			(S5PV2XX_GPC_BASE + 0x00)
#define S5PV2XX_GPCDAT			(S5PV2XX_GPC_BASE + 0x04)
#define S5PV2XX_GPCPUD			(S5PV2XX_GPC_BASE + 0x08)
#define S5PV2XX_GPCDRV			(S5PV2XX_GPC_BASE + 0x0c)
#define S5PV2XX_GPCCONPDN		(S5PV2XX_GPC_BASE + 0x10)
#define S5PV2XX_GPCPUDPDN		(S5PV2XX_GPC_BASE + 0x14)

#define S5PV2XX_GPC_CONMASK(__gpio)	(0xf << ((__gpio) * 4))
#define S5PV2XX_GPC_INPUT(__gpio)	(0x0 << ((__gpio) * 4))
#define S5PV2XX_GPC_OUTPUT(__gpio)	(0x1 << ((__gpio) * 4))

#define S5PV2XX_GPC0_I2S_1_SCLK		(0x2 << 0)
#define S5PV2XX_GPC0_PCM_1_SCLK		(0x3 << 0)
#define S5PV2XX_GPC0_AC97_BITCLK	(0x4 << 0)
#define S5PV2XX_GPC0_GPIO_INT3_0	(0xf << 0)

#define S5PV2XX_GPC1_I2S_1_CDCLK	(0x2 << 4)
#define S5PV2XX_GPC1_PCM_1_EXTCLK	(0x3 << 4)
#define S5PV2XX_GPC1_AC97_RESETn	(0x4 << 4)
#define S5PV2XX_GPC1_GPIO_INT3_1	(0xf << 4)

#define S5PV2XX_GPC2_I2S_1_LRCK		(0x2 << 8)
#define S5PV2XX_GPC2_PCM_1_FSYNC	(0x3 << 8)
#define S5PV2XX_GPC2_AC97_SYNC		(0x4 << 8)
#define S5PV2XX_GPC2_GPIO_INT3_2	(0xf << 8)

#define S5PV2XX_GPC3_I2S_1_SDI		(0x2 << 12)
#define S5PV2XX_GPC3_PCM_1_SIN		(0x3 << 12)
#define S5PV2XX_GPC3_AC97_SDI		(0x4 << 12)
#define S5PV2XX_GPC3_GPIO_INT3_3	(0xf << 12)

#define S5PV2XX_GPC4_I2S_1_SDO		(0x2 << 16)
#define S5PV2XX_GPC4_PCM_1_SOUT		(0x3 << 16)
#define S5PV2XX_GPC4_AC97_SDO		(0x4 << 16)
#define S5PV2XX_GPC4_GPIO_INT3_4	(0xf << 16)

#define S5PV2XX_GPB0_SPI_MISO0          (2<<0)
#define S5PV2XX_GPB1_SPI_CLK0           (2<<4)
#define S5PV2XX_GPB2_SPI_MOSI0          (2<<8)
#define S5PV2XX_GPB3_SPI_CS0            (2<<12)

#define S5PV2XX_GPB4_SPI_MISO1          (2<<16)
#define S5PV2XX_GPB5_SPI_CLK1           (2<<20)
#define S5PV2XX_GPB6_SPI_MOSI1          (2<<24)
#define S5PV2XX_GPB7_SPI_CS1            (2<<28)

#define S5PV2XX_GPG3_0SPI_CLK2          (3<<0)
#define S5PV2XX_GPG3_1SPI_CS2           (3<<4)
#define S5PV2XX_GPG3_2SPI_MISO2         (3<<8)
#define S5PV2XX_GPG3_3SPI_MOSI2         (3<<12)
