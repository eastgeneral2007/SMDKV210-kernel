/* linux/arch/arm/plat-s5pv2xx/irq-om.c
 *
 * Copyright (c) 2003,2004 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *	http://armlinux.simtec.co.uk/
 *
 * S3C24XX - IRQ PM code
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/sysdev.h>

#include <plat/cpu.h>
#include <plat/pm.h>
#include <plat/irqs.h>
#include <plat/regs-gpio.h>

#include <mach/regs-irq.h>
/* state for IRQs over sleep */

/* default is to allow for EINT0..EINT31, and IRQ_RTC_TIC, IRQ_RTC_ALARM, 
 * as wakeup sources
 *
 * set bit to 1 in allow bitfield to enable the wakeup settings on it
*/

unsigned long s3c_irqwake_intallow	= 0x00000006L;
unsigned long s3c_irqwake_eintallow	= 0xffffffffL;

int s3c_irq_wake(unsigned int irqno, unsigned int state)
{
	unsigned long irqbit;

	switch (irqno) {
	case IRQ_RTC_TIC:
	case IRQ_RTC_ALARM:
		irqbit = 1 << (irqno + 1 - IRQ_RTC_ALARM);
		if (!state)
			s3c_irqwake_intmask |= irqbit;
		else
			s3c_irqwake_intmask &= ~irqbit;
		break;
	default:
		return -ENOENT;
	}
	return 0;
}

/* this lot should be really saved by the IRQ code */
/* VICXADDRESSXX initilaization to be needed */
static struct sleep_save irq_save[] = {
	SAVE_ITEM(S5PV210_VIC0REG(VIC_INT_SELECT)),
	SAVE_ITEM(S5PV210_VIC1REG(VIC_INT_SELECT)),
	SAVE_ITEM(S5PV210_VIC2REG(VIC_INT_SELECT)),
	SAVE_ITEM(S5PV210_VIC3REG(VIC_INT_SELECT)),
	SAVE_ITEM(S5PV210_VIC0REG(VIC_INT_ENABLE)),
	SAVE_ITEM(S5PV210_VIC1REG(VIC_INT_ENABLE)),
	SAVE_ITEM(S5PV210_VIC2REG(VIC_INT_ENABLE)),
	SAVE_ITEM(S5PV210_VIC3REG(VIC_INT_ENABLE)),
	SAVE_ITEM(S5PV210_VIC0REG(VIC_INT_SOFT)),
	SAVE_ITEM(S5PV210_VIC1REG(VIC_INT_SOFT)),
	SAVE_ITEM(S5PV210_VIC2REG(VIC_INT_SOFT)),
	SAVE_ITEM(S5PV210_VIC3REG(VIC_INT_SOFT)),
};

static struct sleep_save eint_save[] = {
	SAVE_ITEM(S5PV2XX_EINT30CON),
	SAVE_ITEM(S5PV2XX_EINT31CON),
	SAVE_ITEM(S5PV2XX_EINT32CON),
	SAVE_ITEM(S5PV2XX_EINT33CON),
	SAVE_ITEM(S5PV2XX_EINT30FLTCON0),
	SAVE_ITEM(S5PV2XX_EINT30FLTCON1),
	SAVE_ITEM(S5PV2XX_EINT31FLTCON0),
	SAVE_ITEM(S5PV2XX_EINT31FLTCON1),
	SAVE_ITEM(S5PV2XX_EINT32FLTCON0),
	SAVE_ITEM(S5PV2XX_EINT32FLTCON1),
	SAVE_ITEM(S5PV2XX_EINT33FLTCON0),
	SAVE_ITEM(S5PV2XX_EINT33FLTCON1),
	SAVE_ITEM(S5PV2XX_EINT30MASK),
	SAVE_ITEM(S5PV2XX_EINT31MASK),
	SAVE_ITEM(S5PV2XX_EINT32MASK),
	SAVE_ITEM(S5PV2XX_EINT33MASK),
};

int s5pv2xx_irq_suspend(struct sys_device *dev, pm_message_t state)
{
	s3c_pm_do_save(eint_save, ARRAY_SIZE(eint_save));
	s3c_pm_do_save(irq_save, ARRAY_SIZE(irq_save));
	return 0;
}

int s5pv2xx_irq_resume(struct sys_device *dev)
{
	s3c_pm_do_restore(irq_save, ARRAY_SIZE(irq_save));
	s3c_pm_do_restore(eint_save, ARRAY_SIZE(eint_save));
	return 0;
}
