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
	u8 *arr = stormc_alloc_arena_u8(a, 15);
	if (arr == NULL) {
		printf("returned nullptr\n");
		return 1;
	}
	f32 *arrf = stormc_alloc_arena_f32(a, 15);
	if (arrf == NULL) {
		printf("returned nullptr\n");
		return 1;
	}
	Vec2 *arrv2 = stormc_alloc_arena_vec2(a, 50);
	if (arrv2 == NULL) {
		printf("returned nullptr\n");
		return 1;
	}
	for (u32 idx = 0; idx < 64; idx++){
		arr[idx] = 1 + idx*idx;
		printf("arr[idx] = %u\n", arr[idx]);
	}

	for (u32 idx = 0; idx < 64; idx++){
		arrf[idx] = 1 + (idx*idx) / 3.0f;
		printf("arr[idx] = %f\n", arrf[idx]);
	}
	for (u32 idx = 0; idx < 64; idx++){
		arrv2[idx].x = 1 + (idx*idx) / 3.0f;
		arrv2[idx].y = 3.0f / (1 + (idx*idx));
		printf("arr[idx].x = %f\n", arrv2[idx].x);
		printf("arr[idx].y = %f\n", arrv2[idx].y);
	}
	return 0;
}
