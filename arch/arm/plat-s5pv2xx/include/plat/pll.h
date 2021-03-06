/* linux/arch/arm/plat-s5pc1xx/include/plat/pll.h
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * S5PV2XX PLL register
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#define XTAL_FREQ	12000000

#define S5P_PLL_MDIV_MASK	((1 << (25-16+1)) - 1)
#define S5P_PLL_PDIV_MASK	((1 << (13-8+1)) - 1)
#define S5P_PLL_SDIV_MASK	((1 << (2-0+1)) - 1)
#define S5P_PLL_MDIV_SHIFT	(16)
#define S5P_PLL_PDIV_SHIFT	(8)
#define S5P_PLL_SDIV_SHIFT	(0)

#include <asm/div64.h>

#define APLL_VAL_1664	(1<<31)|(417<<16)|(3<<8)|(0)
#define APLL_VAL_1332	(1<<31)|(444<<16)|(4<<8)|(0)
#define APLL_VAL_1000	((1<<31)|(0xfa<<16)|(0x6<<8)|(0x1))
#define APLL_VAL_800	((1<<31)|(0xc8<<16)|(0x6<<8)|(0x1))

enum s5pv2xx_base_pll_t{
	S5PV2XX_PLL_APLL,
	S5PV2XX_PLL_MPLL,
	S5PV2XX_PLL_EPLL,
	S5PV2XX_PLL_VPLL,
};

static inline unsigned long s5pv2xx_get_pll(unsigned long baseclk,
					    u32 pllcon, enum s5pv2xx_base_pll_t base_pll_type)
{
	u32 mdiv, pdiv, sdiv;
	u64 fvco = baseclk;

	mdiv = (pllcon >> S5P_PLL_MDIV_SHIFT) & S5P_PLL_MDIV_MASK;
	pdiv = (pllcon >> S5P_PLL_PDIV_SHIFT) & S5P_PLL_PDIV_MASK;
	sdiv = (pllcon >> S5P_PLL_SDIV_SHIFT) & S5P_PLL_SDIV_MASK;

	fvco *= mdiv ;

	switch(base_pll_type){
	case S5PV2XX_PLL_APLL:
		do_div(fvco, (pdiv << (sdiv-1)));
		break;
		
	default:
		do_div(fvco, (pdiv << sdiv));
		break;
	}

	return (unsigned long)fvco;
	
}

