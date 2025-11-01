#include "../core/stormc_types.h"
#include "../core/stormc_allocator.h"
#include "../core/stormc_mem.h"

typedef struct StormC_Array_Header StormC_Array_Header;
typedef struct StormC_Array StormC_Array;
typedef struct StormC_Slice StormC_Slice;
#define GET_ARRAY_HEADER(ptr) \
	(StormC_Array_Header*)((u8*)((ptr)) - sizeof(StormC_Array_Header))

#define MAKE_ARRAY(type, element_count) \
	stormc_array_make(sizeof(type), ALIGNOF(type), element_count)

#define SLICE(arr, start, end)\
	stormc_array_slice(arr, start, end)

struct StormC_Slice{
	void *slice;
	u32  len;
};

struct StormC_Array_Header{
	u32	cap;
	u32	len;
	u32	cur_idx;
	u32	alignment;
	u32	element_size;
	u32	resize_factor;
};




static void *stormc_array_make(u32 size, u32 alignment, u32 element_count)
{
	StormC_Array_Header *pl;
	size_t size_array_hdr = sizeof(*pl);
	size = STORMC_ALIGN_UP(size, alignment);
	u8 *block = (u8*)stormc_alloc((size * element_count) + size_array_hdr);
	pl = (StormC_Array_Header*)block;
	pl->alignment = alignment;
	pl->cap = element_count;
	pl->len = 0;
	pl->resize_factor = 2;
	pl->element_size = size;
	pl++;


	return (void*)pl;
}


static void *stormc_array_append(void *arr, void *value)
{
	StormC_Array_Header *header = GET_ARRAY_HEADER(arr);
	if (header->len >= header->cap) {
		u32 new_size = sizeof(*header) + header->cap * header->resize_factor;
		stormc_resize(header, new_size);
		header->cap = new_size;
	}

	u32 align = header->alignment;
	stormc_memcpy((u8*)arr + header->len * header->element_size, value, header->element_size);
	header->len++;

	return arr;
}

static StormC_Slice stormc_array_slice(void *arr, u32 slice_start, u32 slice_end)
{
	StormC_Array_Header *header = GET_ARRAY_HEADER(arr);
	StormC_Slice slice;
	slice.slice = (StormC_Slice*)((u8*)arr + slice_start * header->element_size);
	slice.len = slice_end - slice_start;
	return slice;
}


static inline u32 stormc_array_len(void *arr)
{
	StormC_Array_Header *header = GET_ARRAY_HEADER(arr);

	return header->len;

}

static inline u32 stormc_array_capacity(void *arr)
{
	StormC_Array_Header *header = GET_ARRAY_HEADER(arr);

	return header->cap;

}
