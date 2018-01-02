// SRT_log.h -- logging interface
#ifndef _LOG_H
#define _LOG_H

#include "SRT_define.h"

#include <time.h>
#include <stdio.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/* the importance of a log determines weather it should or should not be ignored
 * match syslog level, excluding very high priority logs as these cannot occur
 */
typedef enum {
	SRT_LOG_DEBUG,   /* debugging message */
	SRT_LOG_INFO,    /* informational message */
	SRT_LOG_NOTICE,  /* note that logical change has occurred */
	SRT_LOG_WARNING, /* warning message */
	SRT_LOG_ERR,     /* error message, created by error.h */
	SRT_LOG_CRIT     /* critical condition reached */
} SRT_LogPrio;

/* set the current log priority baseline, logs with a priority lower than this will be ignored */
extern void SRT_CCALL SRT_LogSetPrio(SRT_LogPrio prio);

/* get the current internal log priority */
extern SRT_LogPrio SRT_CCALL SRT_LogGetPrio(void);

/* set a file to write to, by default the internal fp will remain NULL */
extern void SRT_CCALL SRT_LogSetFile(FILE* fp);

/* get the current write file stored internally, by default will be NULL */
extern FILE* SRT_CCALL SRT_LogGetFile(void);

/* a structure identifying all aux data coming with a log
 * most can be ignored but may be used to format by SRT_LogWriter
 */
typedef struct {
	const char* invoke_func;
	const char* invoke_file;
	size_t invoke_line;
	size_t reference_id;
	struct tm* invoke_timeinf;
} SRT_LogAux;

/* a function that describes the transmission of log data including its format
 * when writing to a file reference SRT_LogGetFile(...) which may return NULL
 */
typedef void (*SRT_LogWriter)(char* message, SRT_LogPrio priority, SRT_LogAux* auxdata);

/* set the current writer function, the default is SRT_LogWriter(...)
 * this can be set to NULL to disable all logs
 */
extern void SRT_CCALL SRT_LogSetWriter(SRT_LogWriter writer);

/* get the current writer used internally */
extern SRT_LogWriter SRT_CCALL SRT_LogGetWriter(void);

/* the default SRT_LogWriter implementation, behavior is as follows:
 * writes to stdout and a file if it has been set by SRT_LogSetFile
 * writes to syslog if on a linux system that has <syslog.h> catagory XXX
 * uses ANSI color codes if on a system that supports it
 * format is "{time} {priority} {invoke file}:{invoke line} {message}"
 */
extern void SRT_CCALL SRT_LogDefaultWriter(char* message, SRT_LogPrio priority, SRT_LogAux* auxdata);

/* generate a log by forming aux data from params and parsing to log writer
 * should not be called directly, rather use SRT_Log macro
 */
extern void SRT_CCALL SRT_LogFormation(const char* invoke_func, const char* invoke_file,
		size_t invoke_line, SRT_LogPrio priority, const char* fmt, ...) SRT_PRINTFLIKE(5);

/* generate a log by forming aux data from params and parsing to log writer
 * should not be called directly, rather use SRT_Log macro
 */
extern void SRT_CCALL SRT_LogFormationV(const char* invoke_func, const char* invoke_file,
		size_t invoke_line, SRT_LogPrio priority, const char* fmt, va_list args);

#if ((__GNUC__ >= 2) || defined(_MSC_VER) || defined (__WATCOMC__))
#	define __func__ __FUNCTION__
#else
#	define __func__ "<anonymous>"
#endif

#if SRT_CVER < 1990
# 	error "logs require C99 variatic macros"
#else
# 	define SRT_Log(prio, f, a...)  SRT_LogFormation(__func__, __FILE__, __LINE__, prio, f, ##a)
# 	define SRT_LogDebug(f, a...)   SRT_Log(SRT_LOG_DEBUG, f, ##a)
# 	define SRT_LogInfo(f, a...)    SRT_Log(SRT_LOG_INFO, f, ##a)
# 	define SRT_LogNotice(f, a...)  SRT_Log(SRT_LOG_NOTICE, f, ##a)
# 	define SRT_LogWarning(f, a...) SRT_Log(SRT_LOG_WARNING, f, ##a)
# 	define SRT_LogErr(f, a...)     SRT_Log(SRT_LOG_ERR, f, ##a)
# 	define SRT_LogCrit(f, a...)    SRT_Log(SRT_LOG_CRIT, f, ##a)
#endif

#ifdef __cplusplus
}
#endif

#endif
