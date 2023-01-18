#ifndef __IPLATURE_UTILITY_UTIL_H__
#define  __IPLATURE_UTILITY_UTIL_H__

#define PACE_ZERO(v,t) do{static t p; v = p;}while(0);

# define cdr_int64_to(from) \
	( (((from) & (0xffull << 56)) >> 56) \
	| (((from) & (0xffull << 48)) >> 40) \
	| (((from) & (0xffull << 40)) >> 24) \
	| (((from) & (0xffull << 32)) >> 8) \
	| (((from) & (0xffull << 24)) << 8) \
	| (((from) & (0xffull << 16)) << 24) \
	| (((from) & (0xffull << 8)) << 40) \
	| (((from) & 0xffull) << 56) )


# define cdr_int32_to(from) \
	( (((from) & (0xfful << 24)) >> 24) \
	| (((from) & (0xfful << 16)) >> 8) \
	| (((from) & (0xfful << 8)) << 8) \
	| (((from) & 0xfful) << 24) )

# define cdr_int16_to(from) \
	( (((from) & (0xffu << 8)) >> 8) \
	| (((from) & 0xffu) << 8) )

#endif
