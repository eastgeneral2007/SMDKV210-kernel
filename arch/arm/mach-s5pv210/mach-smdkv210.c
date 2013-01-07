/* linux/arch/arm/mach-s5pv210/mach-smdkv210.c
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *              http://www.samsung.com/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/list.h>
#include <linux/timer.h>
#include <linux/init.h>
#include <linux/serial_core.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/i2c.h>
#include <linux/i2c-gpio.h>
#include <linux/regulator/max8698.h>
#include <linux/delay.h>
#include <linux/mtd/nand.h>
#include <linux/mtd/partitions.h>
#include <linux/clk.h>
#include <linux/mm.h>
#include <linux/pwm_backlight.h>
#include <linux/videodev2.h>
#include <media/s5k3ba_platform.h>
#include <media/s5k4ba_platform.h>
#include <media/s5k4ea_platform.h>
#include <media/s5k6aa_platform.h>

#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/mach/irq.h>
#include <asm/setup.h>

#include <mach/hardware.h>
#include <mach/map.h>
#include <mach/regs-mem.h>
#include <mach/gpio.h>

#include <asm/irq.h>
#include <asm/mach-types.h>

#include <plat/regs-serial.h>
#include <plat/regs-rtc.h>
#include <plat/iic.h>
#include <plat/fimc.h>
#include <plat/csis.h>
#include <plat/fb.h>
#include <plat/mfc.h>

#include <plat/nand.h>
#include <plat/partition.h>
#include <plat/s5pv210.h>
#include <plat/clock.h>
#include <plat/devs.h>
#include <plat/cpu.h>
#include <plat/ts.h>
#include <plat/adc.h>
#include <plat/gpio-cfg.h>
#include <plat/regs-gpio.h>
#include <plat/regs-clock.h>
#include <plat/regs-fimc.h>
#include <plat/ide.h>

#ifdef CONFIG_S3C_SAMSUNG_PMEM
#include <linux/android_pmem.h>
#include <plat/media.h>
#endif

#ifdef CONFIG_USB_SUPPORT
#include <plat/regs-otg.h>
#include <plat/pll.h>
#include <linux/usb/ch9.h>

/* S3C_USB_CLKSRC 0: EPLL 1: CLK_48M */
#define S3C_USB_CLKSRC	1
#define OTGH_PHY_CLK_VALUE      (0x22)  /* UTMI Interface, otg_phy input clk 12Mhz Oscillator */
#endif

#if defined(CONFIG_PM)
#include <plat/pm.h>
#endif

#define UCON S3C2410_UCON_DEFAULT | S3C_UCON_PCLK
#define ULCON S3C2410_LCON_CS8 | S3C2410_LCON_PNONE | S3C2410_LCON_STOPB
#define UFCON S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE

extern struct sys_timer s5pv2xx_timer;
extern void s5pv2xx_reserve_bootmem(void);

#if defined(CONFIG_MMC_SDHCI_S3C)
extern void s3c_sdhci_set_platdata(void);
#endif

struct membank s3c_meminfo[] __initdata = {
	[0] = {
		.start = 0x20000000,
		.size = 512 * SZ_1M,
		.node = 0,
	},
	[1] = {
		.start = 0x40000000,
		.size = 512 * SZ_1M,
		.node = 0,
	},
};

static struct s3c24xx_uart_clksrc smdkv210_serial_clocks[] = {
#if defined(CONFIG_SERIAL_S5PC11X_HSUART)
/* HS-UART Clock using SCLK */
	[0] = {
		.name		= "uclk1",
		.divisor	= 1,
		.min_baud	= 0,
		.max_baud	= 0,
	},
#else
	[0] = {
		.name           = "pclk",
		.divisor        = 1,
		.min_baud       = 0,
		.max_baud       = 0,
	},
#endif
};

static struct s3c2410_uartcfg smdkv210_uartcfgs[] __initdata = {
	[0] = {
		.hwport	     = 0,
		.flags	     = 0,
		.ucon	     = S3C64XX_UCON_DEFAULT,
		.ulcon	     = S3C64XX_ULCON_DEFAULT,
		.ufcon	     = S3C64XX_UFCON_DEFAULT,
		.clocks      = smdkv210_serial_clocks,
		.clocks_size = ARRAY_SIZE(smdkv210_serial_clocks),
	},
	[1] = {
		.hwport	     = 1,
		.flags	     = 0,
		.ucon	     = S3C64XX_UCON_DEFAULT,
		.ulcon	     = S3C64XX_ULCON_DEFAULT,
		.ufcon	     = S3C64XX_UFCON_DEFAULT,
		.clocks      = smdkv210_serial_clocks,
		.clocks_size = ARRAY_SIZE(smdkv210_serial_clocks),
	},
	[2] = {
		.hwport      = 2,
		.flags       = 0,
		.ucon	     = S3C64XX_UCON_DEFAULT,
		.ulcon	     = S3C64XX_ULCON_DEFAULT,
		.ufcon	     = S3C64XX_UFCON_DEFAULT,
		.clocks      = smdkv210_serial_clocks,
		.clocks_size = ARRAY_SIZE(smdkv210_serial_clocks),
	},
	[3] = {
		.hwport      = 3,
		.flags       = 0,
		.ucon	     = S3C64XX_UCON_DEFAULT,
		.ulcon	     = S3C64XX_ULCON_DEFAULT,
		.ufcon	     = S3C64XX_UFCON_DEFAULT,
		.clocks      = smdkv210_serial_clocks,
		.clocks_size = ARRAY_SIZE(smdkv210_serial_clocks),
	},
};

/* PMIC */
static struct regulator_consumer_supply buck1_consumers[] = {
	{
		.supply		= "vddarm",
	},
};

static struct regulator_init_data max8698_buck1_data = {
	.constraints	= {
		.name		= "VCC_ARM",
		.min_uV		=  750000,
		.max_uV		= 1500000,
		.always_on	= 1,
		.valid_ops_mask	= REGULATOR_CHANGE_VOLTAGE,
		.state_mem	= {
			.uV	= 1200000,
			.mode	= REGULATOR_MODE_STANDBY,
			.enabled = 0,
		},
	},
	.num_consumer_supplies	= ARRAY_SIZE(buck1_consumers),
	.consumer_supplies	= buck1_consumers,
};

static struct regulator_consumer_supply buck2_consumers[] = {
	{
		.supply		= "vddint",
	},
};

static struct regulator_init_data max8698_buck2_data = {
	.constraints	= {
		.name		= "VCC_INTERNAL",
		.min_uV		= 1000000,
		.max_uV		= 1500000,
		.always_on	= 1,
		.valid_ops_mask	= REGULATOR_CHANGE_VOLTAGE,
		.state_mem	= {
			.uV	= 1200000,
			.mode	= REGULATOR_MODE_NORMAL,
			.enabled = 0,
		},
	},
	.num_consumer_supplies	= ARRAY_SIZE(buck2_consumers),
	.consumer_supplies	= buck2_consumers,
};

static struct regulator_init_data max8698_buck3_data = {
	.constraints	= {
		.name		= "VCC_MEM",
		.min_uV		= 1800000,
		.max_uV		= 1800000,
		.apply_uV	= 1,
		.state_mem	= {
			.uV	= 1800000,
			.mode	= REGULATOR_MODE_NORMAL,
			.enabled = 1,
		},
	},
};

static struct regulator_init_data max8698_ldo2_data = {
	.constraints	= {
		.name		= "VALIVE_1.1V",
		.min_uV		= 1100000,
		.max_uV		= 1100000,
		.apply_uV	= 1,
		.always_on	= 1,
		.state_mem	= {
			.uV	= 1100000,
			.mode	= REGULATOR_MODE_NORMAL,
			.enabled = 1,
		},
	},
};

static struct regulator_init_data max8698_ldo3_data = {
	.constraints	= {
		.name		= "VUOTG_D_1.1V/VUHOST_D_1.1V",
		.min_uV		= 1100000,
		.max_uV		= 1100000,
		.apply_uV	= 1,
		.state_mem = {
			.uV		= 1100000,
			.mode		= REGULATOR_MODE_STANDBY,
			.enabled	= 0,
		},
	},
};

static struct regulator_init_data max8698_ldo4_data = {
	.constraints	= {
		.name		= "V_MIPI_1.8V",
		.min_uV		= 1800000,
		.max_uV		= 1800000,
		.apply_uV	= 1,
		.boot_on	= 1,
		.state_mem = {
			.uV		= 1800000,
			.mode		= REGULATOR_MODE_STANDBY,
			.enabled	= 0,
		},
	},
};

static struct regulator_init_data max8698_ldo5_data = {
	.constraints	= {
		.name		= "VMMC_2.8V/VEXT_2.8V",
		.min_uV		= 2800000,
		.max_uV		= 2800000,
		.apply_uV	= 1,
		.state_mem = {
			.uV		= 2800000,
			.mode		= REGULATOR_MODE_NORMAL,
			.enabled	= 1,
		},
	},
};

static struct regulator_init_data max8698_ldo6_data = {
	.constraints	= {
		.name		= "VCC_2.6V",
		.min_uV		= 2600000,
		.max_uV		= 2600000,
		.apply_uV	= 1,
		.state_mem = {
			.uV		= 2600000,
			.mode		= REGULATOR_MODE_NORMAL,
			.enabled	= 1,
		},
	},
};

static struct regulator_init_data max8698_ldo7_data = {
	.constraints	= {
		.name		= "VDAC_2.8V",
		.min_uV		= 2800000,
		.max_uV		= 2800000,
		.apply_uV	= 1,
		.state_mem = {
			.uV		= 2800000,
			.mode		= REGULATOR_MODE_NORMAL,
			.enabled	= 1,
		},
	},
};

static struct regulator_init_data max8698_ldo8_data = {
	.constraints	= {
		.name		= "VUOTG_A_3.3V/VUHOST_A_3.3V",
		.min_uV		= 3300000,
		.max_uV		= 3300000,
		.apply_uV	= 1,
		.state_mem = {
			.uV		= 0,
			.mode		= REGULATOR_MODE_STANDBY,
			.enabled	= 0,
		},
	},
};

static struct regulator_init_data max8698_ldo9_data = {
	.constraints	= {
		.name		= "{VADC/VSYS/VKEY}_2.8V",
		.min_uV		= 3000000,
		.max_uV		= 3000000,
		.apply_uV	= 1,
		.state_mem = {
			.uV		= 3000000,
			.mode		= REGULATOR_MODE_NORMAL,
			.enabled	= 1,
		},
	},
};

static struct max8698_subdev_data smdkc110_regulators[] = {
	{ MAX8698_LDO2, &max8698_ldo2_data },
	{ MAX8698_LDO3, &max8698_ldo3_data },
	{ MAX8698_LDO4, &max8698_ldo4_data },
	{ MAX8698_LDO5, &max8698_ldo5_data },
	{ MAX8698_LDO6, &max8698_ldo6_data },
	{ MAX8698_LDO7, &max8698_ldo7_data },
	{ MAX8698_LDO8, &max8698_ldo8_data },
	{ MAX8698_LDO9, &max8698_ldo9_data },
	{ MAX8698_BUCK1, &max8698_buck1_data },
	{ MAX8698_BUCK2, &max8698_buck2_data },
	{ MAX8698_BUCK3, &max8698_buck3_data },
};

static struct max8698_platform_data max8698_platform_data = {
	.num_regulators	= ARRAY_SIZE(smdkc110_regulators),
	.regulators	= smdkc110_regulators,

	.set1		= S5PV2XX_GPH1(6),
	.set2		= S5PV2XX_GPH1(7),
	.set3		= S5PV2XX_GPH0(4),

	.dvsarm1	= 0xb,
	.dvsarm2	= 0x9,
	.dvsarm3	= 0x7,
	.dvsarm4	= 0x5,

	.dvsint1	= 0x9,
	.dvsint2	= 0x7,

};

/* I2C0 */
static struct i2c_board_info i2c_devs0[] __initdata = {
	{ I2C_BOARD_INFO("wm8580", 0x1b), },
};

/* I2C1 */
static struct i2c_board_info i2c_devs1[] __initdata = {
	{
		I2C_BOARD_INFO("s5p_ddc", (0x74>>1)),
	},
};

/* I2C2 */
static struct i2c_board_info i2c_devs2[] __initdata = {
	{
		/* The address is 0xCC used since SRAD = 0 */
		I2C_BOARD_INFO("max8698", (0xCC >> 1)),
		.platform_data = &max8698_platform_data,
	},
};

#ifdef CONFIG_S3C_SAMSUNG_PMEM
static struct android_pmem_platform_data pmem_pdata = {
	.name = "s3c-pmem",
	.no_allocator = 0,
	.cached = 0,
	.buffered = 0,
	.start = 0,
	.size = 0,
};

static struct platform_device s3c_pmem_device = {
	.name = "s3c-pmem",
	.id = 0,
	.dev = { .platform_data = &pmem_pdata },
};
#endif

struct map_desc smdkv210_iodesc[] = {};

static struct platform_device *smdkv210_devices[] __initdata = {
#ifdef CONFIG_FB_S3C
	&s3c_device_fb,
#endif
	&s3c_device_dm9000,
	&s3c_device_keypad,
#ifdef CONFIG_TOUCHSCREEN_S3C
	&s3c_device_ts,
#endif
	&s3c_device_adc,
	&s3c_device_mfc,

#ifdef CONFIG_S3C_DEV_HSMMC
	&s3c_device_hsmmc0,
#endif

#ifdef CONFIG_S3C_DEV_HSMMC1
	&s3c_device_hsmmc1,
#endif

#ifdef CONFIG_S3C_DEV_HSMMC2
	&s3c_device_hsmmc2,
#endif

#ifdef CONFIG_S3C_DEV_HSMMC3
	&s3c_device_hsmmc3,
#endif

#ifdef CONFIG_S3C2410_WATCHDOG
	&s3c_device_wdt,
#endif

#ifdef CONFIG_RTC_DRV_S3C
	&s3c_device_rtc,
#endif

#ifdef CONFIG_HAVE_PWM
	&s3c_device_timer[0],
	&s3c_device_timer[1],
	&s3c_device_timer[2],
	&s3c_device_timer[3],
#endif
	&s3c_device_usb_ohci,
	&s3c_device_usb_ehci,
	&s3c_device_usbgadget,
#if defined(CONFIG_BLK_DEV_IDE_S3C)
	&s3c_device_cfcon,
#endif
#if defined(CONFIG_MTD_NAND_S3C)
	&s3c_device_nand,
#endif

#ifdef CONFIG_SND_SOC_SMDK_WM9713
	&s5pv2xx_device_ac97,
#endif
	&s5p_device_tvout,
	&s3c_device_fimc0,
	&s3c_device_fimc1,
	&s3c_device_fimc2,
	&s3c_device_csis,
	&s3c_device_i2c0,
	&s3c_device_i2c1,
	&s3c_device_i2c2,
	&s3c_device_ipc,
	&s3c_device_jpeg,
	&s5p_device_rotator,
	&s5p_device_cec,
	&s5p_device_hpd,
	&s3c_device_g2d,
#if defined(CONFIG_SND_SMDK_WM8580) || defined(CONFIG_SND_SMDK_WM8580_LP)
	&s5pv2xx_device_iis0,
#endif
#if defined(CONFIG_SND_S5PV2XX_SOC_WM8580_PCM)
	&s5pv2xx_device_pcm1,
#endif

#ifdef CONFIG_S3C_SAMSUNG_PMEM
	&s3c_pmem_device,
#endif
};

static struct s3c_ts_mach_info s3c_ts_platform __initdata = {
	.delay			= 10000,
	.presc			= 49,
	.oversampling_shift	= 2,
	.resol_bit		= 12,
	.s3c_adc_con		= ADC_TYPE_2,
};

static struct s3c_adc_mach_info s3c_adc_platform __initdata = {
	/* s5pc100 supports 12-bit resolution */
	.delay  = 10000,
	.presc  = 49,
	.resolution = 12,
};

/*
 * External camera reset
 * Because the most of cameras take i2c bus signal, so that
 * you have to reset at the boot time for other i2c slave devices.
 * This function also called at fimc_init_camera()
 * Do optimization for cameras on your platform.
*/
static int smdkv210_cam0_power(int onoff)
{
	int err;
	/* Camera A */
	err = gpio_request(S5PV2XX_GPH0(2), "GPH0");
	if (err) {
		printk("#### failed to request GPH0 for CAM_2V8\n");
	}
	s3c_gpio_setpull(S5PV2XX_GPH0(2), S3C_GPIO_PULL_NONE);
	gpio_direction_output(S5PV2XX_GPH0(2), 0);
	gpio_direction_output(S5PV2XX_GPH0(2), 1);
	gpio_free(S5PV2XX_GPH0(2));

	return 0;
}

static int smdkv210_cam1_power(int onoff)
{
	int err;

	/* Camera B */
	err = gpio_request(S5PV2XX_GPH0(3), "GPH0");
	if (err) {
		printk("#### failed to request GPH0 for CAM_2V8\n");
	}
	s3c_gpio_setpull(S5PV2XX_GPH0(3), S3C_GPIO_PULL_NONE);
	gpio_direction_output(S5PV2XX_GPH0(3), 0);
	gpio_direction_output(S5PV2XX_GPH0(3), 1);
	gpio_free(S5PV2XX_GPH0(3));

	return 0;
}

static int smdkv210_mipi_cam_reset()
{
	int err;

	err = gpio_request(S5PV2XX_GPH0(3), "GPH0");
	if(err) {
		printk("#### failed to reset(GPH0) for MIPI CAM\n");
	}
	s3c_gpio_setpull(S5PV2XX_GPH0(3), S3C_GPIO_PULL_NONE);
	gpio_direction_output(S5PV2XX_GPH0(3), 0);
	gpio_direction_output(S5PV2XX_GPH0(3), 1);
	gpio_free(S5PV2XX_GPH0(3));

	return 0;
}

static int smdkv210_mipi_cam_power(int onoff)
{
	int err;

	/* added for V210 CAM power */
	err = gpio_request(S5PV2XX_GPH1(2), "GPH1");
	if(err) {
		printk("#### failed to request(GPH1)for CAM_2V8\n");
	}

	s3c_gpio_setpull(S5PV2XX_GPH1(2), S3C_GPIO_PULL_NONE);
	gpio_direction_output(S5PV2XX_GPH1(2), onoff);
	gpio_free(S5PV2XX_GPH1(2));

	return 0;
}

/*
 * Guide for Camera Configuration for smdkv210
 * ITU channel must be set as A or B
 * ITU CAM CH A: S5K3BA only
 * ITU CAM CH B: one of S5K3BA and S5K4BA
 * MIPI: one of S5K4EA and S5K6AA
 *
 * NOTE1: if the S5K4EA is enabled, all other cameras must be disabled
 * NOTE2: currently, only 1 MIPI camera must be enabled
 * NOTE3: it is possible to use both one ITU cam and one MIPI cam except for S5K4EA case
 *
*/
#undef CAM_ITU_CH_A
#undef S5K3BA_ENABLED
#undef S5K4BA_ENABLED
#undef S5K4EA_ENABLED
#define S5K6AA_ENABLED
#undef WRITEBACK_ENABLED

/* External camera module setting */
/* 2 ITU Cameras */
#ifdef S5K3BA_ENABLED
static struct s5k3ba_platform_data s5k3ba_plat = {
	.default_width = 640,
	.default_height = 480,
	.pixelformat = V4L2_PIX_FMT_VYUY,
	.freq = 24000000,
	.is_mipi = 0,
};

static struct i2c_board_info  s5k3ba_i2c_info = {
	I2C_BOARD_INFO("S5K3BA", 0x2d),
	.platform_data = &s5k3ba_plat,
};

static struct s3c_platform_camera s5k3ba = {
#ifdef CAM_ITU_CH_A
	.id		= CAMERA_PAR_A,
#else
	.id		= CAMERA_PAR_B,
#endif
	.type		= CAM_TYPE_ITU,
	.fmt		= ITU_601_YCBCR422_8BIT,
	.order422	= CAM_ORDER422_8BIT_CRYCBY,
	.i2c_busnum	= 0,
	.info		= &s5k3ba_i2c_info,
	.pixelformat	= V4L2_PIX_FMT_VYUY,
	.srclk_name	= "mout_epll",
#ifdef CAM_ITU_CH_A
	.clk_name	= "sclk_cam0",
#else
	.clk_name	= "sclk_cam1",
#endif
	.clk_rate	= 24000000,
	.line_length	= 1920,
	.width		= 640,
	.height		= 480,
	.window		= {
		.left	= 0,
		.top	= 0,
		.width	= 640,
		.height	= 480,
	},

	/* Polarity */
	.inv_pclk	= 0,
	.inv_vsync	= 1,
	.inv_href	= 0,
	.inv_hsync	= 0,

	.initialized	= 0,
#ifdef CAM_ITU_CH_A
	.cam_power	= smdkv210_cam0_power,
#else
	.cam_power	= smdkv210_cam1_power,
#endif
};
#endif

#ifdef S5K4BA_ENABLED
static struct s5k4ba_platform_data s5k4ba_plat = {
	.default_width = 800,
	.default_height = 600,
	.pixelformat = V4L2_PIX_FMT_UYVY,
	.freq = 44000000,
	.is_mipi = 0,
};

static struct i2c_board_info  s5k4ba_i2c_info = {
	I2C_BOARD_INFO("S5K4BA", 0x2d),
	.platform_data = &s5k4ba_plat,
};

static struct s3c_platform_camera s5k4ba = {
#ifdef CAM_ITU_CH_A
	.id		= CAMERA_PAR_A,
#else
	.id		= CAMERA_PAR_B,
#endif
	.type		= CAM_TYPE_ITU,
	.fmt		= ITU_601_YCBCR422_8BIT,
	.order422	= CAM_ORDER422_8BIT_CBYCRY,
	.i2c_busnum	= 0,
	.info		= &s5k4ba_i2c_info,
	.pixelformat	= V4L2_PIX_FMT_UYVY,
	.srclk_name	= "mout_mpll",
#ifdef CAM_ITU_CH_A
	.clk_name	= "sclk_cam0",
#else
	.clk_name	= "sclk_cam1",
#endif
	.clk_rate	= 44000000,
	.line_length	= 1920,
	.width		= 800,
	.height		= 600,
	.window		= {
		.left	= 0,
		.top	= 0,
		.width	= 800,
		.height	= 600,
	},

	/* Polarity */
	.inv_pclk	= 0,
	.inv_vsync	= 1,
	.inv_href	= 0,
	.inv_hsync	= 0,

	.initialized	= 0,
#ifdef CAM_ITU_CH_A
	.cam_power	= smdkv210_cam0_power,
#else
	.cam_power	= smdkv210_cam1_power,
#endif
};
#endif

/* 2 MIPI Cameras */
#ifdef S5K4EA_ENABLED
static struct s5k6aa_platform_data s5k4ea_plat = {
	.default_width = 1920,
	.default_height = 1080,
	.pixelformat = V4L2_PIX_FMT_UYVY,
	.freq = 24000000,
	.is_mipi = 1,
};

static struct i2c_board_info  s5k4ea_i2c_info = {
	I2C_BOARD_INFO("S5K4EA", 0x2d),
	.platform_data = &s5k4ea_plat,
};

static struct s3c_platform_camera s5k4ea = {
	.id		= CAMERA_CSI_C,
	.type		= CAM_TYPE_MIPI,
	.fmt		= MIPI_CSI_YCBCR422_8BIT,
	.order422	= CAM_ORDER422_8BIT_CBYCRY,
	.i2c_busnum	= 0,
	.info		= &s5k4ea_i2c_info,
	.pixelformat	= V4L2_PIX_FMT_UYVY,
	.srclk_name	= "mout_mpll",
	.clk_name	= "sclk_cam0",
	.clk_rate	= 48000000,
	.line_length	= 1920,
	.width		= 1920,
	.height		= 1080,
	.window		= {
		.left	= 0,
		.top	= 0,
		.width	= 1920,
		.height	= 1080,
	},

	.mipi_lanes	= 2,
	.mipi_settle	= 12,
	.mipi_align	= 32,

	/* Polarity */
	.inv_pclk	= 0,
	.inv_vsync	= 1,
	.inv_href	= 0,
	.inv_hsync	= 0,

	.initialized	= 0,
	.cam_power	= smdkv210_mipi_cam_power,
};
#endif

#ifdef S5K6AA_ENABLED
static struct s5k6aa_platform_data s5k6aa_plat = {
	.default_width = 640,
	.default_height = 480,
	.pixelformat = V4L2_PIX_FMT_UYVY,
	.freq = 24000000,
	.is_mipi = 1,
};

static struct i2c_board_info  s5k6aa_i2c_info = {
	I2C_BOARD_INFO("S5K6AA", 0x3c),
	.platform_data = &s5k6aa_plat,
};

static struct s3c_platform_camera s5k6aa = {
	.id		= CAMERA_CSI_C,
	.type		= CAM_TYPE_MIPI,
	.fmt		= MIPI_CSI_YCBCR422_8BIT,
	.order422	= CAM_ORDER422_8BIT_CBYCRY,
	.i2c_busnum	= 0,
	.info		= &s5k6aa_i2c_info,
	.pixelformat	= V4L2_PIX_FMT_UYVY,
	.srclk_name	= "mout_epll",
	.clk_name	= "sclk_cam0",
	.clk_rate	= 24000000,
	.line_length	= 1920,
	/* default resol for preview kind of thing */
	.width		= 640,
	.height		= 480,
	.window		= {
		.left	= 0,
		.top	= 0,
		.width	= 640,
		.height	= 480,
	},

	.mipi_lanes	= 1,
	.mipi_settle	= 6,
	.mipi_align	= 32,

	/* Polarity */
	.inv_pclk	= 0,
	.inv_vsync	= 1,
	.inv_href	= 0,
	.inv_hsync	= 0,

	.initialized	= 0,
	.cam_power	= smdkv210_mipi_cam_power,
};
#endif

#ifdef WRITEBACK_ENABLED
static struct i2c_board_info  writeback_i2c_info = {
	I2C_BOARD_INFO("WriteBack", 0x0),
};

static struct s3c_platform_camera writeback = {
	.id		= CAMERA_WB,
	.fmt		= ITU_601_YCBCR422_8BIT,
	.order422	= CAM_ORDER422_8BIT_CBYCRY,
	.i2c_busnum	= 0,
	.info		= &writeback_i2c_info,
//	.pixelformat	= V4L2_PIX_FMT_UYVY,	/* not sure */
	.pixelformat	= V4L2_PIX_FMT_YUV444,
	.line_length	= 800,
	.width		= 480,
	.height		= 800,
	.window		= {
		.left	= 0,
		.top	= 0,
		.width	= 480,
		.height	= 800,
	},

	.initialized	= 0,
};

#endif

/* Interface setting */
static struct s3c_platform_fimc fimc_plat = {
#if defined(S5K4EA_ENABLED) || defined(S5K6AA_ENABLED)
	.default_cam	= CAMERA_CSI_C,
#else

#ifdef WRITEBACK_ENABLED
	.default_cam	= CAMERA_WB,
#elif CAM_ITU_CH_A
	.default_cam	= CAMERA_PAR_A,
#else
	.default_cam	= CAMERA_PAR_B,
#endif

#endif
	.camera		= {
#ifdef S5K3BA_ENABLED
		&s5k3ba,
#endif
#ifdef S5K4BA_ENABLED
		&s5k4ba,
#endif
#ifdef S5K4EA_ENABLED
		&s5k4ea,
#endif
#ifdef S5K6AA_ENABLED
		&s5k6aa,
#endif
#ifdef WRITEBACK_ENABLED
		&writeback,
#endif
	},
	.hw_ver		= 0x43,
};

#if defined(CONFIG_HAVE_PWM)
static struct platform_pwm_backlight_data smdk_backlight_data = {
	.pwm_id         = 3,
	.max_brightness = 255,
	.dft_brightness = 255,
	.pwm_period_ns  = 78770,
};

static struct platform_device smdk_backlight_device = {
	.name           = "pwm-backlight",
	.dev            = {
		.parent = &s3c_device_timer[3].dev,
		.platform_data = &smdk_backlight_data,
	},
};
static void __init smdk_backlight_register(void)
{
	int ret = platform_device_register(&smdk_backlight_device);
	if (ret)
		printk(KERN_ERR "smdk: failed to register backlight device: %d\n", ret);
}
#else
#define smdk_backlight_register()	do { } while (0)
#endif

static struct s3c_ide_platdata smdkv210_ide_pdata __initdata = {
	.setup_gpio     = s5pv2xx_ide_setup_gpio,
};

static void smdkv210_power_off(void)
{
	unsigned long reg;

	reg = __raw_readl(S5P_PS_HOLD_CONTROL);
	reg &= ~(0x1 << 8);
	__raw_writel(reg, S5P_PS_HOLD_CONTROL);
}

static void __init smdkv210_map_io(void)
{
#if defined(CONFIG_ARCH_S5PV2XX)
	s3c_device_nand.name = "s5pv210-nand";
#else
	s3c_device_nand.name = "s5pc100-nand";
#endif
	s5pv2xx_init_io(smdkv210_iodesc, ARRAY_SIZE(smdkv210_iodesc));
	s3c24xx_init_clocks(24000000);
	s3c24xx_init_uarts(smdkv210_uartcfgs, ARRAY_SIZE(smdkv210_uartcfgs));
#if defined(CONFIG_SERIAL_S5PC11X_HSUART)
	/* got to have a high enough uart source clock for higher speeds */
	writel((readl(S5P_CLK_DIV4) & ~(0xffff0000)) | 0x44440000, S5P_CLK_DIV4);
#endif
	s5pv2xx_reserve_bootmem();

	pm_power_off = smdkv210_power_off;
}

static void __init smdkv210_dm9000_set(void)
{
	unsigned int tmp;

	tmp =((0<<28)|(0<<24)|(5<<16)|(0<<12)|(0<<8)|(0<<4)|(0<<0));
	__raw_writel(tmp, (S5PV2XX_SROM_BW+0x18));

	tmp = __raw_readl(S5PV2XX_SROM_BW);
	tmp &= ~(0xf<<20);

#if CONFIG_DM9000_16BIT
	tmp |= (0x1<<20);
#else
	tmp |= (0x2<<20);
#endif
	__raw_writel(tmp, S5PV2XX_SROM_BW);


	tmp = __raw_readl(S5PV2XX_MP01CON);
	tmp &= ~(0xf<<20);
	tmp |=(2<<20);
	__raw_writel(tmp,(S5PV2XX_MP01CON));
}

static void __init smdkv210_flash_set(void)
{
	unsigned int gpio;
	unsigned int tmp;

	for (gpio = S5PV2XX_GPJ1(0); gpio <= S5PV2XX_GPJ1(5); gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(4));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	}

	tmp = __raw_readl(S5PV2XX_GPJ4CON);
	tmp &= ~(0xf<<16);
	tmp |= (4<<16);
	__raw_writel(tmp, S5PV2XX_GPJ4CON);

	tmp = __raw_readl(S5PV2XX_GPJ4PUD);
	tmp &= ~(3<<8);
	__raw_writel(tmp, S5PV2XX_GPJ4PUD);

	tmp = __raw_readl(S5PV2XX_SROM_BW);
	tmp &= ~(0xf);
	tmp |= (0x1);
	__raw_writel(tmp, S5PV2XX_SROM_BW);

	tmp = __raw_readl(S5PV2XX_MP01CON);
	tmp &= ~(0xf);
	tmp |=(2);
	__raw_writel(tmp,(S5PV2XX_MP01CON));
}

#ifdef CONFIG_S3C_SAMSUNG_PMEM
static void __init s3c_pmem_set_platdata(void)
{
	pmem_pdata.start = s3c_get_media_memory_bank(S3C_MDEV_PMEM, 1);
	pmem_pdata.size = s3c_get_media_memsize_bank(S3C_MDEV_PMEM, 1);
}
#endif

static void __init smdkv210_machine_init(void)
{
	s3c_device_nand.dev.platform_data = &s3c_nand_mtd_part_info;
	smdkv210_dm9000_set();

	smdkv210_flash_set();

#ifdef CONFIG_S3C_SAMSUNG_PMEM
	s3c_pmem_set_platdata();
#endif
	/* i2c */
	s3c_i2c0_set_platdata(NULL);
	s3c_i2c1_set_platdata(NULL);
	s3c_i2c2_set_platdata(NULL);
	i2c_register_board_info(0, i2c_devs0, ARRAY_SIZE(i2c_devs0));
	i2c_register_board_info(1, i2c_devs1, ARRAY_SIZE(i2c_devs1));
	i2c_register_board_info(2, i2c_devs2, ARRAY_SIZE(i2c_devs2));

	s3cfb_set_platdata(NULL);
#if defined(CONFIG_BLK_DEV_IDE_S3C)
	s3c_ide_set_platdata(&smdkv210_ide_pdata);
#endif

#if defined(CONFIG_TOUCHSCREEN_S3C)
        s3c_ts_set_platdata(&s3c_ts_platform);
#endif

#if defined(CONFIG_S5PV2XX_ADC)
        s3c_adc_set_platdata(&s3c_adc_platform);
#endif

	/* fimc */
	s3c_fimc0_set_platdata(&fimc_plat);
	s3c_fimc1_set_platdata(&fimc_plat);
	s3c_fimc2_set_platdata(&fimc_plat);
	s3c_csis_set_platdata(NULL);
	smdkv210_cam0_power(1);
	smdkv210_cam1_power(1);
	smdkv210_mipi_cam_reset();

	/* mfc */
	s3c_mfc_set_platdata(NULL);

	platform_add_devices(smdkv210_devices, ARRAY_SIZE(smdkv210_devices));

#if defined(CONFIG_PM)
	s3c_pm_init();
#endif

#if defined(CONFIG_HAVE_PWM)
	smdk_backlight_register();
#endif

#if defined(CONFIG_MMC_SDHCI_S3C)
	s3c_sdhci_set_platdata();
#endif
}

static void __init smdkv210_fixup(struct machine_desc *desc,
					struct tag *tags, char **cmdline,
					struct meminfo *mi)
{
	u32 i = 0;

	for (i = 0; i < ARRAY_SIZE(s3c_meminfo); i++)
		mi->bank[i] = s3c_meminfo[i];
	mi->nr_banks = ARRAY_SIZE(s3c_meminfo);
}

MACHINE_START(SMDKV210, "smdkv210")
	/* Maintainer: Ben Dooks <ben@fluff.org> */
	.phys_io	= S3C_PA_UART & 0xfff00000,
	.io_pg_offst	= (((u32)S3C_VA_UART) >> 18) & 0xfffc,
	.boot_params	= S5PV2XX_PA_SDRAM + 0x100,
	.fixup		= smdkv210_fixup,
	.init_irq	= s5pv210_init_irq,
	.map_io		= smdkv210_map_io,
	.init_machine	= smdkv210_machine_init,
	.timer		= &s5pv2xx_timer,
MACHINE_END


#ifdef CONFIG_USB_SUPPORT
/* Initializes OTG Phy. */
void otg_phy_init(void) {
	writel(readl(S5P_USB_PHY_CONTROL)|(0x1<<0), S5P_USB_PHY_CONTROL); /*USB PHY0 Enable */
	writel((readl(S3C_USBOTG_PHYPWR)&~(0x3<<3)&~(0x1<<0))|(0x1<<5), S3C_USBOTG_PHYPWR);
	writel((readl(S3C_USBOTG_PHYCLK)&~(0x5<<2))|(0x3<<0), S3C_USBOTG_PHYCLK);
	writel((readl(S3C_USBOTG_RSTCON)&~(0x3<<1))|(0x1<<0), S3C_USBOTG_RSTCON);
	udelay(10);
	writel(readl(S3C_USBOTG_RSTCON)&~(0x7<<0), S3C_USBOTG_RSTCON);
	udelay(10);

}
EXPORT_SYMBOL(otg_phy_init);

/* USB Control request data struct must be located here for DMA transfer */
struct usb_ctrlrequest usb_ctrl __attribute__((aligned(8)));
EXPORT_SYMBOL(usb_ctrl);

/* OTG PHY Power Off */
void otg_phy_off(void) {
	writel(readl(S3C_USBOTG_PHYPWR)|(0x3<<3), S3C_USBOTG_PHYPWR);
	writel(readl(S5P_USB_PHY_CONTROL)&~(1<<0), S5P_USB_PHY_CONTROL);

}
EXPORT_SYMBOL(otg_phy_off);

void usb_host_phy_init(void)
{
	struct clk *otg_clk;

	otg_clk = clk_get(NULL, "otg");
	clk_enable(otg_clk);

	if(readl(S5P_USB_PHY_CONTROL)&(0x1<<1)){
		return;
	}

	writel(readl(S5P_USB_PHY_CONTROL)|(0x1<<1), S5P_USB_PHY_CONTROL);
	writel((readl(S3C_USBOTG_PHYPWR)&~(0x1<<7)&~(0x1<<6))|(0x1<<8)|(0x1<<5), S3C_USBOTG_PHYPWR);
	writel((readl(S3C_USBOTG_PHYCLK)&~(0x1<<7))|(0x3<<0), S3C_USBOTG_PHYCLK);
	writel((readl(S3C_USBOTG_RSTCON))|(0x1<<4)|(0x1<<3), S3C_USBOTG_RSTCON);
	udelay(10);
	writel(readl(S3C_USBOTG_RSTCON)&~(0x1<<4)&~(0x1<<3), S3C_USBOTG_RSTCON);
	udelay(10);
}
EXPORT_SYMBOL(usb_host_phy_init);

void usb_host_phy_off(void)
{
	writel(readl(S3C_USBOTG_PHYPWR)|(0x1<<7)|(0x1<<6), S3C_USBOTG_PHYPWR);
	writel(readl(S5P_USB_PHY_CONTROL)&~(1<<1), S5P_USB_PHY_CONTROL);
}
EXPORT_SYMBOL(usb_host_phy_off);
#endif

#if defined(CONFIG_RTC_DRV_S3C)
/* RTC common Function for samsung APs*/
unsigned int s3c_rtc_set_bit_byte(void __iomem *base, uint offset, uint val)
{
        writeb(val, base + offset);

        return 0;
}

unsigned int s3c_rtc_read_alarm_status(void __iomem *base)
{
        return 1;
}

void s3c_rtc_set_pie(void __iomem *base, uint to)
{
        unsigned int tmp;

        tmp = readw(base + S3C2410_RTCCON) & ~S3C_RTCCON_TICEN;

        if (to)
                tmp |= S3C_RTCCON_TICEN;

        writew(tmp, base + S3C2410_RTCCON);
}

void s3c_rtc_set_freq_regs(void __iomem *base, uint freq, uint s3c_freq)
{
        unsigned int tmp;

        tmp = readw(base + S3C2410_RTCCON) & (S3C_RTCCON_TICEN | S3C2410_RTCCON_RTCEN );
        writew(tmp, base + S3C2410_RTCCON);
        s3c_freq = freq;
        tmp = (32768 / freq)-1;
        writel(tmp, base + S3C2410_TICNT);
}

void s3c_rtc_enable_set(struct platform_device *pdev,void __iomem *base, int en)
{
        unsigned int tmp;

        if (!en) {
                tmp = readw(base + S3C2410_RTCCON);
                writew(tmp & ~ (S3C2410_RTCCON_RTCEN | S3C_RTCCON_TICEN), base + S3C2410_RTCCON);
        } else {
                /* re-enable the device, and check it is ok */
                if ((readw(base+S3C2410_RTCCON) & S3C2410_RTCCON_RTCEN) == 0){
                        dev_info(&pdev->dev, "rtc disabled, re-enabling\n");

                        tmp = readw(base + S3C2410_RTCCON);
                        writew(tmp|S3C2410_RTCCON_RTCEN, base+S3C2410_RTCCON);
                }

                if ((readw(base + S3C2410_RTCCON) & S3C2410_RTCCON_CNTSEL)){
                        dev_info(&pdev->dev, "removing RTCCON_CNTSEL\n");

                        tmp = readw(base + S3C2410_RTCCON);
                        writew(tmp& ~S3C2410_RTCCON_CNTSEL, base+S3C2410_RTCCON);
                }

                if ((readw(base + S3C2410_RTCCON) & S3C2410_RTCCON_CLKRST)){
                        dev_info(&pdev->dev, "removing RTCCON_CLKRST\n");

                        tmp = readw(base + S3C2410_RTCCON);
                        writew(tmp & ~S3C2410_RTCCON_CLKRST, base+S3C2410_RTCCON);
                }
        }
}
#endif
#if defined(CONFIG_KEYPAD_S3C) || defined(CONFIG_KEYPAD_S3C_MODULE)
#if defined(CONFIG_KEYPAD_S3C_MSM)
void s3c_setup_keypad_cfg_gpio(void)
{
	unsigned int gpio;
	unsigned int end;

	/* gpio setting for KP_COL0 */
	s3c_gpio_cfgpin(S5PV2XX_GPJ1(5), S3C_GPIO_SFN(3));
	s3c_gpio_setpull(S5PV2XX_GPJ1(5), S3C_GPIO_PULL_NONE);


	/* gpio setting for KP_COL1 ~ KP_COL7 and KP_ROW0 */
	end = S5PV2XX_GPJ2(8);
	for (gpio = S5PV2XX_GPJ2(0); gpio < end; gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(3));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	}

	/* gpio setting for KP_ROW1 ~ KP_ROW8 */
	end = S5PV2XX_GPJ3(8);
	for (gpio = S5PV2XX_GPJ3(0); gpio < end; gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(3));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	}

        /* gpio setting for KP_ROW9 ~ KP_ROW13 */
	end = S5PV2XX_GPJ4(5);
	for (gpio = S5PV2XX_GPJ4(0); gpio < end; gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(3));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	}
}
#else
void s3c_setup_keypad_cfg_gpio(int rows, int columns)
{
	unsigned int gpio;
	unsigned int end;

	end = S5PV2XX_GPH3(rows);

	/* Set all the necessary GPH2 pins to special-function 0 */
	for (gpio = S5PV2XX_GPH3(0); gpio < end; gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(3));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	}

	end = S5PV2XX_GPH2(columns);

	/* Set all the necessary GPK pins to special-function 0 */
	for (gpio = S5PV2XX_GPH2(0); gpio < end; gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(3));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	}
}
#endif /* if defined(CONFIG_KEYPAD_S3C_MSM)*/

EXPORT_SYMBOL(s3c_setup_keypad_cfg_gpio);
#endif
