/* linux/arch/arm/plat-s3c/dev-audio.c
 *
 * Copyright (c) 2009 Samsung Electronics Co. Ltd
 * Author: Jaswinder Singh <jassi.brar@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/io.h>
#include <linux/dma-mapping.h>

#include <mach/map.h>
#include <mach/s3c-dma.h>

#include <plat/irqs.h>
#include <plat/devs.h>
#include <plat/audio.h>
#include <plat/gpio-bank-i.h>
#include <plat/gpio-bank-c.h>
#include <plat/gpio-bank-c1.h>
#include <plat/gpio-cfg.h>
#include <plat/regs-clock.h>

static int s5pv2xx_cfg_i2s(struct platform_device *pdev)
{
	/* configure GPIO for i2s port */
	switch (pdev->id) {
	case 0:
		s3c_gpio_cfgpin(S5PV2XX_GPI(0), S5PV2XX_GPI0_I2S_0_SCLK);
		s3c_gpio_cfgpin(S5PV2XX_GPI(1), S5PV2XX_GPI1_I2S_0_CDCLK);
		s3c_gpio_cfgpin(S5PV2XX_GPI(2), S5PV2XX_GPI2_I2S_0_LRCK);
		s3c_gpio_cfgpin(S5PV2XX_GPI(3), S5PV2XX_GPI3_I2S_0_SDI);
		s3c_gpio_cfgpin(S5PV2XX_GPI(4), S5PV2XX_GPI4_I2S_0_SDO0);
		s3c_gpio_cfgpin(S5PV2XX_GPI(5), S5PV2XX_GPI5_I2S_0_SDO1);
		s3c_gpio_cfgpin(S5PV2XX_GPI(6), S5PV2XX_GPI6_I2S_0_SDO2);
		break;

	case 1:
		s3c_gpio_cfgpin(S5PV2XX_GPC0(0), S5PV2XX_GPC0_I2S_1_SCLK);
		s3c_gpio_cfgpin(S5PV2XX_GPC0(1), S5PV2XX_GPC1_I2S_1_CDCLK);
		s3c_gpio_cfgpin(S5PV2XX_GPC0(2), S5PV2XX_GPC2_I2S_1_LRCK);
		s3c_gpio_cfgpin(S5PV2XX_GPC0(3), S5PV2XX_GPC3_I2S_1_SDI);
		s3c_gpio_cfgpin(S5PV2XX_GPC0(4), S5PV2XX_GPC4_I2S_1_SDO);
		break;

	case 2:
		s3c_gpio_cfgpin(S5PV2XX_GPC1(0), S5PV2XX_GPC1_0_I2S_2_SCLK);
		s3c_gpio_cfgpin(S5PV2XX_GPC1(1), S5PV2XX_GPC1_1_I2S_2_CDCLK);
		s3c_gpio_cfgpin(S5PV2XX_GPC1(2), S5PV2XX_GPC1_2_I2S_2_LRCLK);
		s3c_gpio_cfgpin(S5PV2XX_GPC1(3), S5PV2XX_GPC1_3_I2S_2_SDI);
		s3c_gpio_cfgpin(S5PV2XX_GPC1(4), S5PV2XX_GPC1_4_I2S_2_SDO);
		break;

	default:
		printk("Invalid Device %d!\n", pdev->id);
		return -EINVAL;
	}

	return 0;
}

static struct s3c_audio_pdata s3c_i2s_pdata = {
	.cfg_gpio = s5pv2xx_cfg_i2s,
};

static struct resource s5pv2xx_iis0_resource[] = {
	[0] = {
		.start = S5PV2XX_PA_IIS0, /* V50 */
		.end   = S5PV2XX_PA_IIS0 + 0x100 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = DMACH_I2S0_OUT,
		.end   = DMACH_I2S0_OUT,
		.flags = IORESOURCE_DMA,
	},
	[2] = {
		.start = DMACH_I2S0_IN,
		.end   = DMACH_I2S0_IN,
		.flags = IORESOURCE_DMA,
	},
};

struct platform_device s5pv2xx_device_iis0 = {
	.name		  = "s3c64xx-iis",
	.id		  = 0,
	.num_resources	  = ARRAY_SIZE(s5pv2xx_iis0_resource),
	.resource	  = s5pv2xx_iis0_resource,
	.dev = {
		.platform_data = &s3c_i2s_pdata,
	},
};
EXPORT_SYMBOL(s5pv2xx_device_iis0);

static struct resource s5pv2xx_iis1_resource[] = {
	[0] = {
		.start = S5PV2XX_PA_IIS1,
		.end   = S5PV2XX_PA_IIS1 + 0x100 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = DMACH_I2S1_OUT,
		.end   = DMACH_I2S1_OUT,
		.flags = IORESOURCE_DMA,
	},
	[2] = {
		.start = DMACH_I2S1_IN,
		.end   = DMACH_I2S1_IN,
		.flags = IORESOURCE_DMA,
	},
};

struct platform_device s5pv2xx_device_iis1 = {
	.name		  = "s3c64xx-iis",
	.id		  = 1,
	.num_resources	  = ARRAY_SIZE(s5pv2xx_iis1_resource),
	.resource	  = s5pv2xx_iis1_resource,
	.dev = {
		.platform_data = &s3c_i2s_pdata,
	},
};
EXPORT_SYMBOL(s5pv2xx_device_iis1);

static struct resource s5pv2xx_iis2_resource[] = {
	[0] = {
		.start = S5PV2XX_PA_IIS2,
		.end   = S5PV2XX_PA_IIS2 + 0x100 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = DMACH_I2S2_OUT,
		.end   = DMACH_I2S2_OUT,
		.flags = IORESOURCE_DMA,
	},
	[2] = {
		.start = DMACH_I2S2_IN,
		.end   = DMACH_I2S2_IN,
		.flags = IORESOURCE_DMA,
	},
};

struct platform_device s5pv2xx_device_iis2 = {
	.name		  = "s3c64xx-iis",
	.id		  = 2,
	.num_resources	  = ARRAY_SIZE(s5pv2xx_iis2_resource),
	.resource	  = s5pv2xx_iis2_resource,
	.dev = {
		.platform_data = &s3c_i2s_pdata,
	},
};
EXPORT_SYMBOL(s5pv2xx_device_iis2);

/* PCM Controller platform_devices */

static int s5pv2xx_pcm_cfg_gpio(struct platform_device *pdev)
{
	switch (pdev->id) {
	case 0:
#if defined(CONFIG_CPU_S5PV210_EVT1)
		s3c_gpio_cfgpin(S5PV2XX_GPI(0), S5PV2XX_GPI0_PCM_0_SCLK);
		s3c_gpio_cfgpin(S5PV2XX_GPI(1), S5PV2XX_GPI1_PCM_0_EXTCLK);
		s3c_gpio_cfgpin(S5PV2XX_GPI(2), S5PV2XX_GPI2_PCM_0_FSYNC);
		s3c_gpio_cfgpin(S5PV2XX_GPI(3), S5PV2XX_GPI3_PCM_0_SIN);
		s3c_gpio_cfgpin(S5PV2XX_GPI(4), S5PV2XX_GPI4_PCM_0_SOUT);
#else
		s3c_gpio_cfgpin(S5PV2XX_GPC1(0), S5PV2XX_GPC1_0_PCM_0_SCLK);
		s3c_gpio_cfgpin(S5PV2XX_GPC1(1), S5PV2XX_GPC1_1_PCM_0_EXTCLK);
		s3c_gpio_cfgpin(S5PV2XX_GPC1(2), S5PV2XX_GPC1_2_PCM_0_FSYNC);
		s3c_gpio_cfgpin(S5PV2XX_GPC1(3), S5PV2XX_GPC1_3_PCM_0_SIN);
		s3c_gpio_cfgpin(S5PV2XX_GPC1(4), S5PV2XX_GPC1_4_PCM_0_SOUT);
#endif
		break;
	case 1:
		s3c_gpio_cfgpin(S5PV2XX_GPC0(0), S5PV2XX_GPC0_PCM_1_SCLK);
		s3c_gpio_cfgpin(S5PV2XX_GPC0(1), S5PV2XX_GPC1_PCM_1_EXTCLK);
		s3c_gpio_cfgpin(S5PV2XX_GPC0(2), S5PV2XX_GPC2_PCM_1_FSYNC);
		s3c_gpio_cfgpin(S5PV2XX_GPC0(3), S5PV2XX_GPC3_PCM_1_SIN);
		s3c_gpio_cfgpin(S5PV2XX_GPC0(4), S5PV2XX_GPC4_PCM_1_SOUT);
		break;
	case 2:
#if defined(CONFIG_CPU_S5PV210_EVT1)
		s3c_gpio_cfgpin(S5PV2XX_GPC1(0), S5PV2XX_GPC1_0_PCM_2_SCLK);
		s3c_gpio_cfgpin(S5PV2XX_GPC1(1), S5PV2XX_GPC1_1_PCM_2_EXTCLK);
		s3c_gpio_cfgpin(S5PV2XX_GPC1(2), S5PV2XX_GPC1_2_PCM_2_FSYNC);
		s3c_gpio_cfgpin(S5PV2XX_GPC1(3), S5PV2XX_GPC1_3_PCM_2_SIN);
		s3c_gpio_cfgpin(S5PV2XX_GPC1(4), S5PV2XX_GPC1_4_PCM_2_SOUT);
#else
		s3c_gpio_cfgpin(S5PV2XX_GPI(0), S5PV2XX_GPI0_PCM_2_SCLK);
		s3c_gpio_cfgpin(S5PV2XX_GPI(1), S5PV2XX_GPI1_PCM_2_EXTCLK);
		s3c_gpio_cfgpin(S5PV2XX_GPI(2), S5PV2XX_GPI2_PCM_2_FSYNC);
		s3c_gpio_cfgpin(S5PV2XX_GPI(3), S5PV2XX_GPI3_PCM_2_SIN);
		s3c_gpio_cfgpin(S5PV2XX_GPI(4), S5PV2XX_GPI4_PCM_2_SOUT);
#endif
		break;
	default:
		printk(KERN_DEBUG "Invalid PCM Controller number!");
		return -EINVAL;
	}

	return 0;
}

static struct s3c_audio_pdata s3c_pcm_pdata = {
	.cfg_gpio = s5pv2xx_pcm_cfg_gpio,
};

static struct resource s5pv2xx_pcm0_resource[] = {
	[0] = {
		.start = S5PV2XX_PA_PCM0,
		.end   = S5PV2XX_PA_PCM0 + 0x100 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = DMACH_PCM0_TX,
		.end   = DMACH_PCM0_TX,
		.flags = IORESOURCE_DMA,
	},
	[2] = {
		.start = DMACH_PCM0_RX,
		.end   = DMACH_PCM0_RX,
		.flags = IORESOURCE_DMA,
	},
};

struct platform_device s5pv2xx_device_pcm0 = {
	.name		  = "samsung-pcm",
	.id		  = 0,
	.num_resources	  = ARRAY_SIZE(s5pv2xx_pcm0_resource),
	.resource	  = s5pv2xx_pcm0_resource,
	.dev = {
		.platform_data = &s3c_pcm_pdata,
	},
};
EXPORT_SYMBOL(s5pv2xx_device_pcm0);

static struct resource s5pv2xx_pcm1_resource[] = {
	[0] = {
		.start = S5PV2XX_PA_PCM1,
		.end   = S5PV2XX_PA_PCM1 + 0x100 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = DMACH_PCM1_TX,
		.end   = DMACH_PCM1_TX,
		.flags = IORESOURCE_DMA,
	},
	[2] = {
		.start = DMACH_PCM1_RX,
		.end   = DMACH_PCM1_RX,
		.flags = IORESOURCE_DMA,
	},
};

struct platform_device s5pv2xx_device_pcm1 = {
	.name		  = "samsung-pcm",
	.id		  = 1,
	.num_resources	  = ARRAY_SIZE(s5pv2xx_pcm1_resource),
	.resource	  = s5pv2xx_pcm1_resource,
	.dev = {
		.platform_data = &s3c_pcm_pdata,
	},
};
EXPORT_SYMBOL(s5pv2xx_device_pcm1);

static struct resource s5pv2xx_pcm2_resource[] = {
	[0] = {
		.start = S5PV2XX_PA_PCM2,
		.end   = S5PV2XX_PA_PCM2 + 0x100 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = DMACH_PCM2_TX,
		.end   = DMACH_PCM2_TX,
		.flags = IORESOURCE_DMA,
	},
	[2] = {
		.start = DMACH_PCM2_RX,
		.end   = DMACH_PCM2_RX,
		.flags = IORESOURCE_DMA,
	},
};

struct platform_device s5pv2xx_device_pcm2 = {
	.name		  = "samsung-pcm",
	.id		  = 2,
	.num_resources	  = ARRAY_SIZE(s5pv2xx_pcm2_resource),
	.resource	  = s5pv2xx_pcm2_resource,
	.dev = {
		.platform_data = &s3c_pcm_pdata,
	},
};
EXPORT_SYMBOL(s5pv2xx_device_pcm2);

/* AC97 Controller platform devices */

static int s5pv2xx_ac97_cfg_gpio(struct platform_device *pdev)
{
	s3c_gpio_cfgpin(S5PV2XX_GPC0(0), S5PV2XX_GPC0_AC97_BITCLK);
	s3c_gpio_cfgpin(S5PV2XX_GPC0(1), S5PV2XX_GPC1_AC97_RESETn);
	s3c_gpio_cfgpin(S5PV2XX_GPC0(2), S5PV2XX_GPC2_AC97_SYNC);
	s3c_gpio_cfgpin(S5PV2XX_GPC0(3), S5PV2XX_GPC3_AC97_SDI);
	s3c_gpio_cfgpin(S5PV2XX_GPC0(4), S5PV2XX_GPC4_AC97_SDO);

	return 0;
}

static struct resource s5pv2xx_ac97_resource[] = {
	[0] = {
		.start = S5PV2XX_PA_AC97,
		.end   = S5PV2XX_PA_AC97 + 0x100 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = DMACH_AC97_PCMOUT,
		.end   = DMACH_AC97_PCMOUT,
		.flags = IORESOURCE_DMA,
	},
	[2] = {
		.start = DMACH_AC97_PCMIN,
		.end   = DMACH_AC97_PCMIN,
		.flags = IORESOURCE_DMA,
	},
	[3] = {
		.start = DMACH_AC97_MICIN,
		.end   = DMACH_AC97_MICIN,
		.flags = IORESOURCE_DMA,
	},
	[4] = {
		.start = IRQ_AC97,
		.end   = IRQ_AC97,
		.flags = IORESOURCE_IRQ,
	},
};

static struct s3c_audio_pdata s3c_ac97_pdata = {
	.cfg_gpio = s5pv2xx_ac97_cfg_gpio,
};

static u64 s5pv2xx_ac97_dmamask = DMA_BIT_MASK(32);

struct platform_device s5pv2xx_device_ac97 = {
	.name		  = "s3c-ac97",
	.id		  = -1,
	.num_resources	  = ARRAY_SIZE(s5pv2xx_ac97_resource),
	.resource	  = s5pv2xx_ac97_resource,
	.dev = {
		.platform_data = &s3c_ac97_pdata,
		.dma_mask = &s5pv2xx_ac97_dmamask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	},
};
EXPORT_SYMBOL(s5pv2xx_device_ac97);
