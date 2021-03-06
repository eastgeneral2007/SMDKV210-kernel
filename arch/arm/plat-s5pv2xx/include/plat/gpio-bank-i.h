/* linux/arch/arm/plat-s5pv2xx/include/plat/gpio-bank-i.h
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

#define S5PV2XX_GPICON			(S5PV2XX_GPI_BASE + 0x00)
#define S5PV2XX_GPIDAT			(S5PV2XX_GPI_BASE + 0x04)
#define S5PV2XX_GPIPUD			(S5PV2XX_GPI_BASE + 0x08)
#define S5PV2XX_GPIDRV			(S5PV2XX_GPI_BASE + 0x0c)
#define S5PV2XX_GPICONPDN		(S5PV2XX_GPI_BASE + 0x10)
#define S5PV2XX_GPIPUDPDN		(S5PV2XX_GPI_BASE + 0x14)

#define S5PV2XX_GPI_CONMASK(__gpio)	(0xf << ((__gpio) * 4))
#define S5PV2XX_GPI_INPUT(__gpio)	(0x0 << ((__gpio) * 4))
#define S5PV2XX_GPI_OUTPUT(__gpio)	(0x1 << ((__gpio) * 4))

#define S5PV2XX_GPI0_I2S_0_SCLK		(0x2 << 0)
#if defined(CONFIG_CPU_S5PV210_EVT1)
#define S5PV2XX_GPI0_PCM_0_SCLK		(0x3 << 0)
#else
#define S5PV2XX_GPI0_PCM_2_SCLK		(0x3 << 0)
#endif

#define S5PV2XX_GPI1_I2S_0_CDCLK	(0x2 << 4)
#if defined(CONFIG_CPU_S5PV210_EVT1)
#define S5PV2XX_GPI1_PCM_0_EXTCLK	(0x3 << 4)
#else
#define S5PV2XX_GPI1_PCM_2_EXTCLK	(0x3 << 4)
#endif

#define S5PV2XX_GPI2_I2S_0_LRCK		(0x2 << 8)
#if defined(CONFIG_CPU_S5PV210_EVT1)
#define S5PV2XX_GPI2_PCM_0_FSYNC	(0x3 << 8)
#else
#define S5PV2XX_GPI2_PCM_2_FSYNC	(0x3 << 8)
#endif

#define S5PV2XX_GPI3_I2S_0_SDI		(0x2 << 12)
#if defined(CONFIG_CPU_S5PV210_EVT1)
#define S5PV2XX_GPI3_PCM_0_SIN		(0x3 << 12)
#else
#define S5PV2XX_GPI3_PCM_2_SIN		(0x3 << 12)
#endif

#define S5PV2XX_GPI4_I2S_0_SDO0		(0x2 << 16)
#if defined(CONFIG_CPU_S5PV210_EVT1)
#define S5PV2XX_GPI4_PCM_0_SOUT		(0x3 << 16)
#else
#define S5PV2XX_GPI4_PCM_2_SOUT		(0x3 << 16)
#endif

#define S5PV2XX_GPI5_I2S_0_SDO1		(0x2 << 20)

#define S5PV2XX_GPI6_I2S_0_SDO2		(0x2 << 24)

