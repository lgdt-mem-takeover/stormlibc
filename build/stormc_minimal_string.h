#pragma once
static inline String make_string(char *in)
{
	u64 len, idx;
	String pl;

	len = 0;
	while(in[++len]);
	pl.str = (char *)malloc(len);

	for (idx = 0; idx < len; idx++){
		pl.str[idx] = in[idx];
	}
	pl.len = len;

	return pl;
}

static inline bool sstrcmpx(const String dst, const String src)
{

    if(dst.len != src.len) return false;

    u64 idx;

    for (idx = 0; idx < dst.len; idx++){
	if (dst.str[idx] != src.str[idx]) return false;
    }
    return true;
}


static inline u64 sstrlenx(const char *string)
{
    if(string[0] == '\0') return 0;
    u64 count = 0;
    while(string[++count]);
    return count;
}
