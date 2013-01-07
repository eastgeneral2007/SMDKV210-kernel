/* linux/drivers/media/video/samsung/tv20/s5pv210/cec_s5pv210.h
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *              http://www.samsung.com/
 *
 * S5PV210 - cec ftn header for Samsung TVOut driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _LINUX_CEC_H_
#define _LINUX_CEC_H_

#define CEC_IOC_MAGIC        'c'

/**
 * CEC device request code to set logical address.
 */
#define CEC_IOC_SETLADDR     _IOW(CEC_IOC_MAGIC, 0, unsigned int)

#endif /* _LINUX_CEC_H_ */
