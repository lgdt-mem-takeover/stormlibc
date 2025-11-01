#include "stormc_types.h"


static inline void stormc_memcpy(void *dst, void *src, u64 size)
{
	u64 idx;
	u64 batch_size = size / 32;
	u64 remainder = size % 32;
	for (idx = 0; idx < batch_size; idx += 32){
		simd_32_u8 load_src = _mm256_loadu_si256((const simd_32_u8*)((u8*)src + idx));
		_mm256_storeu_si256(((__m256i_u*)dst + idx), load_src);
	}


	if (remainder > 0){
		for (; idx < size; idx++){
			((u8*)dst)[idx] = ((u8*)src)[idx];
		}
	}
}
