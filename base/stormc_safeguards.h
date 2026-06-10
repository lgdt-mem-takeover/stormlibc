#pragma once
#include "../stormc_header.h"

#define SAFE_INDEXING(arr_cap, index) SELECT(index >= arr_cap, arr_cap, index)



#define try(func_name, func_params, ...) \
	({\
		__auto_type __return__ = func_name func_params;\
		if(__return__ == (__typeof__(__return__))0){\
			__VA_ARGS__\
		}\
		__return__;\
	})


#define try_syscall(func_name, func_params, ...) \
	({\
		__auto_type __return__ = func_name func_params;\
		if ((__return__ < 0)){\
			__VA_ARGS__\
		}\
		__return__;\
	})


#define try_indexing(arr, arr_len, index, ...) \
	({\
		__auto_type __return__ = SAFE_INDEXING(arr_len, index);\
		__typeof__((arr)[0]) __value__ = {0};\
		if (__return__ == arr_len){\
			__VA_ARGS__\
		} else { \
			__value__ = arr[__return__];\
		}\
		__value__;\
	})
