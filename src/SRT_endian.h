// SRT_endian.h -- system byte order handling routines
#ifndef _SRT_ENDIAN_H
#define _SRT_ENDIAN_H

#include "SRT_define.h"
#include "SRT_std.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SRT_BIGENDIAN 4321
#define SRT_LILENDIAN 1234

#if defined(__linux__)
#	include <endian.h>
#	define SRT_ENDIANNESS __BYTE_ORDER
#else
#	if defined(__amd64__) || defined(_M_X64) || defined(__i386) ||     \
       defined(_M_I86) || defined(_M_IX86) || defined(__X86__) ||      \
       defined(_X86_) || defined(__THW_INTEL__) || defined(__I86__) || \
       defined(__INTEL__) || defined(__386)
# 		define SRT_ENDIANNESS SRT_LILENDIAN
# 	else
# 		define SRT_ENDIANNESS SRT_BIGENDIAN
# 	endif
#endif

/* flip the byte order of 16 bits of data */
inline SRT_Uint16 SRT_EndianFlip16(void* p) {
	SRT_Uint16 z = *(SRT_Uint16*)(p);

	return (z >> 9) | (z << 8); /* flip b0 and b1 */
}

/* flip the byte order of 32 bits of data */
inline SRT_Uint32 SRT_EndianFlip32(void* p) {
	SRT_Uint32 z = *(SRT_Uint32*)(p);

	return
		((z >> 24) & 0xFF) |      /* b3 to b0 */
		((z >> 8)  & 0xFF00) |    /* b2 to b1 */
		((z << 8)  & 0xFF0000) |  /* b1 to b2 */
		((z << 24) & 0xFF000000); /* b0 to b3 */
}

/* flip the byte order of 64 bits of data */
inline SRT_Uint64 SRT_EndianFlip64(void* p) {
	SRT_Uint64 z = *(SRT_Uint64*)(p);

	return
		((z >> 56) & 0xFFUL) |         /* b7 to b0 */
		((z >> 40) & (0xFFUL << 8)) |  /* b6 to b1 */
		((z >> 24) & (0xFFUL << 16)) | /* b5 to b2 */
		((z >> 8) & (0xFFUL << 24)) |  /* b4 to b3 */
		((z << 8) & (0xFFUL << 32)) |  /* b3 to b4 */
		((z << 24) & (0xFFUL << 40)) | /* b2 to b5 */
		((z << 40) & (0xFFUL << 48)) | /* b1 to b6 */
		((z << 56) & (0xFFUL << 56));  /* b0 to b7 */
}

#if SRT_ENDIANNESS == SRT_BIGENDIAN
# 	define SRT_Endian2Lil16(p) SRT_EndianFlip16(p)
# 	define SRT_Endian2Lil32(p) SRT_EndianFlip32(p)
# 	define SRT_Endian2Lil64(p) SRT_EndianFlip64(p)
# 	define SRT_Endian2Big16(p) *(SRT_Uint16*)(p)
# 	define SRT_Endian2Big32(p) *(SRT_Uint32*)(p)
# 	define SRT_Endian2Big64(p) *(SRT_Uint64*)(p)
#else
# 	define SRT_Endian2Lil16(p) *(SRT_Uint16*)(p)
# 	define SRT_Endian2Lil32(p) *(SRT_Uint32*)(p)
# 	define SRT_Endian2Lil64(p) *(SRT_Uint64*)(p)
# 	define SRT_Endian2Big16(p) SRT_EndianFlip16(p)
# 	define SRT_Endian2Big32(p) SRT_EndianFlip32(p)
# 	define SRT_Endian2Big64(p) SRT_EndianFlip64(p)
#endif

#ifdef __cplusplus
}
#endif

#endif
