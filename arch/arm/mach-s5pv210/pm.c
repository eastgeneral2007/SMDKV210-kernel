/* linux/arch/arm/mach-s5pv210/pm.c
 *
 * Copyright (c) 2006 Samsung Electronics
 *
 *
 * S5PV210 (and compatible) Power Manager (Suspend-To-RAM) support
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <linux/init.h>
#include <linux/suspend.h>
#include <linux/errno.h>
#include <linux/time.h>
#include <linux/sysdev.h>
#include <linux/io.h>

#include <mach/hardware.h>

#include <asm/mach-types.h>

#include <plat/regs-gpio.h>
#include <plat/regs-clock.h>
#include <plat/cpu.h>
#include <plat/pm.h>

#include <mach/regs-irq.h>

#define DBG(fmt...) printk(KERN_DEBUG fmt)

void s5pv210_cpu_suspend(void)
{
	unsigned long tmp;

	/* issue the standby signal into the pm unit. Note, we
	 * issue a write-buffer drain just in case */

	tmp = 0;
/*
 * MCR p15,0,<Rd>,c7,c10,5 ; Data Memory Barrier Operation.
 * MCR p15,0,<Rd>,c7,c10,4 ; Data Synchronization Barrier operation.
 * MCR p15,0,<Rd>,c7,c0,4 ; Wait For Interrupt.
 */
#if defined(CONFIG_CPU_S5PV210_EVT0)
	tmp = __raw_readl(S5P_PWR_CFG);
	tmp &= S5P_CFG_WFI_CLEAN;
	__raw_writel(tmp, S5P_PWR_CFG);

	tmp = (1 << 2);
	__raw_writel(tmp, S5P_PWR_MODE);
#else

	asm("b 1f\n\t"
	    ".align 5\n\t"
	    "1:\n\t"
	    "mcr p15, 0, %0, c7, c10, 5\n\t"
	    "mcr p15, 0, %0, c7, c10, 4\n\t"
	    ".word 0xe320f003" :: "r" (tmp));

	/* we should never get past here */
#endif
	panic("sleep resumed to originator?");
}

static void s5pv210_pm_prepare(void)
{
	unsigned int tmp;
	/* ensure at least INFORM0 has the resume address */
	__raw_writel(virt_to_phys(s3c_cpu_resume), S5P_INFORM0);

	tmp = __raw_readl(S5P_SLEEP_CFG);
	tmp &= ~(S5P_SLEEP_CFG_OSC_EN | S5P_SLEEP_CFG_USBOSC_EN);
	__raw_writel(tmp, S5P_SLEEP_CFG);

	/* WFI for SLEEP mode configuration by SYSCON */
	tmp = __raw_readl(S5P_PWR_CFG);
	tmp &= S5P_CFG_WFI_CLEAN;
	tmp |= S5P_CFG_WFI_SLEEP;
	__raw_writel(tmp, S5P_PWR_CFG);

	/* SYSCON interrupt handling disable */
	tmp = __raw_readl(S5P_OTHERS);
	tmp |= S5P_OTHER_SYSC_INTOFF;
	__raw_writel(tmp, S5P_OTHERS);

	__raw_writel(0xffffffff, S5PV210_VIC0REG(VIC_INT_ENABLE_CLEAR));
	__raw_writel(0xffffffff, S5PV210_VIC1REG(VIC_INT_ENABLE_CLEAR));
	__raw_writel(0xffffffff, S5PV210_VIC2REG(VIC_INT_ENABLE_CLEAR));
	__raw_writel(0xffffffff, S5PV210_VIC3REG(VIC_INT_ENABLE_CLEAR));

	/* Enable RTC TICK,ALARM interrupt as a wakeup source */
	tmp = __raw_readl(S5P_WAKEUP_MASK);
	tmp &= ~((1 << 1) | (1 << 2));
	__raw_writel(tmp, S5P_WAKEUP_MASK);
}

static int s5pv210_pm_add(struct sys_device *sysdev)
{
	pm_cpu_prep = s5pv210_pm_prepare;
	pm_cpu_sleep = s5pv210_cpu_suspend;

	return 0;
}

static struct sleep_save s5pv210_sleep[] = {

};

static int s5pv210_pm_resume(struct sys_device *dev)
{
	s3c_pm_do_restore(s5pv210_sleep, ARRAY_SIZE(s5pv210_sleep));
	return 0;
}

static struct sysdev_driver s5pv210_pm_driver = {
	.add		= s5pv210_pm_add,
	.resume		= s5pv210_pm_resume,
};

static __init int s5pv210_pm_drvinit(void)
{
	printk(KERN_INFO "S5PV210 Power driver init\n");
	return sysdev_driver_register(&s5pv210_sysclass, &s5pv210_pm_driver);
}

arch_initcall(s5pv210_pm_drvinit);

