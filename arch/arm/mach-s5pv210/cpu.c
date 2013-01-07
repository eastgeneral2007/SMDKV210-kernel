/* linux/arch/arm/mach-s5pc100/cpu.c
 *
 * Copyright 2008 Samsung Electronics
 * Copyright 2008 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *	http://armlinux.simtec.co.uk/
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
#include <linux/clk.h>
#include <linux/io.h>
#include <linux/sysdev.h>
#include <linux/serial_core.h>
#include <linux/platform_device.h>

#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/mach/irq.h>
#include <asm/proc-fns.h>
#include <asm/irq.h>

#include <mach/hardware.h>
#include <mach/idle.h>
#include <mach/map.h>
#include <mach/reset.h>

#include <plat/cpu-freq.h>
#include <plat/regs-serial.h>

#include <plat/cpu.h>
#include <plat/devs.h>
#include <plat/clock.h>
#include <plat/sdhci.h>
#include <plat/iic-core.h>
#include <plat/s5pv210.h>

#include <plat/regs-clock.h>

#undef T32_PROBE_DEBUGGING

#if defined(T32_PROBE_DEBUGGING)
#include <linux/gpio.h>
#include <plat/gpio-cfg.h>
#include <plat/regs-gpio.h>
#endif

/* Initial IO mappings */

static struct map_desc s5pv210_iodesc[] __initdata = {
	IODESC_ENT(LCD),
	IODESC_ENT(SROMC),
	IODESC_ENT(SYSTIMER),
        IODESC_ENT(OTG),
        IODESC_ENT(OTGSFR),
        IODESC_ENT(SYSCON),
        IODESC_ENT(GPIO),
        IODESC_ENT(NAND),
        IODESC_ENT(AUDSS),
	//IODESC_ENT(HOSTIFB),
};

/* s5pv210_map_io
 *
 * register the standard cpu IO areas
*/

static void s5pv210_idle(void)
{
	unsigned int tmp;
/*
 * 1. Set CFG_DIDLE field of IDLE_CFG. 
 * (0x0 for IDLE and 0x1 for DEEP-IDLE)
 * 2. Set TOP_LOGIC field of IDLE_CFG to 0x2
 * 3. Set CFG_STANDBYWFI field of PWR_CFG to 2'b01.
 * 4. Set PMU_INT_DISABLE bit of OTHERS register to 1'b01 to prevent interrupts from
 *    occurring while entering IDLE mode.
 * 5. Execute Wait For Interrupt instruction (WFI).
 */
	tmp = __raw_readl(S5P_IDLE_CFG);
	tmp &=~ ((3<<30)|(3<<28)|(1<<0));	// No DEEP IDLE
	tmp |= ((2<<30)|(2<<28));		// TOP logic : ON
	__raw_writel(tmp, S5P_IDLE_CFG);

	tmp = __raw_readl(S5P_PWR_CFG);
	tmp &= S5P_CFG_WFI_CLEAN;
	__raw_writel(tmp, S5P_PWR_CFG);

	cpu_do_idle();
}
void __init s5pv210_map_io(void)
{
	iotable_init(s5pv210_iodesc, ARRAY_SIZE(s5pv210_iodesc));

	/* HS-MMC Platform data init*/
        s3c6410_default_sdhci0();
        s3c6410_default_sdhci1();
        s3c6410_default_sdhci2();
        s3c6410_default_sdhci3();	

	/* set s5pv210 idle function */
	s5pv2xx_idle = s5pv210_idle;
}

void __init s5pv210_init_clocks(int xtal)
{
	printk(KERN_DEBUG "%s: initialising clocks\n", __func__);
	s3c24xx_register_baseclocks(xtal);
	s5pv2xx_register_clocks();
	s5pv210_register_clocks();
	s5pv210_setup_clocks();
#if defined(CONFIG_HAVE_PWM)
        s3c_pwmclk_init();
#endif	
}

void __init s5pv210_init_irq(void)
{
	/* VIC0, VIC1, and VIC2 are fully populated. */
	s5pv2xx_init_irq(~0, ~0, ~0, ~0);
}

struct sysdev_class s5pv210_sysclass = {
	.name	= "s5pv210-core",
};

static struct sys_device s5pv210_sysdev = {
	.cls	= &s5pv210_sysclass,
};

static int __init s5pv210_core_init(void)
{
	return sysdev_class_register(&s5pv210_sysclass);
}

core_initcall(s5pv210_core_init);

static void s5pv210_sw_reset(void)
{
	printk(KERN_DEBUG "S5PV210 SWRESET\n");
	__raw_writel(0x1, S5P_SWRESET);
}

int __init s5pv210_init(void)
{
	printk("S5PV210: Initialising architecture\n");
#if defined(CONFIG_USE_SW_RESET)
	s5pv2xx_reset_hook = s5pv210_sw_reset;
#endif
	return sysdev_register(&s5pv210_sysdev);
}
