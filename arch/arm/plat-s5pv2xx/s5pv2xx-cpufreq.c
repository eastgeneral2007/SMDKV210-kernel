/*
 *  linux/arch/arm/plat-s5pv2xx/s5pv2xx-cpufreq.c
 *
 *  CPU frequency scaling for S5PC110
 *
 *  Copyright (C) 2008 Samsung Electronics
 *
 *  Based on cpu-sa1110.c, Copyright (C) 2001 Russell King
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/err.h>
#include <linux/clk.h>
#include <linux/io.h>
#include <linux/regulator/consumer.h>
#include <linux/gpio.h>
#include <asm/system.h>

#include <mach/hardware.h>
#include <mach/map.h>

#include <plat/regs-clock.h>
#include <plat/cpu-freq.h>
#include <plat/pll.h>
#include <plat/clock.h>
#include <plat/gpio-cfg.h>
#include <plat/regs-gpio.h>

static struct clk *mpu_clk;
static struct regulator *arm_regulator;
static struct regulator *internal_regulator;

struct s3c_cpufreq_freqs s3c_freqs;

static struct cpufreq_frequency_table *s5pv210_freq_table;

#define BOOTUP_LEVEL		(L1)	/* 800MHz */
#define LOWER_BUS_SPEED

/* frequency */
/*
static struct cpufreq_frequency_table s5pv210_freq_table[] = {
	{L0, 1000*1000},
	{L1, 800*1000},
	{L2, 400*1000},
	{L3, 100*1000},
	{0, CPUFREQ_TABLE_END},
};
*/
struct s5pv2xx_dvfs_conf {
	const unsigned long	lvl;		/* DVFS level : L0,L1,L2,L3.*/
	unsigned long		arm_volt;	/* uV */
	unsigned long		int_volt;	/* uV */

/***
* clkdiv_val: divider value for each bus system.
* { APLL, A2M, HCLK_MSYS, PCLK_MSYS,
*HCLK_DSYS, PCLK_DSYS, HCLK_PSYS, PCLK_PSYS,
*		ONEDRAM}
*/
	unsigned long		clk_div0_reg;
	unsigned long		clk_div0_mask;
	unsigned long		onedram_div;
	struct s3c_freq		s5pv2xx_clk_info;

};

static struct s5pv2xx_dvfs_conf s5pv210_dvfs_conf[] = {
	{
		.lvl		= L0,
		.arm_volt	= 1300000,
		.int_volt	= 1200000,
		.clk_div0_reg	= 0x14131440,
		.clk_div0_mask	= 0x7f7f7777,
		.onedram_div	= 0x3,
		.s5pv2xx_clk_info = {

			.fclk 		= 1000000,
			.armclk 	= 1000000,
			.hclk_tns 	= 0,
			.hclk 		= 133000,
			.pclk 		= 66000,
			.hclk_msys 	= 200000,
			.pclk_msys 	= 100000,
			.hclk_dsys 	= 166000,
			.pclk_dsys 	= 83000,
		},
	}, {
		.lvl		= L1,
		.arm_volt	= 1200000,
		.int_volt	= 1200000,
		.clk_div0_reg	= 0x14131330,
		.clk_div0_mask	= 0x7f7f7777,
		.onedram_div	= 0x3,
		.s5pv2xx_clk_info = {

			.fclk 		= 800000,
			.armclk 	= 800000,
			.hclk_tns 	= 0,
			.hclk 		= 133000,
			.pclk 		= 66000,
			.hclk_msys 	= 200000,
			.pclk_msys 	= 100000,
			.hclk_dsys 	= 166000,
			.pclk_dsys 	= 83000,
		},
	}, {
		.lvl		= L2,
		.arm_volt	= 1200000,
		.int_volt	= 1200000,
		.clk_div0_reg	= 0x14131131,
		.clk_div0_mask	= 0x7f7f7777,
		.onedram_div	= 0x3,
		.s5pv2xx_clk_info = {

			.fclk 		= 800000,
			.armclk 	= 400000,
			.hclk_tns 	= 0,
			.hclk 		= 133000,
			.pclk 		= 66000,
			.hclk_msys 	= 200000,
			.pclk_msys 	= 100000,
			.hclk_dsys 	= 166000,
			.pclk_dsys 	= 83000,
		},
	}, {
#if defined(LOWER_BUS_SPEED)
		.lvl		= L3,
		.arm_volt	= 1100000,
		.int_volt	= 1100000,
		.clk_div0_reg	= 0x09070077,
		.clk_div0_mask	= 0x7f7f7777,
		.onedram_div	= 0x7,
		.s5pv2xx_clk_info = {

			.fclk 		= 800000,
			.armclk 	= 100000,
			.hclk_tns 	= 0,
			.hclk 		= 66000,
			.pclk 		= 66000,
			.hclk_msys 	= 100000,
			.pclk_msys 	= 100000,
			.hclk_dsys 	= 83000,
			.pclk_dsys 	= 83000,
#else
		.lvl		= L3,
		.arm_volt	= 1200000,
		.int_volt	= 1200000,
		.clk_div0_reg	= 0x14131033,
		.clk_div0_mask	= 0x7f7f7777,
		.onedram_div	= 0x3,
		.s5pv2xx_clk_info = {

			.fclk 		= 800000,
			.armclk 	= 200000,
			.hclk_tns 	= 0,
			.hclk 		= 133000,
			.pclk 		= 66000,
			.hclk_msys 	= 200000,
			.pclk_msys 	= 100000,
			.hclk_dsys 	= 166000,
			.pclk_dsys 	= 83000,
#endif
		},
	},
};

static int s5pv2xx_register_frequency_table(void)
{
	unsigned int nr_dvfs = sizeof(s5pv210_dvfs_conf) /
				sizeof(struct s5pv2xx_dvfs_conf);
	unsigned int iter;

	s5pv210_freq_table = kzalloc((nr_dvfs + 1) *
			sizeof(struct cpufreq_frequency_table), GFP_KERNEL);

	if (s5pv210_freq_table == NULL) {
		printk(KERN_ERR "failed to allocate memory\n");
		return -ENOMEM;
	}

	for (iter = 0; iter < nr_dvfs; iter++) {
		s5pv210_freq_table[iter].index = s5pv210_dvfs_conf[iter].lvl;
		s5pv210_freq_table[iter].frequency =
			s5pv210_dvfs_conf[iter].s5pv2xx_clk_info.armclk;
	}

	s5pv210_freq_table[nr_dvfs].index = 0;
	s5pv210_freq_table[nr_dvfs].frequency = CPUFREQ_TABLE_END;

	return 0;
}

int s5pv210_verify_speed(struct cpufreq_policy *policy)
{

	if (policy->cpu)
		return -EINVAL;

	return cpufreq_frequency_table_verify(policy, s5pv210_freq_table);
}

unsigned int s5pv210_getspeed(unsigned int cpu)
{
	unsigned long rate;

	if (cpu)
		return 0;

	rate = clk_get_rate(mpu_clk) / KHZ_T;

	return rate;
}

static int s5pv210_target(struct cpufreq_policy *policy,
		       unsigned int target_freq,
		       unsigned int relation)
{
	int ret = 0;
	unsigned long arm_clk;
	unsigned int index, reg, arm_volt, int_volt;
	unsigned int pll_changing = 0;
	unsigned int bus_speed_changing = 0;

	struct s5pv2xx_dvfs_conf *cur_dvfs;

	cur_dvfs = s5pv210_dvfs_conf;

	s3c_freqs.freqs.old = s5pv210_getspeed(0);

	if (cpufreq_frequency_table_target(policy, s5pv210_freq_table,
		target_freq, relation, &index)) {
		ret = -EINVAL;
		goto out;
	}

	arm_clk = s5pv210_freq_table[index].frequency;

	s3c_freqs.freqs.new = arm_clk;
	s3c_freqs.freqs.cpu = 0;

	if (s3c_freqs.freqs.new == s3c_freqs.freqs.old)
		return 0;

	arm_volt = s5pv210_dvfs_conf[index].arm_volt;
	int_volt = s5pv210_dvfs_conf[index].int_volt;

	/* iNew clock inforamtion update */
	memcpy(&s3c_freqs.new, &s5pv210_dvfs_conf[index].s5pv2xx_clk_info,
					sizeof(struct s3c_freq));

	cpufreq_notify_transition(&s3c_freqs.freqs, CPUFREQ_PRECHANGE);

	if (s3c_freqs.freqs.new > s3c_freqs.freqs.old) {
		/* Voltage up */
		regulator_set_voltage(arm_regulator, arm_volt,
				arm_volt);
		regulator_set_voltage(internal_regulator, int_volt,
				int_volt);
	}

	/* Check if there need to change PLL */
	if (s3c_freqs.new.fclk != s3c_freqs.old.fclk)
		pll_changing = 1;

	/* Check if there need to change System bus clock */
	if (s3c_freqs.new.hclk_msys != s3c_freqs.old.hclk_msys) {
		bus_speed_changing = 1;

		if (index == L3) {
		/* Reconfigure DRAM refresh counter value for new clock */
			__raw_writel(0x30c, S5P_VA_DMC1 + 0x30);
			__raw_writel(0x30c, S5P_VA_DMC0 + 0x30);
		}
	}
/* APLL should be changed in this level
 * APLL -> MPLL(for stable transition) -> APLL
 * Some clock source's clock API  are not prepared. Do not use clock API
 * in below code.
 */
	if (pll_changing) {
		__raw_writel(0x50c, S5P_VA_DMC1 + 0x30);

		/* SCLKAPLL -> SCLKMPLL */
		reg = __raw_readl(S5P_CLK_SRC0);
		reg &= ~(S5P_CLKSRC0_MUX200_MASK);
		reg |= (0x1 << S5P_CLKSRC0_MUX200_SHIFT);
		__raw_writel(reg, S5P_CLK_SRC0);

		do {
			reg = __raw_readl(S5P_CLK_MUX_STAT0);
		} while (reg & (0x1 << 18));

		/* Change APLL to MPLL in MFC_MUX and G3D MUX */
		reg = __raw_readl(S5P_CLK_DIV2);
		reg &= ~(S5P_CLKDIV2_G3D_MASK | S5P_CLKDIV2_MFC_MASK);
		reg |= (0x3 << S5P_CLKDIV2_G3D_SHIFT) |
				(0x3 << S5P_CLKDIV2_MFC_SHIFT);
		__raw_writel(reg, S5P_CLK_DIV2);

		do {
			reg = __raw_readl(S5P_CLK_DIV_STAT0);
		} while (reg & ((1 << 16) | (1 << 17)));

		reg = __raw_readl(S5P_CLK_SRC2);
		reg &= ~(S5P_CLKSRC2_G3D_MASK | S5P_CLKSRC2_MFC_MASK);
		reg |= (1 << S5P_CLKSRC2_G3D_SHIFT) |
				(1 << S5P_CLKSRC2_MFC_SHIFT);
		__raw_writel(reg, S5P_CLK_SRC2);

		do {
			reg = __raw_readl(S5P_CLK_MUX_STAT1);
		} while (reg & ((1 << 7) | (1 << 3)));

	}

	/* DMC0 source clock : SCLKA2M -> SCLKMPLL */
	/* DMC0 : 200Mhz -> 166Mhz */
	__raw_writel(0x50e, S5P_VA_DMC0 + 0x30);

	reg = __raw_readl(S5P_CLK_DIV6);
	reg &= ~(S5P_CLKDIV6_ONEDRAM_MASK);
	reg |= (0x3 << S5P_CLKDIV6_ONEDRAM_SHIFT);
	__raw_writel(reg, S5P_CLK_DIV6);

	do {
		reg = __raw_readl(S5P_CLK_DIV_STAT1);
	} while (reg & (1<<15));
	
	reg = __raw_readl(S5P_CLK_SRC6);
	reg &= ~(S5P_CLKSRC6_ONEDRAM_MASK);
	reg |= (0x1 << S5P_CLKSRC6_ONEDRAM_SHIFT);
	__raw_writel(reg, S5P_CLK_SRC6);

	do {
		reg = __raw_readl(S5P_CLK_MUX_STAT1);
	} while (reg & (1<<11));

	reg = __raw_readl(S5P_CLK_DIV0);

	reg &= ~(s5pv210_dvfs_conf[index].clk_div0_mask);

	reg |= (s5pv210_dvfs_conf[index].clk_div0_reg);

	__raw_writel(reg, S5P_CLK_DIV0);

	do {
		reg = __raw_readl(S5P_CLK_DIV_STAT0);
	} while (reg & 0xff);

	if (pll_changing) {
		reg = __raw_readl(S5P_CLK_SRC6);
		reg &= ~S5P_CLKSRC6_HPM_MASK;
		reg |= (1 << S5P_CLKSRC6_HPM_SHIFT);
		__raw_writel(reg, S5P_CLK_SRC6);

		do {
			reg = __raw_readl(S5P_CLK_MUX_STAT1);
		} while (reg & (1 << 18));

		/* Deselect APLL output : FOUTAPLL -> FINPLL */
		reg = __raw_readl(S5P_CLK_SRC0);
		reg &= ~S5P_CLKSRC0_APLL_MASK;
		reg |= 0 << S5P_CLKSRC0_APLL_SHIFT;
		__raw_writel(reg, S5P_CLK_SRC0);

		/* Turn off PLL */
		reg = __raw_readl(S5P_APLL_CON);
		reg &= ~(1 << 31);
		__raw_writel(reg, S5P_APLL_CON);

		/* Lock time = 300us*24Mhz = 7200(0x1c20) */
		__raw_writel(0x1c20, S5P_APLL_LOCK);

		if (index == L0)
			__raw_writel(APLL_VAL_1000, S5P_APLL_CON);
		else
			__raw_writel(APLL_VAL_800, S5P_APLL_CON);

		do {
			reg = __raw_readl(S5P_APLL_CON);
		} while (!(reg & (0x1 << 29)));

		/* Select APLL output : FINPLL -> FOUTAPLL */
		reg = __raw_readl(S5P_CLK_SRC0);
		reg &= ~S5P_CLKSRC0_APLL_MASK;
		reg |= (1 << S5P_CLKSRC0_APLL_SHIFT);
		__raw_writel(reg, S5P_CLK_SRC0);

		do {
			reg = __raw_readl(S5P_CLK_MUX_STAT0);
		} while (reg & (1 << 2));

		/* Change MPLL to A2M(@200Mhz) in MFC_MUX and G3D MUX */
		reg = __raw_readl(S5P_CLK_DIV2);
		reg &= ~(S5P_CLKDIV2_G3D_MASK | S5P_CLKDIV2_MFC_MASK);

		if (index == L0)
			reg |= (0x4 << S5P_CLKDIV2_G3D_SHIFT) |
					(0x4 << S5P_CLKDIV2_MFC_SHIFT);
		else
			reg |= (0x3 << S5P_CLKDIV2_G3D_SHIFT) |
					(0x3 << S5P_CLKDIV2_MFC_SHIFT);

		__raw_writel(reg, S5P_CLK_DIV2);

		do {
			reg = __raw_readl(S5P_CLK_DIV_STAT0);
		} while (reg & ((1 << 16) | (1 << 17)));

		reg = __raw_readl(S5P_CLK_SRC2);
		reg &= ~(S5P_CLKSRC2_G3D_MASK | S5P_CLKSRC2_MFC_MASK);
		reg |= (0 << S5P_CLKSRC2_G3D_SHIFT) |
					(0 << S5P_CLKSRC2_MFC_SHIFT);
		__raw_writel(reg, S5P_CLK_SRC2);

		do {
			reg = __raw_readl(S5P_CLK_MUX_STAT1);
		} while (reg & ((1 << 7) | (1 << 3)));

		/* Change MPLL to APLL in MSYS_MUX and HPM_MUX */
		reg = __raw_readl(S5P_CLK_SRC0);
		reg &= ~(S5P_CLKSRC0_MUX200_MASK);
		reg |= (0x0 << S5P_CLKSRC0_MUX200_SHIFT);
		__raw_writel(reg, S5P_CLK_SRC0);

		do {
			reg = __raw_readl(S5P_CLK_MUX_STAT0);
		} while (reg & (0x1 << 18));

		__raw_writel(0x618, S5P_VA_DMC1 + 0x30);
	
		/* DMC0 source clock : SCLKMPLL -> SCLKA2M */
		/* DMC0 : 166Mhz -> 200Mhz */
		reg = __raw_readl(S5P_CLK_SRC6);
		reg &= ~(S5P_CLKSRC6_ONEDRAM_MASK);
		reg |= (0x0 << S5P_CLKSRC6_ONEDRAM_SHIFT);
		__raw_writel(reg, S5P_CLK_SRC6);

		do {
			reg = __raw_readl(S5P_CLK_MUX_STAT1);
		} while (reg & (1<<11));

		reg = __raw_readl(S5P_CLK_DIV6);
		reg &= ~(S5P_CLKDIV6_ONEDRAM_MASK);
		reg |= (0x0 << S5P_CLKDIV6_ONEDRAM_SHIFT);
		__raw_writel(reg, S5P_CLK_DIV6);

		do {
			reg = __raw_readl(S5P_CLK_DIV_STAT1);
		} while (reg & (1<<15));
	
		__raw_writel(0x618, S5P_VA_DMC0 + 0x30);
	}


/* L3 level need to change memory bus speed, hence onedram clock divier and
 * memory refresh parameter should be changed
 * Only care L2 <-> L3 transition
 */
	if (bus_speed_changing) {
		reg = __raw_readl(S5P_CLK_DIV6);
		reg &= ~S5P_CLKDIV6_ONEDRAM_MASK;
		reg |= (s5pv210_dvfs_conf[index].onedram_div);
		__raw_writel(reg, S5P_CLK_DIV6);

		do {
			reg = __raw_readl(S5P_CLK_DIV_STAT1);
		} while (reg & (1<<15));

		if (index == L2) {
			/* Reconfigure DRAM refresh counter value */
			__raw_writel(0x618, S5P_VA_DMC1 + 0x30);
			__raw_writel(0x618, S5P_VA_DMC0 + 0x30);
		}
	}

	if (s3c_freqs.freqs.new < s3c_freqs.freqs.old) {
		/* Voltage down */
		regulator_set_voltage(internal_regulator, int_volt,
				int_volt);
		regulator_set_voltage(arm_regulator, arm_volt,
				arm_volt);
	}

	cpufreq_notify_transition(&s3c_freqs.freqs, CPUFREQ_POSTCHANGE);

	memcpy(&s3c_freqs.old, &s3c_freqs.new, sizeof(struct s3c_freq));
	printk(KERN_INFO "Perf changed[L%d]\n", index);

out:
	return ret;
}

#ifdef CONFIG_PM
static int s5pv210_cpufreq_suspend(struct cpufreq_policy *policy,
			pm_message_t pmsg)
{
	int ret = 0;

	return ret;
}

static int s5pv210_cpufreq_resume(struct cpufreq_policy *policy)
{
	int ret = 0;

	/* clock information update with wakeup value */
	memcpy(&s3c_freqs.old, &s5pv210_dvfs_conf[BOOTUP_LEVEL].s5pv2xx_clk_info,
					sizeof(struct s3c_freq));
	return ret;
}
#endif

static int __init s5pv210_cpu_init(struct cpufreq_policy *policy)
{
	u32 reg;
	int ret = 0;

#ifdef CLK_OUT_PROBING
	reg = __raw_readl(S5P_CLK_OUT);
	reg &= ~(0x1f << 12 | 0xf << 20);
	reg |= (0xf << 12 | 0x1 << 20);
	__raw_writel(reg, S5P_CLK_OUT);
#endif
	mpu_clk = clk_get(NULL, MPU_CLK);
	if (IS_ERR(mpu_clk))
		return PTR_ERR(mpu_clk);
#if defined(CONFIG_REGULATOR)
	arm_regulator = regulator_get(NULL, "vddarm");
	if (IS_ERR(arm_regulator)) {
		printk(KERN_ERR "failed to get resource %s\n", "vddarm");
		return PTR_ERR(arm_regulator);
	}
	internal_regulator = regulator_get(NULL, "vddint");
	if (IS_ERR(internal_regulator)) {
		printk(KERN_ERR "failed to get resource %s\n", "vddint");
		return PTR_ERR(internal_regulator);
	}

#endif

	if (policy->cpu != 0)
		return -EINVAL;
	policy->cur = policy->min = policy->max = s5pv210_getspeed(0);

	if (s5pv2xx_register_frequency_table())
		return ret;

	cpufreq_frequency_table_get_attr(s5pv210_freq_table, policy->cpu);

	policy->cpuinfo.transition_latency = 40000;

	memcpy(&s3c_freqs.old, &s5pv210_dvfs_conf[BOOTUP_LEVEL].s5pv2xx_clk_info,
					sizeof(struct s3c_freq));

	return cpufreq_frequency_table_cpuinfo(policy, s5pv210_freq_table);
}

static struct cpufreq_driver s5pv210_driver = {
	.flags		= CPUFREQ_STICKY,
	.verify		= s5pv210_verify_speed,
	.target		= s5pv210_target,
	.get		= s5pv210_getspeed,
	.init		= s5pv210_cpu_init,
	.name		= "s5pv210",
#ifdef CONFIG_PM
	.suspend	= s5pv210_cpufreq_suspend,
	.resume		= s5pv210_cpufreq_resume,
#endif
};

static int __init s5pv210_cpufreq_init(void)
{
	return cpufreq_register_driver(&s5pv210_driver);
}

late_initcall(s5pv210_cpufreq_init);
