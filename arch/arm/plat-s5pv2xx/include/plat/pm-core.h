/* linux/arch/arm/plat-s3c24xx/include/plat/pll.h
 *
 * Copyright 2008 Simtec Electronics
 *      Ben Dooks <ben@simtec.co.uk>
 *      http://armlinux.simtec.co.uk/
 *
 * S3C24xx - PM core support for arch/arm/plat-s3c/pm.c
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

static inline void s3c_pm_debug_init_uart(void)
{
}

static inline void s3c_pm_arch_prepare_irqs(void)
{
	__raw_writel(s3c_irqwake_intmask, S5P_WAKEUP_MASK);
	__raw_writel(s3c_irqwake_eintmask, S5P_EINT_WAKEUP_MASK);
	
	/* ack any outstanding external interrupts before we go to sleep */

}

static inline void s3c_pm_arch_stop_clocks(void)
{
}

static void s3c_pm_show_resume_irqs(int start, unsigned long which,
				    unsigned long mask);

static inline void s3c_pm_arch_show_resume_irqs(void)
{
}

/* make these defines, we currently do not have any need to change
 * the IRQ wake controls depending on the CPU we are running on */

#define s3c_irqwake_eintallow	(0xFFFFFFFF)
#define s3c_irqwake_intallow	(0)

static inline void s3c_pm_arch_update_uart(void __iomem *regs,
					   struct pm_uart_save *save)
{
}
