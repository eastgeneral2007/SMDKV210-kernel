/* linux/arch/arm/mach-s5pv210/leds-s5pv210.c
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *              http://www.samsung.com/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/kernel_stat.h>
#include <linux/sched.h>
#include <linux/gpio.h>

#include <asm/io.h>
#include <asm/leds.h>
#include <asm/system.h>
#include <asm/mach-types.h>

#include <plat/regs-gpio.h>
#include <plat/gpio-cfg.h>
#include <plat/gpio-bank-h0.h>
#include <mach/map.h>

#include "leds.h"

#define LED0	S5PV2XX_GPH1(4)
#define LED1	S5PV2XX_GPH1(5)
#define LED2	S5PV2XX_GPH1(6)
#define LED3	S5PV2XX_GPH1(7)

#define LED_STATE_ENABLED	1<<0
#define LED_STATE_CLAIMED	1<<1
#define LED_TIMER_ON		1<<2
#define LED_IDLE		1<<3


void s5pv210_leds_event(led_event_t evt)
{
	unsigned long flags;

	static u16 led_state, hw_led_state;

	local_irq_save(flags);

	if (!(led_state & LED_STATE_ENABLED) && evt != led_start)
		goto done;

	switch (evt) {
	case led_start:
		led_state |= LED_STATE_ENABLED;
		break;

	case led_stop:
	case led_halted:
		/* all leds off during suspend or shutdown */
		led_state &= ~LED_STATE_ENABLED;
		break;

	case led_claim:
		led_state |= LED_STATE_CLAIMED;
		hw_led_state = 0;
		break;

	case led_release:
		led_state &= ~LED_STATE_CLAIMED;
		break;

#ifdef CONFIG_LEDS_TIMER
	case led_timer:
		led_state ^= LED_TIMER_ON;

		if (led_state & LED_TIMER_ON)
			gpio_set_value(LED0, 1);
		else {
			gpio_set_value(LED0, 0);
		}

		break;
#endif

#ifdef CONFIG_LEDS_CPU
	case led_idle_start:
		gpio_set_value(LED1, 1);
		break;

	case led_idle_end:
		gpio_set_value(LED1, 0);
		break;
#endif

	case led_green_on:
		break;
	case led_green_off:
		break;

	case led_amber_on:
		break;
	case led_amber_off:
		break;

	case led_red_on:
		break;
	case led_red_off:
		break;

	case led_blue_on:
		break;
	case led_blue_off:
		break;

	default:
		break;
	}

done:
	local_irq_restore(flags);
}
