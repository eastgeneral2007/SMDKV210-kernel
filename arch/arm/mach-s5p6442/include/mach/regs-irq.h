/* linux/arch/arm/mach-s5p6442/include/mach/regs-irq.h
 *
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S5P64XX - IRQ register definitions
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __ASM_ARCH_REGS_IRQ_H
#define __ASM_ARCH_REGS_IRQ_H __FILE__

#include <asm/hardware/vic.h>
#include <mach/map.h>
/* interrupt controller */
#define S3C_VIC0REG(x)          ((x) + S3C_VA_VIC0)
#define S3C_VIC1REG(x)          ((x) + S3C_VA_VIC1)
#define S3C_VIC2REG(x)          ((x) + S3C_VA_VIC2)

#define S5P64XX_VIC0IRQSTATUS       S3C_VIC0REG(0x000)
#define S5P64XX_VIC1IRQSTATUS       S3C_VIC1REG(0x000)

#define S5P64XX_VIC0FIQSTATUS       S3C_VIC0REG(0x004)
#define S5P64XX_VIC1FIQSTATUS       S3C_VIC1REG(0x004)

#define S5P64XX_VIC0RAWINTR         S3C_VIC0REG(0x008)
#define S5P64XX_VIC1RAWINTR         S3C_VIC1REG(0x008)

#define S5P64XX_VIC0INTSELECT       S3C_VIC0REG(0x00C)
#define S5P64XX_VIC1INTSELECT       S3C_VIC1REG(0x00C)

#define S5P64XX_VIC0INTENABLE       S3C_VIC0REG(0x010)
#define S5P64XX_VIC1INTENABLE       S3C_VIC1REG(0x010)

#define S5P64XX_VIC0INTENCLEAR      S3C_VIC0REG(0x014)
#define S5P64XX_VIC1INTENCLEAR      S3C_VIC1REG(0x014)

#define S5P64XX_VIC0SOFTINT         S3C_VIC0REG(0x018)
#define S5P64XX_VIC1SOFTINT         S3C_VIC1REG(0x018)

#define S5P64XX_VIC0SOFTINTCLEAR    S3C_VIC0REG(0x01C)
#define S5P64XX_VIC1SOFTINTCLEAR    S3C_VIC1REG(0x01C)

#define S5P64XX_VIC0PROTECTION      S3C_VIC0REG(0x020)
#define S5P64XX_VIC1PROTECTION      S3C_VIC1REG(0x020)

#define S5P64XX_VIC0SWPRIORITYMASK  S3C_VIC0REG(0x024)
#define S5P64XX_VIC1SWPRIORITYMASK  S3C_VIC1REG(0x024)

#define S5P64XX_VIC0PRIORITYDAISY   S3C_VIC0REG(0x028)
#define S5P64XX_VIC1PRIORITYDAISY   S3C_VIC1REG(0x028)

#define S5P64XX_VIC0VECTADDR0       S3C_VIC0REG(0x100)
#define S5P64XX_VIC1VECTADDR0       S3C_VIC1REG(0x100)

#define S5P64XX_VIC0VECTADDR1       S3C_VIC0REG(0x104)
#define S5P64XX_VIC1VECTADDR1       S3C_VIC1REG(0x104)

#define S5P64XX_VIC0VECTADDR2       S3C_VIC0REG(0x108)
#define S5P64XX_VIC1VECTADDR2       S3C_VIC1REG(0x108)

#define S5P64XX_VIC0ADDRESS         S3C_VIC0REG(0xF00)
#define S5P64XX_VIC1ADDRESS         S3C_VIC1REG(0xF00)



/* GPIO is 0x7F008xxx, */
#define S5P64XX_GPIOREG(x)	(S5P64XX_VA_GPIO + (x))

#define S5P64XX_EINT0CON			S5P64XX_GPIOREG(0xE00)		/* EINT0  ~ EINT7  */
#define S5P64XX_EINT1CON			S5P64XX_GPIOREG(0xE04)		/* EINT8  ~ EINT15 */
#define S5P64XX_EINT2CON			S5P64XX_GPIOREG(0xE08)		/* EINT16 ~ EINT23 */
#define S5P64XX_EINT3CON			S5P64XX_GPIOREG(0xE0C)		/* EINT24 ~ EINT31 */
#define S5P64XX_EINTCON(x)			(S5P64XX_EINT0CON+((x)*0x4))	/* EINT0  ~ EINT31  */

#define S5P64XX_EINT0FLTCON0			S5P64XX_GPIOREG(0xE80)		/* EINT0  ~ EINT3  */
#define S5P64XX_EINT0FLTCON1			S5P64XX_GPIOREG(0xE84)
#define S5P64XX_EINT1FLTCON0			S5P64XX_GPIOREG(0xE88)		/* EINT8 ~  EINT11 */
#define S5P64XX_EINT1FLTCON1			S5P64XX_GPIOREG(0xE8C)
#define S5P64XX_EINT2FLTCON0			S5P64XX_GPIOREG(0xE90)
#define S5P64XX_EINT2FLTCON1			S5P64XX_GPIOREG(0xE94)
#define S5P64XX_EINT3FLTCON0			S5P64XX_GPIOREG(0xE98)
#define S5P64XX_EINT3FLTCON1			S5P64XX_GPIOREG(0xE9C)
#define S5P64XX_EINTFLTCON(x)			(S5P64XX_EINT0FLTCON0+((x)*0x4))	/* EINT0  ~ EINT31 */

#define S5P64XX_EINT0MASK			S5P64XX_GPIOREG(0xF00)		/* EINT0 ~  EINT7  */
#define S5P64XX_EINT1MASK			S5P64XX_GPIOREG(0xF04)		/* EINT8 ~  EINT15 */
#define S5P64XX_EINT2MASK			S5P64XX_GPIOREG(0xF08)		/* EINT16 ~ EINT23 */
#define S5P64XX_EINT3MASK			S5P64XX_GPIOREG(0xF0C)		/* EINT24 ~ EINT31 */
#define S5P64XX_EINTMASK(x)			(S5P64XX_EINT0MASK+((x)*0x4))	/* EINT0 ~  EINT31  */

#define S5P64XX_EINT0PEND			S5P64XX_GPIOREG(0xF40)		/* EINT0 ~  EINT7  */
#define S5P64XX_EINT1PEND			S5P64XX_GPIOREG(0xF44)		/* EINT8 ~  EINT15 */
#define S5P64XX_EINT2PEND			S5P64XX_GPIOREG(0xF48)		/* EINT16 ~ EINT23 */
#define S5P64XX_EINT3PEND			S5P64XX_GPIOREG(0xF4C)		/* EINT24 ~ EINT31 */
#define S5P64XX_EINTPEND(x)			(S5P64XX_EINT0PEND+((x)*0x4))	/* EINT0 ~  EINT31  */

#define eint_offset(irq)			((irq) < IRQ_EINT16_31 ? ((irq)-IRQ_EINT0) :  \
						(irq-S3C_IRQ_EINT_BASE))
					
#define eint_irq_to_bit(irq)			(1 << (eint_offset(irq) & 0x7))

#define eint_conf_reg(irq)			((eint_offset(irq)) >> 3)
#define eint_filt_reg(irq)			((eint_offset(irq)) >> 2)
#define eint_mask_reg(irq)			((eint_offset(irq)) >> 3)
#define eint_pend_reg(irq)			((eint_offset(irq)) >> 3)

#endif /* __ASM_ARCH_6400_REGS_IRQ_H */
