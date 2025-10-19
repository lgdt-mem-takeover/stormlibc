#pragma once
#ifndef _GNU_SOURCE
	#define _GNU_SOURCE
#endif

#include <fcntl.h>
#include <sys/stat.h>
#include <stdalign.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <immintrin.h>
#include <sys/mman.h>

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


#define thisfile static
#define local_persist static
#define global_persist static

#include "storm_types.h"
#include "stormc_dice.h"
#include "stormc_random.h"
#include "storm_stringlib.c"
#include "storm_stdio.c"
#include "stormc_runtime.c"
#include "stormc_allocator.c"
#include "stormc_hashmap.h"
