/* linux/arch/arm/plat-s5pv2xx/include/plat/gpio-bank-a0.h
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * S5PV2XX GPIO BANK register
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#define S5PV2XX_GPA0CON			(S5PV2XX_GPA0_BASE + 0x00)
#define S5PV2XX_GPA0DAT			(S5PV2XX_GPA0_BASE + 0x04)
#define S5PV2XX_GPA0PUD			(S5PV2XX_GPA0_BASE + 0x08)
#define S5PV2XX_GPA0DRV			(S5PV2XX_GPA0_BASE + 0x0c)
#define S5PV2XX_GPA0CONPDN		(S5PV2XX_GPA0_BASE + 0x10)
#define S5PV2XX_GPA0PUDPDN		(S5PV2XX_GPA0_BASE + 0x14)

#define S5PV2XX_GPA0_CONMASK(__gpio)	(0xf << ((__gpio) * 4))
#define S5PV2XX_GPA0_INPUT(__gpio)	(0x0 << ((__gpio) * 4))
#define S5PV2XX_GPA0_OUTPUT(__gpio)	(0x1 << ((__gpio) * 4))

#define S5PV2XX_GPA0_0_UART_0_RXD	(0x2 << 0)
#define S5PV2XX_GPA0_0_GPIO_INT1_0	(0xf << 0)

#define S5PV2XX_GPA0_1_UART_0_TXD	(0x2 << 4)
#define S5PV2XX_GPA0_1_GPIO_INT1_1	(0xf << 4)

#define S5PV2XX_GPA0_2_UART_0_CTSn	(0x2 << 8)
#define S5PV2XX_GPA0_2_GPIO_INT1_2	(0xf << 8)

#define S5PV2XX_GPA0_3_UART_0_RTSn	(0x2 << 12)
#define S5PV2XX_GPA0_3_GPIO_INT1_3	(0xf << 12)

#define S5PV2XX_GPA0_4_UART_1_RXD	(0x2 << 16)
#define S5PV2XX_GPA0_4_GPIO_INT1_4	(0xf << 16)

#define S5PV2XX_GPA0_5_UART_1_TXD	(0x2 << 20)
#define S5PV2XX_GPA0_5_GPIO_INT1_5	(0xf << 20)

#define S5PV2XX_GPA0_6_UART_1_CTSn	(0x2 << 24)
#define S5PV2XX_GPA0_6_GPIO_INT1_6	(0xf << 24)

#define S5PV2XX_GPA0_7_UART_1_RTSn	(0x2 << 28)
#define S5PV2XX_GPA0_7_GPIO_INT1_7	(0xf << 28)

