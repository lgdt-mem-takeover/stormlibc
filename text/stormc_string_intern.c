/*TODO: NEEDS REWRITE TO ACCOMODATE CHANGES TO OTHER PARTS OF THE LIBRARY*/
#pragma once
#include "../stormc_header.h"
#include "str-two-way.h"
#include <sys/uio.h>


#define SCRT_BASE(stack, x) \
  scrt_string_base(stack, x) \

#define SCRT_AS_CHAR(stack, x) \
  scrt_string_as_char(stack, x) \

#define SCRT_STRING(stack, x) \
  scrt_string(stack, x) \



#define SString_NULL (SString){.str = 0, .len = 0}
#define MATCH (1 << 2)
#define NOT_MATCH (1 << 3)

#define ALIGN_UP(size, alignment) (((size) + ((alignment) - 1)) & ~((alignment) - 1))


#define scrt_string_concat(pl, stack, ...)			\
	do{					\
		const char *arr[] = {__VA_ARGS__, NULL};\
		u64 len = 0;				\
		while(arr[++len]);			\
		(pl) = _scrt_string_concat(stack, arr, len);		\
	}while(0)

#define scrt_sstring_concat(stack, ...)			\
	do{					\
		const SString arr[] = {__VA_ARGS__, SString_NULL};\
		u64 len = 0;				\
		while(arr[++len].len);			\
		(pl) = _scrt_sstring_concat(stack, arr, len);		\
	}while(0)

typedef struct SFile SFile;
typedef struct SCRT_Strings SCRT_Strings;
typedef struct SString SString;
typedef u64 Eq_Payload;

struct SString {
	u32 str;
	u32 len;
};



static inline const char * scrt_string_as_char(struct stormc_stack *s, SString str)
{
  return (const char *)s->base + str.str;
}

static inline struct stormc_stack *scrt_init_strings(struct stormc_stack *s, u64 rsrv)
{
	s = STORMC_STACK_GEN(rsrv);
	return s;
}

static Eq_Payload is_eq_at(struct stormc_stack *s, const u8 *str, u32 len)
{
	Eq_Payload pl = NOT_MATCH;
	const u8 *found =
		(len < LONG_NEEDLE_THRESHOLD)
		? two_way_short_needle(s->base, s->base_offset, str, len)
		: two_way_long_needle(s->base, s->base_offset, str, len);

	if (found) {
		pl = ((found - s->base) << 8) | MATCH;
		return pl;
	}

	return (u64)((0 | NOT_MATCH));
}



static SString scrt_string(struct stormc_stack *s, const u8 *str)
{
	u32 len = 0;
	if(str[0] == '\0') return(SString){};
	while(str[++len]);


	SString pl = {};
	pl.str = s->base_offset;
	pl.len = len;

	char *current = (char*)STORMC_STACK_PUSH(s, char, len);


	u32 stride = 0;
	char ch = 0;
	Eq_Payload is_eq = is_eq_at(s, str, len);
	if(is_eq & MATCH){
		pl.str = is_eq >> 8;
		return pl;
	}

	u32 idx = 0;
	for(;idx < len; idx++)
	{
		current[idx] = str[idx];
	}
	current[idx] = '\0';

	return pl;
}

static SString _scrt_sstring_concat(struct stormc_stack *s, const SString arr[], u64 len)
{
	u64 buff_len = 0;
	u64 begin = 0;
	while(begin < len){
		buff_len += arr[begin].len;
		begin++;
	}
	STORMC_STACK_START(s);
	u8 *buff = (u8*)STORMC_STACK_PUSH(s, char, buff_len + 1);
	u64 buff_idx = 0;
	u64 idx = 0;
	u64 inner_idx;
	while(idx < len){
		u64 arr_len = arr[idx].len;
		const char *current = SCRT_AS_CHAR(s, arr[idx]);
		for (inner_idx = 0; inner_idx < arr_len; inner_idx++){
			buff[buff_idx++] = current[inner_idx];
		}
		idx++;
	}
	buff[buff_idx] = '\0';


	SString pl = scrt_string(s, buff);
	STORMC_STACK_END(s);
	return pl;

}


static SString _scrt_string_concat(struct stormc_stack *s, const char *arr[], u64 len)
{
	u64 lengths[len];
	u64 idx_lengths = 0;
	u64 buff_len = 0;
	while(idx_lengths < len){
		lengths[idx_lengths] = sstrlenx(arr[idx_lengths]);
		u64 cur = 0;
		buff_len += lengths[idx_lengths];
		idx_lengths++;
	}

	STORMC_STACK_START(s);
	u8 *buff = (u8*)STORMC_STACK_PUSH(s, char, buff_len + 1);
	u64 buff_idx = 0;
	u64 idx = 0;
	u64 inner_idx;
	while(arr[idx]){
		u64 arr_len = lengths[idx];
		for (inner_idx = 0; inner_idx < arr_len; inner_idx++){
			buff[buff_idx++] = arr[idx][inner_idx];
		}
		idx++;
	}
	buff[buff_idx] = '\0';


	SString pl = scrt_string(s, buff);
	STORMC_STACK_END(s);
	return pl;

}


static inline void scrt_print_string(struct stormc_stack *s, SString str)
{
	struct iovec str_vec[2];
	str_vec[0].iov_base = s->base + str.str;
	str_vec[0].iov_len = str.len;
	str_vec[1].iov_base = "\n";
	str_vec[1].iov_len = 1;

	writev(1, str_vec, 2);
}

static inline u8* scrt_string_base(struct stormc_stack *s, SString str)
{
  return s->base + str.str;
}



static inline bool scrt_strcmp(SString target, SString source)
{
  return target.str == source.str && target.len == source.len;
}

static SString scrt_file(struct stormc_stack *s, char *path)
{
	int fd = open(path, O_RDONLY);

	struct stat st;
	fstat(fd, &st);

	u8 *buf = (u8 *)mmap(NULL, st.st_size + 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	read(fd, buf, st.st_size);
	buf[st.st_size] = '\0';
	SString pl = SCRT_STRING(s, buf);

	close(fd);
	munmap(buf, st.st_size + 1);
	return pl;
}





