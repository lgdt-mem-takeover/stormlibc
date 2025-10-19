#pragma once
#include "storm.h"


static void* stormc_alloc(size_t size)
{
#ifdef _WIN32
  return VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#else
  return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1 , 0);
#endif
}

static void stormc_free(void *ptr, size_t size)
{
#ifdef _WIN32
    (void)size;               // size ignored on Windows
    VirtualFree(ptr, 0, MEM_RELEASE);
#else
    munmap(ptr, size);
#endif
}

