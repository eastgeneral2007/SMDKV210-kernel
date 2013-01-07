/* linux/drivers/media/video/samsung/tv20/hpd.h
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *              http://www.samsung.com/
 *
 * S5PV210 - hpd interface header file for Samsung TVOut driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define VERSION         "1.2" /* Driver version number */
#define HPD_MINOR       243 /* Major 10, Minor 243, /dev/hpd */

#define HPD_LO          0
#define HPD_HI          1

struct hpd_struct {
	spinlock_t lock;
	wait_queue_head_t waitq;
	atomic_t state;
};

