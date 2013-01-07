/* linux/arch/arm/plat-s3c/include/plat/ide.h
 *
 * Copyright (C) 2009 Samsung Electronics
 * 	http://samsungsemi.com
 *
 * S3C IDE Platform data definitions
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __PLAT_S3C_IDE_H
#define __PLAT_S3C_IDE_H __FILE__

/**
 * struct s3c_ide_platdata - S3C IDE driver platform data.
 * @setup_gpio: Platform specific ide gpio setup function.
 *
 */
struct s3c_ide_platdata {
	void 	(*setup_gpio)(void);
};

/*
 * s3c_ide_set_platdata() - Setup the platform specifc data for IDE driver.
 * @pdata: Platform data for IDE driver.
 */
extern void s3c_ide_set_platdata(struct s3c_ide_platdata *pdata);

/*
 * s3c64xx_ide_setup_gpio() - Platform specific ide gpio setup function.
 */
extern void s5pv2xx_ide_setup_gpio(void);

#endif
