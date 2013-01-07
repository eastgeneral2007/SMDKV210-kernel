/* arch/arm/mach-s5pc100/include/mach/idle.h
 *
 * Copyright (c) 2004 Simtec Electronics <linux@simtec.co.uk>
 *		http://www.simtec.co.uk/products/SWLINUX/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * S5PC100 CPU Idle controls
*/

#ifndef __ASM_ARCH_IDLE_H
#define __ASM_ARCH_IDLE_H __FILE__

/* This allows the over-ride of the default idle code, in case there
 * is any other things to be done over idle (like DVS)
*/

extern void (*s5pv2xx_idle)(void);

extern void s5pv2xx_default_idle(void);

#endif /* __ASM_ARCH_IDLE_H */
