// SRT_stdlib.h -- libstd autotools standardization
// largely a stripped down version of stdinc.h from libSDL
#ifndef _STD_H
#define _STD_H

#include "SRT_config.h"

#ifdef HAVE_STDIO_H
#	include <stdio.h>
#endif
#ifdef STDC_HEADERS
#	include <stdlib.h>
#	include <stddef.h>
#	include <stdarg.h>
#else
#	ifdef HAVE_STDLIB_H
#		include <stdlib.h>
#	elif defined(HAVE_MALLOC_H)
#		include <malloc.h>
#	endif
#	ifdef HAVE_STDDEF_H
#		include <stddef.h>
#	endif
#	ifdef HAVE_STDARG_H
#		include <stdarg.h>
#	endif
#endif
#ifdef HAVE_STRING_H
#	include <string.h>
#endif
#ifdef HAVE_INTTYPES_H
#	include <inttypes.h>
#elif defined(HAVE_STDINT_H)
#	include <stdint.h>
#endif
#ifdef HAVE_LIMITS_H
#	include <limits.h>
#endif
#if HAVE_MATH_H
#	include <math.h>
#endif
#if HAVE_TIME_H
#	include <time.h>
#endif

#if !defined(HAVE_M_PI) && !defined(M_PI)
#	define M_PI 3.1415926535897
#endif

#if defined(HAVE_CHAR_BIT) && defined(CHAR_BIT)
#	if CHAR_BIT != 8
#		error "bad char bit length"
#	endif
#endif

typedef int SRT_Bool;

#define SRT_True 1
#define SRT_False 0

typedef int8_t    SRT_Sint8;
typedef uint8_t   SRT_Uint8;
typedef int16_t   SRT_Sint16;
typedef uint16_t  SRT_Uint16;
typedef int32_t   SRT_Sint32;
typedef uint32_t  SRT_Uint32;
typedef int64_t   SRT_Sint64;
typedef uint64_t  SRT_Uint64;

// #define SRT_CTASRT(n, x) typedef int SRT_CTASRT_ ## n[(x) * 2 - 1]
//
// SRT_CTASRT(SINT8, sizeof(SRT_Sint8) == 1);
// SRT_CTASRT(UINT8, sizeof(SRT_Uint8) == 1);
// SRT_CTASRT(SINT16, sizeof(SRT_Sint16) == 2)
// SRT_CTASRT(UINT16, sizeof(SRT_Uint16) == 2);
// SRT_CTASRT(SINT32, sizeof(SRT_Sint32) == 4);
// SRT_CTASRT(UINT32, sizeof(SRT_Uint32) == 4);
// SRT_CTASRT(SINT64, sizeof(SRT_Sint64) == 8);
// SRT_CTASRT(UINT64, sizeof(SRT_Uint64) == 8);
//
// #undef SRT_CTASRT

#ifndef HAVE_LIMITS_H
#	if sizeof(size_t) == 8
typedef SRT_Sint64 ssize_t;
#	elif sizeof(size_t) == 4
typedef SRT_Sint32 ssize_t;
#	else
typedef int ssize_t;
#	endif
#endif

#ifdef __GNUC__
# 	define SRT_PRINTFLIKE(n) __attribute__((format( __printf__, n, n+1)))
# 	define SRT_SCANFLIKE(n) __attribute__((format( __scanf__, n, n+1)))
#elif defined(__printflike)
# 	define SRT_PRINTFLIKE(n) __printflike(n, n+1)
# 	define SRT_SCANFLIKE(n)
#else
# 	define SRT_PRINTFLIKE(n)
# 	define SRT_SCANFLIKE(n)
#endif

#ifndef __func__
#	if ((defined(__GNUC__) && __GNUC__ >= 2) || defined(_MSC_VER) || defined(__WATCOMC__))
#		define __func__ __FUNCTION__
#	else
#		define __func__ "<anonymous>"
#	endif
#endif

#ifndef va_copy
#	ifdef __va_copy
#		define va_copy __va_copy
#	else
#		define va_copy(dst, src) memcpy (&dst, &src, sizeof (va_list))
#	endif
#endif

#include "SRT_define.h"

#ifdef __cplusplus
extern "C" {
#endif

extern SRT_Bool SRT_CCALL SRT_IsArabic(int c);
extern SRT_Bool SRT_CCALL SRT_IsLower(int c);
extern SRT_Bool SRT_CCALL SRT_IsUpper(int c);
extern SRT_Bool SRT_CCALL SRT_IsWhitespace(int c);
extern SRT_Bool SRT_CCALL SRT_IsLatin(int c);

extern char* SRT_CCALL SRT_LStrip(char* buf);
extern char* SRT_CCALL SRT_RStrip(char* buf);
extern char* SRT_CCALL SRT_Strip(char* buf);
extern char* SRT_CCALL SRT_ToUpper(char* buf);
extern char* SRT_CCALL SRT_ToLower(char* buf);
extern char* SRT_CCALL SRT_StrDup(const char* src);

extern int SRT_CCALL SRT_Abs(int a);
extern int SRT_CCALL SRT_Sign(int a);
extern int SRT_CCALL SRT_Min(int a, int b);
extern int SRT_CCALL SRT_Max(int a, int b);

#ifdef __cplusplus
}
#endif

#endif
