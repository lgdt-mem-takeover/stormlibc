#pragma once

#include "../../stormc_header.h"
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>


void *stc_os_alloc_default(u64 size)
{
	return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1 , 0);

}

void *stc_os_mem_rsrv(u64 size)
{
	return mmap(NULL, size, PROT_NONE, MAP_ANON | MAP_PRIVATE, -1 , 0);
}

void *stc_os_mem_cmt(void* addrs, u64 size)
{
	size = STC_ALIGN_UP(size, PAGESIZE);
	int res = mprotect(addrs, size, PROT_READ | PROT_WRITE);
	if (unlikely(res != 0)) {
		stc_byte buff[64];
		u64 len = stc_itoa(res, buff);
		// stc_write(2, "mprotect failed with code ", sizeof("mprotect failed with code") - 1);
		// stc_write(2, buff, len);
		// stc_write(2, "\n", 1);
		printf("mprotect code: %d\n", res);
		return NULL;
	}
	return addrs;

}

