/* linux/arch/arm/mach-s5pv210/irq.c
 *
 * Based on arch/arm/mach-s3c2410/irq.c
 * Modified by Jaechoel Lee <jc.lee@samsung.com>
 *
 * Copyright (c) 2006 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
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
 *
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/sysdev.h>

#include <plat/cpu.h>
#include <plat/pm.h>

static int s5pv210_irq_add(struct sys_device *sysdev)
{
	return 0;
}

static struct sysdev_driver s5pv210_irq_driver = {
	.add		= s5pv210_irq_add,
	.suspend	= s5pv2xx_irq_suspend,
	.resume		= s5pv2xx_irq_resume,
};

static int s5pv210_irq_init(void)
{
	return sysdev_driver_register(&s5pv210_sysclass, &s5pv210_irq_driver);
}

arch_initcall(s5pv210_irq_init);
