/* linux/drivers/media/video/samsung/tv20/s5pc100/regs/regs-clock_extra.h
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *              http://www.samsung.com/
 *
 * S5PC100 - Clock Other header file for Samsung TVOut driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __ASM_ARCH_REGS_CLK_EXTRA_H
#define __ASM_ARCH_REGS_CLK_EXTRA_H

#include <mach/map.h>

#define S5P_CLK_OTHER_BASE(x) (x)
//////////////
// Registers     //
//////////////
#define	S5P_CLK_OTHER_SWRESET 			S5P_CLK_OTHER_BASE( 0x0000) 	//	Generate software reset 0x0000_0000
#define	S5P_CLK_OTHER_ONENAND_SWRESET 	S5P_CLK_OTHER_BASE( 0x0008) 	//	OneNAND controller setting 0x0000_0000
#define	S5P_CLK_OTHER_GENERAL_CTRL 		S5P_CLK_OTHER_BASE( 0x0100) 	//	General Control Register 0x0000_0000
#define	S5P_CLK_OTHER_GENERAL_STATUS 		S5P_CLK_OTHER_BASE( 0x0104) 	//	eneral Status Register 0x0000_0000
#define	S5P_CLK_OTHER_MEM_SYS_CFG 		S5P_CLK_OTHER_BASE( 0x0200) 	//	ENDIAN & EBI configuration 0x0000_0000
#define	S5P_CLK_OTHER_CAM_MUX_SEL 		S5P_CLK_OTHER_BASE( 0x0300) 	//	Camera mapping to FIMC selection 0x0000_0000
#define	S5P_CLK_OTHER_MIXER_OUT_SEL 		S5P_CLK_OTHER_BASE( 0x0304) 	//	Video Mixer output to TVENC / HDMI selection 0x0000_0000
#define	S5P_CLK_OTHER_LPMP3_MODE_SEL 	S5P_CLK_OTHER_BASE( 0x0308) //	Low power MP3 mode selection 0x0000_0000
#define	S5P_CLK_OTHER_MIPI_PHY_CON0 		S5P_CLK_OTHER_BASE( 0x0400) //	MIPI D-PHY control register0 0x0000_0000
#define	S5P_CLK_OTHER_MIPI_PHY_CON1 		S5P_CLK_OTHER_BASE( 0x0414) //	MIPI D-PHY control register1 0x0000_0000
#define	S5P_CLK_OTHER_HDMI_PHY_CON0 		S5P_CLK_OTHER_BASE( 0x0420) //	HDMI PHY control register0 0x0000_0000


/////////////////////////
// Macros				      //
/////////////////////////
// HPLL_LOCK
#define HPLL_LOCKTIME(a) (0xffff&a)

// HPLL_CON
#define HPLL_ENABLE     (1<<31)
#define HPLL_DISABLE    (0<<31)
#define HPLL_LOCKED(a)  ((1<<30)&a)
#define MDIV(a)         ((0xff&a)<<16)
#define PDIV(a)         ((0x3f&a)<<8)
#define SDIV(a)         (0x7&a)

// CLK_SRC0
#define HREF_SEL_FIN_27M    (0<<20)
#define HREF_SEL_SRCLK      (1<<20)
#define HREF_SEL_MASK       (~(1<<20))
#define HPLL_SEL_CLK27M     (0<<12)
#define HPLL_SEL_FOUT_HPLL  (1<<12)
#define HPLL_SEL_MASK       (~(1<<12))

// CLK_SRC2
#define VMIXER_SEL_CLK27M       (0<<28)
#define VMIXER_SEL_VCLK_54      (1<<28)
#define VMIXER_SEL_MOUT_HPLL    (2<<28)
#define VMIXER_SEL_MASK         (~(3<<28))

// CLK_DIV3
#define HDMI_DIV_RATIO(a)   ((0xf&((a)-1))<<28)
#define HDMI_DIV_RATIO_MASK (~(0xf<<28))

// CLK_GATE_D1_2
#define CLK_HCLK_HDMI_PASS      (1<<3)
#define CLK_HCLK_VMIXER_PASS    (1<<2)
#define CLK_HCLK_VP_PASS        (1<<1)
#define CLK_HCLK_SDOUT_PASS     (1<<0)
#define CLK_HCLK_MASK           (~0xf)

// CLK_GATE_D1_4
#define CLK_PCLK_IIC_HDMI_PASS  (1<<5)
#define CLK_PCLK_IIC_HDMI_MASK  (~(1<<5))

// CLK_GATE_SCLK_1
#define CLK_SCLK_HDMI_PASS      (1<<7)
#define CLK_SCLK_VMIXER_PASS    (1<<6)
#define CLK_SCLK_VDAC54_PASS    (1<<5)
#define CLK_SCLK_TV54_PASS      (1<<4)
#define CLK_SCLK_HDMI_MASK      (~(1<<7))
#define CLK_SCLK_VMIXER_MASK    (~(1<<6))
#define CLK_SCLK_VDAC54_MASK    (~(1<<5))
#define CLK_SCLK_TV54_MASK      (~(1<<4))

// MIXER_OUT_SEL
#define VMIXER_OUT_SEL_SDOUT    (0)
#define VMIXER_OUT_SEL_HDMI     (1)

#endif //__ASM_ARCH_REGS_CLK_EXTRA_H
