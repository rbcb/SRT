// SRT_error.h -- internal error state maintainer
#ifndef _SRT_ERROR_H
#define _SRT_ERROR_H

#include "SRT_define.h"
#include "SRT_log.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SRT_ERROR_STRMAX
# 	define SRT_ERROR_STRMAX 256
#endif

/* the list of error codes for generic error conditions
 * usually used as the return value for a function indicating it's status
 */
typedef enum {
	SRT_STATUS_GOOD,
	SRT_STATUS_BAD,
	SRT_STATUS_BAD_PARAM,
	SRT_STATUS_BAD_ALLOC,
	SRT_STATUS_BAD_FILEIO,
	SRT_STATUS_BAD_OP,
	SRT_STATUS_BAD_LOGIC,
	SRT_STATUS_BAD_SYSCALL
} SRT_Error;

/* get the last error status generated starting with GOOD */
extern SRT_Error SRT_CCALL SRT_ErrorGetStatus(void);

/* get the last error status generated starting with GOOD and then clear */
extern SRT_Error SRT_CCALL SRT_ErrorEmplaceStatus(void);

/* write the last error string into a buffer */
extern void SRT_CCALL SRT_ErrorGetString(char* dst, size_t len);

/* write the last error string into a buffer and then clear */
extern void SRT_CCALL SRT_ErrorEmplaceString(char* dst, size_t len);

/* reset the current error data to NULL */
extern void SRT_CCALL SRT_ErrorClear(void);

/* set the last error data based on an SRT_Error and use a generic string */
extern SRT_Error SRT_CCALL SRT_ErrorStatus(SRT_Error code);

/* set the last error data using a formatted string with a generic SRT_Error */
extern SRT_Error SRT_CCALL SRT_ErrorString(const char* fmt, ...) SRT_PRINTFLIKE(1);

/* set the last error data with a formatted string and SRT_Error */
extern SRT_Error SRT_CCALL SRT_ErrorMixed(SRT_Error code, const char* fmt, ...) SRT_PRINTFLIKE(2);

/* log the internal error data and then clear */
#define SRT_ErrorLog() do { \
		char __tmp_plbuf[SRT_ERROR_STRMAX]; \
		SRT_ErrorGetString(__tmp_plbuf, SRT_ERROR_STRMAX); \
		SRT_LogErr("[%d] %s", SRT_ErrorGetStatus(), __tmp_plbuf); \
		SRT_ErrorClear(); \
	} while(0)

#ifdef __cplusplus
}
#endif

#endif
