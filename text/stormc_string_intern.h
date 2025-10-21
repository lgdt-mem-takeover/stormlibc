#pragma once
#include "../core/stormc_base.h"
#include "../glibc_parts/str-two-way.h"


#define OOM (1U << 27)
#define SCRT_Size_Strings (1U << 26)

#define SCRT_BASE(x) \
  scrt_string_base(x) \

#define SCRT_AS_CHAR(x) \
  scrt_string_as_char(x) \

#define SCRT_STRING(x) \
  scrt_string(x) \



#define SString_NULL (SString){.str = 0, .len = 0}
#define MATCH (1 << 2)
#define NOT_MATCH (1 << 3)

#define ALIGN_UP(size, alignment) (((size) + ((alignment) - 1)) & ~((alignment) - 1))


#define scrt_string_concat(pl, ...)			\
	do{					\
		const char *arr[] = {__VA_ARGS__, NULL};\
		u64 len = 0;				\
		while(arr[++len]);			\
		(pl) = _scrt_string_concat(arr, len);		\
	}while(0)

#define scrt_sstring_concat(pl, ...)			\
	do{					\
		const SString arr[] = {__VA_ARGS__, SString_NULL};\
		u64 len = 0;				\
		while(arr[++len].len);			\
		(pl) = _scrt_sstring_concat(arr, len);		\
	}while(0)

typedef struct SFile SFile;
typedef struct SCRT_Strings SCRT_Strings;
typedef struct SString SString;
typedef u64 Eq_Payload;



static inline void scrt_memcpy(void * restrict dest, const void * restrict source, u64 len)
{
  u64 idx = 0;
  u8 *ptr_src = (u8*)source;
  u8 *ptr_dest = (u8*)dest;
  while(idx < len)
  {
    ptr_dest[idx] = ptr_src[idx];
    idx++;
  }
}

struct SString
{
  u32 str;
  u32 len;
};


struct SCRT_Strings
{
  u32   cap;
  u32   off;
  u8    *pool;
};

SCRT_Strings *scrt_strings;


static inline const char * scrt_string_as_char(SString str)
{
  return (const char *)scrt_strings->pool + str.str;
}

static inline void scrt_init_strings()
{
  u8 *blk = (u8*)mmap(NULL, SCRT_Size_Strings, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
  scrt_strings = (SCRT_Strings *)blk;
  scrt_strings->cap = SCRT_Size_Strings;
  scrt_strings->off = 0;
  scrt_strings->pool = blk + sizeof(SCRT_Strings);
}

static Eq_Payload is_eq_at(const u8 *str, u32 len)
{
    Eq_Payload pl = NOT_MATCH;
    const u8 *found =
        (len < LONG_NEEDLE_THRESHOLD)
        ? two_way_short_needle(scrt_strings->pool, scrt_strings->off, str, len)
        : two_way_long_needle(scrt_strings->pool, scrt_strings->off, str, len);

    if (found) {
        pl = ((found - scrt_strings->pool) << 8) | MATCH;
        return pl;
    }

    return (u64)((0 | NOT_MATCH));
}



static SString scrt_string(const u8 *str)
{
  u32 len = 0;
  if(str[0] == '\0') return(SString){};
  while(str[++len]);

  if(scrt_strings->off >= scrt_strings->cap){
    printf("Out of memory. Exiting\n");
    exit(1);
  }

  SString pl = {};
  pl.str = scrt_strings->off;
  pl.len = len;


  u32 stride = 0;
  char ch;
  Eq_Payload is_eq = is_eq_at(str, len);
  if(is_eq & MATCH){
    pl.str = is_eq >> 8;
    return pl;
  }




  for(u32 idx = 0; idx < len; idx++)
  {
    scrt_strings->pool[scrt_strings->off++] = str[idx];
  }
  scrt_strings->pool[scrt_strings->off++] = '\0';

  return pl;
}

static SString _scrt_sstring_concat(const SString arr[], u64 len)
{
	u64 buff_len = 0;
	u64 begin = 0;
	while(begin < len){
		buff_len += arr[begin].len;
		begin++;
	}
	u8 *buff = (u8*)malloc(buff_len + 1);
	u64 buff_idx = 0;
	u64 idx = 0;
	u64 inner_idx;
	while(idx < len){
		u64 arr_len = arr[idx].len;
		const char *current = SCRT_AS_CHAR(arr[idx]);
		for (inner_idx = 0; inner_idx < arr_len; inner_idx++){
			buff[buff_idx++] = current[inner_idx];
		}
		idx++;
	}
	buff[buff_idx] = '\0';


	SString pl = scrt_string(buff);
	free(buff);
	return pl;

}


static SString _scrt_string_concat(const char *arr[], u64 len)
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

	u8 *buff = (u8*)malloc(buff_len + 1);
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


	SString pl = scrt_string(buff);
	free(buff);
	return pl;

}


static inline void scrt_print_string(SString str)
{
  struct iovec str_vec[2];
  str_vec[0].iov_base = scrt_strings->pool + str.str;
  str_vec[0].iov_len = str.len;
  str_vec[1].iov_base = "\n";
  str_vec[1].iov_len = 1;

  writev(1, str_vec, 2);
}

static inline u8* scrt_string_base(SString str)
{
  return scrt_strings->pool + str.str;
}



static inline bool scrt_strcmp(SString target, SString source)
{
  return target.str == source.str && target.len == source.len;
}

static SString scrt_file(char *path)
{
	int fd = open(path, O_RDONLY);

	struct stat st;
	fstat(fd, &st);

	u8 *buf = (u8 *)mmap(NULL, st.st_size + 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	read(fd, buf, st.st_size);
	buf[st.st_size] = '\0';
	SString pl = SCRT_STRING(buf);

	close(fd);
	munmap(buf, st.st_size + 1);
	return pl;
}




static inline void scrt_init()
{
  scrt_init_strings();
}
