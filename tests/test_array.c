#include "../core/stormc_types.h"
#include "stormc_array.h"


typedef struct{
	f32 x, y;
}T;

int main(void)
{
	T *arr = MAKE_ARRAY(T, 1);
	for (u64 idx = 0; idx < 3; idx++){
		T value = {.x = 0, .y = 69.0f * idx};
		arr = stormc_array_append(arr, &value);
		printf("arr value [%f]\n", arr[idx].y);
	}

	StormC_Slice slice_u8 = SLICE(arr, 1, 3);

	for (u32 idx = 0; idx < slice_u8.len; idx++){
		printf("slice value [%f]\n", ((T*)slice_u8.slice)[idx].y);
	}
}
