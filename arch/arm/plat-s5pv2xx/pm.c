/* linux/arch/arm/plat-s5pv2xx/pm.c
 *
 * Copyright (c) 2004,2009 Simtec Electronics
 *	boyko.lee <boyko.lee@samsung.com>
 *
 * S5PV2XX Power Manager (Suspend-To-RAM) support
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
 * Parts based on arch/arm/mach-pxa/pm.c
 *
 * Thanks to Dimitry Andric for debugging
*/

#include <linux/init.h>
#include <linux/suspend.h>
#include <linux/errno.h>
#include <linux/time.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/crc32.h>
#include <linux/ioport.h>
#include <linux/delay.h>
#include <linux/serial_core.h>
#include <linux/io.h>
#include <linux/platform_device.h>

#include <asm/cacheflush.h>
#include <mach/hardware.h>

#include <plat/map-base.h>
#include <plat/regs-serial.h>
#include <plat/regs-clock.h>
#include <plat/regs-gpio.h>
#include <plat/gpio-cfg.h>
#include <mach/regs-mem.h>
#include <mach/regs-irq.h>
#include <asm/gpio.h>

#include <asm/mach/time.h>

#include <plat/pm.h>

#define PFX "s5pv2xx-pm: "
static struct sleep_save core_save[] = {
/* Clock source */
	SAVE_ITEM(S5P_EPLL_CON),
#if defined(CONFIG_CPU_S5PV210_EVT1)
	SAVE_ITEM(S5P_EPLL_CON1),
#endif
	SAVE_ITEM(S5P_CLK_SRC0),
	SAVE_ITEM(S5P_CLK_SRC1),
	SAVE_ITEM(S5P_CLK_SRC2),
	SAVE_ITEM(S5P_CLK_SRC3),
	SAVE_ITEM(S5P_CLK_SRC4),
	SAVE_ITEM(S5P_CLK_SRC5),
	SAVE_ITEM(S5P_CLK_SRC6),
/* Clock source Mask */
	SAVE_ITEM(S5P_CLK_SRC_MASK0),
	SAVE_ITEM(S5P_CLK_SRC_MASK1),
/* Clock Divider */
	SAVE_ITEM(S5P_CLK_DIV0),
	SAVE_ITEM(S5P_CLK_DIV1),
	SAVE_ITEM(S5P_CLK_DIV2),
	SAVE_ITEM(S5P_CLK_DIV3),
	SAVE_ITEM(S5P_CLK_DIV4),
	SAVE_ITEM(S5P_CLK_DIV5),
	SAVE_ITEM(S5P_CLK_DIV6),
	SAVE_ITEM(S5P_CLK_DIV7),
/* Clock Main Main Gate */
	SAVE_ITEM(S5P_CLKGATE_MAIN0),
	SAVE_ITEM(S5P_CLKGATE_MAIN1),
	SAVE_ITEM(S5P_CLKGATE_MAIN2),
/* Clock source Peri Gate */
	SAVE_ITEM(S5P_CLKGATE_PERI0),
	SAVE_ITEM(S5P_CLKGATE_PERI1),
/* Clock source SCLK Gate */
	SAVE_ITEM(S5P_CLKGATE_SCLK0),
	SAVE_ITEM(S5P_CLKGATE_SCLK1),
/* Clock IP Clock gate */
	SAVE_ITEM(S5P_CLKGATE_IP0),
	SAVE_ITEM(S5P_CLKGATE_IP1),
	SAVE_ITEM(S5P_CLKGATE_IP2),
	SAVE_ITEM(S5P_CLKGATE_IP3),
	SAVE_ITEM(S5P_CLKGATE_IP4),
/* Clock Blcok and Bus gate */
	SAVE_ITEM(S5P_CLKGATE_BLOCK),
	SAVE_ITEM(S5P_CLKGATE_BUS0),
	SAVE_ITEM(S5P_CLKGATE_BUS1),	
/* Clock ETC */
	SAVE_ITEM(S5P_CLK_OUT),
	SAVE_ITEM(S5P_MDNIE_SEL),
};

static struct sleep_save sromc_save[] = {
	SAVE_ITEM(S5PV2XX_SROM_BW),
	SAVE_ITEM(S5PV2XX_SROM_BC0),
	SAVE_ITEM(S5PV2XX_SROM_BC1),
	SAVE_ITEM(S5PV2XX_SROM_BC2),
	SAVE_ITEM(S5PV2XX_SROM_BC3),
	SAVE_ITEM(S5PV2XX_SROM_BC4),
	SAVE_ITEM(S5PV2XX_SROM_BC5),
};

/* s3c_pm_check_resume_pin
 *
 * check to see if the pin is configured correctly for sleep mode, and
 * make any necessary adjustments if it is not
*/

static void s3c_pm_check_resume_pin(unsigned int pin, unsigned int irqoffs)
{
	
}

/* s3c_pm_configure_extint
 *
 * configure all external interrupt pins
*/

void s3c_pm_configure_extint(void)
{

	/* for each of the external interrupts (EINT0..EINT15) we
	 * need to check wether it is an external interrupt source,
	 * and then configure it as an input if it is not
	*/
	__raw_writel(s3c_irqwake_eintmask, S5P_EINT_WAKEUP_MASK);
}


void s3c_pm_restore_core(void)
{
	s3c_pm_do_restore_core(core_save, ARRAY_SIZE(core_save));
	s3c_pm_do_restore(sromc_save, ARRAY_SIZE(sromc_save));
}

void s3c_pm_save_core(void)
{
	s3c_pm_do_save(sromc_save, ARRAY_SIZE(sromc_save));
	s3c_pm_do_save(core_save, ARRAY_SIZE(core_save));
}


