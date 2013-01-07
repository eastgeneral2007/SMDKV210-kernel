/*
 * linux/sound/soc/s3c/smdks5p_hdmi_spdif.c
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *          http://www.samsung.com/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * - Declaration of common structures and extern variables
 *   for SPDIF transmitter driver
 */

#ifndef __S5P_SPDIF_H
#define __S5P_SPDIF_H __FILE__

#include <linux/clk.h>

struct s5p_spdif_info {
	void __iomem	*regs;
	struct clk	*spdif_clk;
	struct clk	*spdif_sclk;
	int 		master;
};

extern struct s5p_spdif_info s5p_spdif;
extern struct snd_soc_dai s5p_spdif_dai;
#endif /* __S5P_SPDIF_H */
