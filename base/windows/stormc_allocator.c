#pragma once

#include "../../stormc_header.h"

static void *stc_os_alloc_default(u64 size)
{
	return VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
}

void *stc_os_mem_rsrv(u64 size)
{
	return VirtualAlloc(NULL, size, MEM_RESERVE, PAGE_NOACCESS);
}

void *stc_os_mem_cmt(void* addrs, u64 size)
{
	return VirtualAlloc(addrs, size, MEM_COMMIT, PAGE_READWRITE);
}

enum stc_err_code stc_os_mem_free(void *mem, UNUSED u64 size)
{
	return VirtualFree(mem, 0, MEM_RELEASE) ? STC_ERR_OK : STC_ERR_OS_FREE_FAILED;
}
