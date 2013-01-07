/*
 * arch/arm/mach-s5pv210/cpuidle.c
 *
 * CPU idle driver for S5PV210
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 * S5PV210 has several power mode to reduce power consumption.
 * CPU idle driver supports two power mode.
 * #1 Idle mode : WFI(ARM core clock-gating)
 * #2 Deep idle mode : WFI(ARM core power-gating, SDRAM self-refresh)
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/cpuidle.h>
#include <linux/io.h>
#include <asm/proc-fns.h>

#define S5PV210_MAX_STATES	2

static struct cpuidle_driver s5pv210_idle_driver = {
	.name =         "s5pv210_idle",
	.owner =        THIS_MODULE,
};

static DEFINE_PER_CPU(struct cpuidle_device, s5pv210_cpuidle_device);

/* Actual code that puts the SoC in different idle states */
static int s5pv210_enter_idle(struct cpuidle_device *dev,
			       struct cpuidle_state *state)
{
	struct timeval before, after;
	int idle_time;

	local_irq_disable();
	do_gettimeofday(&before);
	if (state == &dev->states[0]) {
		/* Wait for interrupt state */
		printk(KERN_INFO "Normal idle\n");
		cpu_do_idle();
	} else if (state == &dev->states[1]) {
		printk(KERN_INFO "Deep idle\n");
		cpu_do_idle();
	}
	do_gettimeofday(&after);
	local_irq_enable();
	idle_time = (after.tv_sec - before.tv_sec) * USEC_PER_SEC +
			(after.tv_usec - before.tv_usec);
	return idle_time;
}

/* Initialize CPU idle by registering the idle states */
static int s5pv210_init_cpuidle(void)
{
	struct cpuidle_device *device;

	cpuidle_register_driver(&s5pv210_idle_driver);

	device = &per_cpu(s5pv210_cpuidle_device, smp_processor_id());
	device->state_count = S5PV210_MAX_STATES;

	/* Wait for interrupt state */
	device->states[0].enter = s5pv210_enter_idle;
	device->states[0].exit_latency = 1;
	device->states[0].target_residency = 10000;
	device->states[0].flags = CPUIDLE_FLAG_TIME_VALID;
	strcpy(device->states[0].name, "IDLE");
	strcpy(device->states[0].desc, "ARM clock gating - WFI");

	/* Wait for interrupt and DDR self refresh state */
	device->states[1].enter = s5pv210_enter_idle;
	device->states[1].exit_latency = 10;
	device->states[1].target_residency = 10000;
	device->states[1].flags = CPUIDLE_FLAG_TIME_VALID;
	strcpy(device->states[1].name, "DEEP IDLE");
	strcpy(device->states[1].desc, "ARM power gating and memory self refresh - WFI");

	if (cpuidle_register_device(device)) {
		printk(KERN_ERR "s5pv210_init_cpuidle: Failed registering\n");
		return -EIO;
	}
	return 0;
}

device_initcall(s5pv210_init_cpuidle);
