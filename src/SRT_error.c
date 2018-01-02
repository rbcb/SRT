#include "SRT_error.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

char SRT_error_msg[SRT_ERROR_STRMAX];
SRT_Error SRT_error_code;

SRT_Error
SRT_ErrorMixed(SRT_Error code, const char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);

	vsnprintf(&SRT_error_msg[0], SRT_ERROR_STRMAX, fmt, ap);
	SRT_error_code = code;

	va_end(ap);
}

SRT_Error
SRT_ErrorString(const char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);

	vsnprintf(&SRT_error_msg[0], SRT_ERROR_STRMAX, fmt, ap);
	SRT_error_code = SRT_STATUS_BAD;

	va_end(ap);
}

SRT_Error
SRT_ErrorStatus(SRT_Error code) {
	static const char* SRT_code_strings[] = {
		NULL,
		"something went wrong",
		"func was passed bad param",
		"an allocation went bad",
		"a file IO operation failed",
		"an operation failed",
		"a logical condition was met",
		"a syscall failed"
	};

	SRT_error_code = code;

	if (code != SRT_STATUS_GOOD)
		memcpy(&SRT_error_msg[0], SRT_code_strings[code], sizeof(SRT_code_strings[code]));
}

void
SRT_ErrorClear(void) {
	SRT_error_code = SRT_STATUS_GOOD;
	memset(&SRT_error_msg[0], 0, sizeof(SRT_ERROR_STRMAX));
}


void
SRT_ErrorEmplaceString(char* dst, size_t len) {
	SRT_ErrorGetString(dst, len);
	SRT_ErrorClear();
}

void
SRT_ErrorGetString(char* dst, size_t len) {
	strncpy(dst, &SRT_error_msg[0], (len < SRT_ERROR_STRMAX)? len : SRT_ERROR_STRMAX);
}

SRT_Error
SRT_ErrorEmplaceStatus(void) {
	SRT_Error e = SRT_ErrorGetStatus();
	SRT_ErrorClear();

	return e;
}

SRT_Error
SRT_ErrorGetStatus(void) {
	return SRT_error_code;
}
