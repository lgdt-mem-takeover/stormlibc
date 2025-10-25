#include "stormc_bitops.h"

#define SAFE_INDEXING(arr_len, index) SELECT(index > arr_len, arr_len, index)
