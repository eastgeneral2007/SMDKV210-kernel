/* linux/drivers/media/video/samsung/tv20/ddc.h
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *              http://www.samsung.com/
 *
 * S5PV210 - ddc interface header for Samsung TVOut driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

extern int ddc_read(u8 subaddr, u8 *data, u16 len);
extern int ddc_write(u8 *data, u16 len);
