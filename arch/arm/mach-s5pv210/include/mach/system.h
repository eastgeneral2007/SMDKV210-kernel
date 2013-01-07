/* linux/arch/arm/mach-s5pv210/include/mach/system.h
 *
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *      Ben Dooks <ben@simtec.co.uk>
 *      http://armlinux.simtec.co.uk/
 *
 * S5PV210 - system implementation
 */

#include <mach/idle.h>
#include <mach/reset.h>

#ifndef __ASM_ARCH_SYSTEM_H
#define __ASM_ARCH_SYSTEM_H __FILE__

void (*s5pv2xx_idle)(void);
void (*s5pv2xx_reset_hook)(void);

void s5pv2xx_default_idle(void)
{
	printk("default idle function\n");
}

static void arch_idle(void)
{
	if(s5pv2xx_idle != NULL)
		(s5pv2xx_idle)();
	else
		s5pv2xx_default_idle();
}

#include <mach/system-reset.h>
#endif /* __ASM_ARCH_IRQ_H */
