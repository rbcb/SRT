// SRT_define.h -- generic declarations for all headers

/* #ifdef _DEFINE_H
 * #error "define.h may be included once per header"
 * #endif
 * #define _DEFINE_H
 */

#include <stdio.h>
#include <stdarg.h>

/* determine C version */
#ifdef __STDC__
# 	ifdef __STDC_VERSION__
# 		if __STDC_VERSION__ >= 201112L
# 			define SRT_CVER 2011
# 		elif __STDC_VERSION__ >= 199901L
# 			define SRT_CVER 1999
# 		else
# 			define SRT_CVER 1994
# 		endif
# 	else
#		define SRT_CVER 1989
# 	endif
#else
# 	define SRT_CVER 1978
#endif

#if SRT_CVER <= 1989
# 	define const
# 	define volatile
#endif

/* determine compiler */
#if defined(__clang__)
#	define SRT_CMPCLANG
#elif defined(__ICC) || defined(__INTEL_COMPILER)
#	define SRT_CMPICC
#elif defined(__GNUC__) || defined(__GNUG__)
#	define SRT_CMPGCC
#elif defined(__HP_cc) || defined(__HP_aCC)
#	define SRT_CMPHP
#elif defined(__IBMC__) || defined(__IBMCPP__)
#	define SRT_CMPIBM
#elif defined(_MSC_VER)
#	define SRT_CMPVS
#elif defined(__PGI)
#	define SRT_CMPPGCC
#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#	define SRT_CMPSOLARIS
#endif

/* handle NULL between C and C++ */
#if !defined(NULL)
# 	if defined(__cplusplus)
# 		define NULL ((void*)0)
# 	else
# 		define NULL 0
# 	endif
#endif

/* for functions defined in the header, inline linkage must be used
 * this macro logic is modified from SDL2 begin_code.h (zlib licensed)
 */
#ifndef SRT_INLINE
# 	if defined(_MSC_VER)
# 	 	define SRT_INLINE __forceinline
# 	elif ( (defined(__GNUC__) && (__GNUC__ >= 4)) || defined(__clang__) )
#	 	define SRT_INLINE __attribute__((always_inline)) static __inline__
# 	else
#	 	ifndef __inline__
#			if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__DMC__) || defined(__SC__)
#				define __inline__ __inline
#			elif defined(__WATCOMC__) || defined(__LCC__) || defined(__DECC) || defined(__CC_ARM)
#				define __inline__ __inline
#			else
#				define __inline__ inline
#			endif
#		endif
#		define SRT_INLINE static __inline__
# 	endif
#endif

/* use C caling convention */
#ifndef SRT_CCALL
# 	if defined(_MSC_VER) || defined(__WINRT__) && !defined(__GNUC__)
# 		define SRT_CCALL __cdecl
# 	else
# 		define SRT_CCALL
# 	endif
#endif

/* typedefs */
#ifndef SRT_TYPEDEFS
#define SRT_TYPEDEFS

#if defined(__STDC__) || defined(__cplusplus) || defined(_MSC_EXTENSIONS)
typedef void* SRT_Voidp;
#else
typedef char* SRT_Voidp;
#endif

typedef int SRT_Bool;

#define SRT_True 1
#define SRT_False 0

#include <stdint.h>

typedef int8_t    SRT_Sint8;
typedef uint8_t   SRT_Uint8;
typedef int16_t   SRT_Sint16;
typedef uint16_t  SRT_Uint16;
typedef int32_t   SRT_Sint32;
typedef uint32_t  SRT_Uint32;
typedef int64_t   SRT_Sint64;
typedef uint64_t  SRT_Uint64;

#endif

/* printf style argument checking compiler hint */
#if defined(__printflike)
# 	define SRT_PRINTFLIKE(n) __printflike(n, n+1)
#elif defined(__GNUC__)
# 	define SRT_PRINTFLIKE(n) __attribute__((format( __printf__, n, n+1)))
#else
# 	define SRT_PRINTFLIKE(n)
#endif

/* standardize the debug macro from VCC */
#if defined(_DEBUG) || defined(DEBUG) || (defined(__GNUC__) && !defined(__OPTIMIZE__))
#	define SRT_DEBUG
#endif

/* only include child file once */
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# 	pragma once
#endif
