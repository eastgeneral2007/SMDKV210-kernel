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

static irqreturn_t
s3c_button_interrupt(int irq, void *dev_id)
{
	printk(" 11 Button Interrupt occure\n");
	
	return IRQ_HANDLED;
}

static irqreturn_t
s3c_31_button_interrupt(int irq, void *dev_id)
{
	printk(" 31 Button Interrupt occure\n");
	
	return IRQ_HANDLED;
}

static struct irqaction s3c_button_irq = {
	.name		= "s3c 11 button Tick",
	.flags		= IRQF_SHARED ,
	.handler	= s3c_button_interrupt,
};

static struct irqaction s3c_31_button_irq = {
	.name		= "s3c 31 button Tick",
	.flags		= IRQF_SHARED ,
	.handler	= s3c_31_button_interrupt,
};

static void s3c_button_gpio_init(void)
{
	u32 err;

	err = gpio_request(S5PC1XX_GPH1(3),"GPH1");
	if (err){
		printk("gpio request error : %d\n",err);
	}else{
		s3c_gpio_cfgpin(S5PC1XX_GPH1(3),S5PC1XX_GPH1_3_WAKEUP_INT_11);
		s3c_gpio_setpull(S5PC1XX_GPH1(3), S3C_GPIO_PULL_NONE);
	}

	err = gpio_request(S5PC1XX_GPH3(7),"GPH3");
	if (err){
		printk("gpio request error : %d\n",err);
	}else{
		s3c_gpio_cfgpin(S5PC1XX_GPH3(7),S5PC1XX_GPH3_7_WAKEUP_INT_31);
		s3c_gpio_setpull(S5PC1XX_GPH3(7), S3C_GPIO_PULL_NONE);
	}

}

static void __init s3c_button_init(void)
{
	
	printk("S5PC100 Button init function \n");
	
	s3c_button_gpio_init();
	
	set_irq_type(IRQ_EINT11, IRQF_TRIGGER_FALLING);
	setup_irq(IRQ_EINT11, &s3c_button_irq);

	set_irq_type(IRQ_EINT(31), IRQF_TRIGGER_FALLING);
	setup_irq(IRQ_EINT(31), &s3c_31_button_irq);
}

device_initcall(s3c_button_init);