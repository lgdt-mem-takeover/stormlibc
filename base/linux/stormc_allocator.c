#pragma once

#include <unistd.h>
#include <sys/mman.h>


static void *stc_os_alloc_default(u64 size)
{
	return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1 , 0);

}

static void *stc_os_mem_rsrv(u64 size)
{
	return mmap(NULL, size, PROT_NONE, MAP_ANON | MAP_PRIVATE, -1 , 0);
}

static void *stc_os_mem_cmt(void* addrs, u64 size)
{
	size = STC_ALIGN_UP(size, PAGESIZE);
	int res = mprotect(addrs, size, PROT_READ | PROT_WRITE);
	if (unlikely(res != 0)) {
		stc_println("[{cstring}][{u32}]", __FUNCTION__, __LINE__);
		stc_println("{u64}", size);
		printf("mprotect code: %d\n", res);
		return NULL;
	}
	return addrs;

}

static enum stc_err_code stc_os_mem_free(void *mem, u64 size)
{
	if (unlikely(munmap(mem, size)) != 0) {
		return STC_ERR_OS_UNMAP_FAILED;
	}
	return STC_ERR_OK;
}
