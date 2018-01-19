/*
 * $QNXLicenseC:
 * Copyright 2008, QNX Software Systems. 
 * 
 * Licensed under the Apache License, Version 2.0 (the "License"). You 
 * may not reproduce, modify or distribute this software except in 
 * compliance with the License. You may obtain a copy of the License 
 * at: http://www.apache.org/licenses/LICENSE-2.0 
 * 
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" basis, 
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied.
 *
 * This file may contain contributions from others, either as 
 * contributors under the License or as licensors under other terms.  
 * Please review this entire file for other proprietary rights or license 
 * notices, as well as the QNX Development Suite License Guide at 
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */





#include <sys/f3s_mtd.h>

/*
 * Summary
 *
 * MTD Version: 2 only
 * Bus Width:   All
 *
 * Description
 *
 * This is the only MTDv2 unlockall callout for RAM / SRAM. It simulates
 * non-persistent locking for testing purposes.
 */

extern uint32_t *SRAM_LOCK;

int f3s_sram_v2unlockall(f3s_dbase_t *dbase,
                         f3s_access_t *access,
                         uint32_t flags,
                         uint32_t offset)
{
	uint32_t	usize = access->socket.unit_size ? access->socket.unit_size : 65536;

	/* See if we support locking at all */
	if (SRAM_LOCK == NULL) return (EOK);

	/* Clear the lock bits */
	memset (SRAM_LOCK, 0x00, ((access->socket.array_size / usize / 32) + 1) * sizeof(uint32_t));
	return (EOK);
}

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/hardware/flash/mtd-flash/sram/sram_v2unlockall.c $ $Rev: 680332 $")
#endif
