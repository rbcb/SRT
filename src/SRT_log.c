#include "SRT_log.h"

#include <stdarg.h>
#include <stdlib.h> /* HAS_STDLIB */
#include <string.h> /* HAS_STRING */

#ifdef __linux__
# 	include <syslog.h>
#endif

#if 1 /* HAS_UNISTD */
# 	include <unistd.h>
#endif

#if !defined(WIN32_PLATFORM_PSPC) && !defined(_WIN32) /* ANSICON */
# 	define SRT_WINCOLOR 1
#else
# 	define SRT_WINCOLOR 0
#endif

static SRT_LogWriter SRT_log_writer = SRT_LogDefaultWriter;
static SRT_LogPrio SRT_log_prio = SRT_LOG_DEBUG;
static unsigned SRT_mcount;
static FILE* SRT_target;

static SRT_Bool
SRT_IsWhitespace(char c) {
	return
		(c == '\t' ||
		 c == '\n' ||
		 c == '\v' ||
		 c == '\f' ||
		 c == '\r' ||
		 c == ' ');
}

void
SRT_LogFormationV(const char* invoke_func, const char* invoke_file,
				 size_t invoke_line, SRT_LogPrio priority, const char* fmt, va_list args) {

	va_list ap;
	va_copy(ap, args);

	if (priority < SRT_log_prio || fmt == NULL)
		return;

	time_t t; time(&t);
	struct tm* lt = localtime(&t);

	priority =
		(priority > SRT_LOG_CRIT)? SRT_LOG_CRIT :
		(priority < SRT_LOG_DEBUG)? SRT_LOG_DEBUG : priority;

	size_t len = vsnprintf(NULL, 0, fmt, args) + 1;
	char* msg = malloc(len); /* USE MALLOC WRAPPER */
	vsnprintf(msg, len, fmt, ap);

	SRT_LogAux auxdata;
	auxdata.invoke_file = invoke_file;
	auxdata.invoke_func = invoke_func;
	auxdata.invoke_line = invoke_line;
	auxdata.invoke_timeinf = lt;
	auxdata.reference_id = SRT_mcount++;

	len = strlen(msg);
	char* mbit = msg + len;

	do {
		mbit--;
	} while (len-- && SRT_IsWhitespace(*mbit));

	*(mbit + 1) = 0;

	char* nptr = msg;

	while (SRT_IsWhitespace(*nptr) && *nptr++) {}

	if (SRT_log_writer)
		SRT_log_writer(nptr, priority, &auxdata);

	free(msg);

	va_end(ap);
}

void
SRT_LogFormation(const char* invoke_func, const char* invoke_file,
				 size_t invoke_line, SRT_LogPrio priority, const char* fmt, ...) {

	va_list ap;
	va_start(ap, fmt);

	SRT_LogFormationV(invoke_func, invoke_file, invoke_line, priority, fmt, ap);

	va_end(ap);
}

void
SRT_LogDefaultWriter(char* message, SRT_LogPrio priority, SRT_LogAux* auxdata) {
	static const char* SRT_prio_strings[] = {
		"DEBUG",
		"INFO",
		"NOTICE",
		"WARNING",
		"ERR",
		"CRIT"
	};

	static const char* SRT_prio_colors[] = {
		"\033[94m",
		"\033[36m",
		"\033[34m",
		"\033[33m",
		"\033[31m",
		"\033[35m"
	};

	SRT_Bool ansicolor = isatty(STDOUT_FILENO) || SRT_WINCOLOR; /* HAS_UNISTD */

	char short_timebuf[9];
	char long_timebuf[20];

	strftime(&short_timebuf[0], sizeof(short_timebuf), "%H:%M:%S", auxdata->invoke_timeinf);
	strftime(&long_timebuf[0], sizeof(long_timebuf), "%d-%m-%Y %H:%M:%S", auxdata->invoke_timeinf);

	if (ansicolor) {
		printf("%s %s%-7s \033[90m%s:%02d \033[37m%s\n\033[0m",
			short_timebuf,
			SRT_prio_colors[priority],
			SRT_prio_strings[priority],
			auxdata->invoke_file,
			auxdata->invoke_line,
			message);
	} else {
		printf("%s %-7s %s:%02d %s\n",
			short_timebuf,
			SRT_prio_strings[priority],
			auxdata->invoke_file,
			auxdata->invoke_line,
			message);
	}

	FILE* target = SRT_LogGetFile();
	if (target) {
		fprintf(target, "%s %-7s %s:%02d %s\n",
			long_timebuf,
			SRT_prio_strings[priority],
			auxdata->invoke_file,
			auxdata->invoke_line,
			message);

		fflush(target);
	}

#ifdef __linux__ /* HAS_SYSLOG */
	syslog(LOG_DEBUG - (int)priority, "%s", message);
#endif
}

SRT_LogWriter
SRT_LogGetWriter(void) {
	return SRT_log_writer;
}

void
SRT_LogSetWriter(SRT_LogWriter writer) {
	SRT_log_writer = writer;
}

FILE*
SRT_LogGetFile(void) {
	return SRT_target;
}

void
SRT_LogSetFile(FILE* fp) {
	SRT_target = fp;
}

SRT_LogPrio
SRT_LogGetPrio(void) {
	return SRT_log_prio;
}

void SRT_LogSetPrio(SRT_LogPrio prio) {
	if (prio >= SRT_LOG_DEBUG && prio <= SRT_LOG_CRIT)
		SRT_log_prio = prio;
}
