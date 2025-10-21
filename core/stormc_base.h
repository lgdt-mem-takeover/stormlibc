#pragma once
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <immintrin.h>
#include <stdint.h>
#include <sys/mman.h>
#include <string.h>
#include <stdio.h>

#define thisfile static
#define global_persist static
#define local_persist static
#define at_least static

#ifndef restrict
# if defined(__GNUC__) || defined(__clang__)
#  define restrict __restrict
# else
#  define restrict
# endif
#endif


#ifndef inline
# if defined(__GNUC__) || defined(__clang__)
#  define inline __inline__
# elif defined(_MSC_VER)
#  define inline __inline
# else
#  define inline
# endif
#endif

#define OFFSETOF(type, member) \
  __builtin_offsetof(type, member) \

#define unreachable __builtin_unreachable()

#define KILOBYTE(x) ((x) * 1024ull)
#define MEGABYTE(x) ((x) * 1024ull * 1024ull)
#define CACHELINE_SIZE 64


#define thisfile static
#define local_persist static
#define at_least static



#define true 1
#define false 0
