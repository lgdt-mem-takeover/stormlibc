#include <stddef.h>
#define STORMC_ALLOCATOR

#include "../stormc_header.h"

#define new_array_t(__name) array_##__name
#define T(__name) new_array_t(__name)

#define STC_MAKE_ARRAY(__type)\
	array_t(__type)\
	typedef struct array_##__type{\
		__type		*ptr;\
		u64		len;\
		u64		mem_cmt;\
		u64		mem_rsrv;\
	}array_##__name;\
	\
	static array_##__name array_init_##__name(u64 max_capacity)\
	{\
		\
	}\


#define LOOP_ARR(arr, last_pos, capture_value, idx, ...) \
	do{\
		u64 idx = 0;\
		__typeof__(*arr.ptr) *capture_value = arr.ptr;\
		__typeof__(*arr.ptr) *end_arr = arr.ptr + last_pos;\
		while (capture_value != end_arr) {\
			idx = capture_value - arr.ptr;\
			__VA_ARGS__;\
			++capture_value;\
		}\
	}while(0);
