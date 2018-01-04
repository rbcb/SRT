// SRT_define.h -- generic declarations for all headers

#ifdef MSC_VER
#	ifndef _CRT_SECURE_NO_DEPRECATE
#		define _CRT_SECURE_NO_DEPRECATE
#	endif
#endif

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
# 	error "K&R C unsupported"
#endif

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
 * this macro logic is modified from SDL begin_code.h (zlib licensed)
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

#ifndef SRT_CCALL
# 	if defined(_MSC_VER) || defined(__WINRT__) && !defined(__GNUC__)
# 		define SRT_CCALL __cdecl
# 	else
# 		define SRT_CCALL
# 	endif
#endif

#if defined(_DEBUG) || defined(DEBUG) || (defined(__GNUC__) && !defined(__OPTIMIZE__))
#	define SRT_DEBUG
#endif

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# 	pragma once
#endif
