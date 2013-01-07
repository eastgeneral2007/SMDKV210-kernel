/* linux/arch/arm/plat-s5pv2xx/include/plat/media.h
 *
 * Copyright 2009 Samsung Electronics
 *	Jinsung Yang <jsgood.yang@samsung.com>
 *	Jonghun Han <jonghun.han@samsung.com>
 *	http://samsungsemi.com/
 *
 * Samsung Media device descriptions
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef _S3C_MEDIA_H
#define _S3C_MEDIA_H

#include <linux/types.h>
#include <asm/setup.h>

/* 3 fimc indexes should be fixed as n, n+1 and n+2 */
#define S3C_MDEV_JPEG		0
#define S3C_MDEV_MFC		1
#define S3C_MDEV_FIMC0		2
#define S3C_MDEV_FIMC1		3
#define S3C_MDEV_FIMC2		4
#define S3C_MDEV_CMM		5
#define S3C_MDEV_PMEM		6

struct s3c_media_device {
	u32		id;
	const char 	*name;
	u32		bank;
	size_t		memsize;
	dma_addr_t	paddr;
};

extern struct membank s3c_meminfo[];

extern dma_addr_t s3c_get_media_memory_bank(int dev_id, int bank);
extern size_t s3c_get_media_memsize_bank(int dev_id, int bank);

#endif

