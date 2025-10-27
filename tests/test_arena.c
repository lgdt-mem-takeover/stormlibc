#include "../core/stormc_allocator.h"

typedef struct{
	f32 x,y;
}Vec2;

STORMC_SETUP_ARENA_TYPE(u8, u8)
STORMC_SETUP_ARENA_TYPE(f32, f32)
STORMC_SETUP_ARENA_TYPE(vec2, Vec2)



int main(void)
{
	StormC_Arena *a = stormc_arena_emit(512);
	StormC_Array_u8 arr = stormc_alloc_arena_u8(a, 15);
	if (arr.arr == NULL) {
		printf("failed allocation");
		exit(1);
	}

	StormC_Array_f32 arrf = stormc_alloc_arena_f32(a, 15);
	if (arrf.arr == NULL) {
		printf("failed allocation");
		exit(1);
	}
	StormC_Array_vec2 arrv2 = stormc_alloc_arena_vec2(a, 50);
	if (arrv2.arr == NULL) {
		printf("failed allocation");
		exit(1);
	}
	for (u32 idx = 0; idx < arr.len; idx++){
		arr.arr[idx] = 1 + idx*idx;
		printf("arr[idx] = %u\n", arr.arr[idx]);
	}

	for (u32 idx = 0; idx < arr.len; idx++){
		arrf.arr[idx] = 1 + (idx*idx) / 3.0f;
		printf("arr[idx] = %f\n", arrf.arr[idx]);
	}
	for (u32 idx = 0; idx < 64; idx++){
		arrv2.arr[idx].x = 1 + (idx*idx) / 3.0f;
		arrv2.arr[idx].y = 3.0f / (1 + (idx*idx));
		printf("arr[idx].x = %f\n", arrv2.arr[idx].x);
		printf("arr[idx].y = %f\n", arrv2.arr[idx].y);
	}
	return 0;
}
