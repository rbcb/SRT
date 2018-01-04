#include "SRT_std.h"

SRT_Bool
SRT_IsArabic(int c) {
	return c >= '0' && c <= '9';
}

SRT_Bool
SRT_IsLower(int c) {
	return c >= 'a' && c <= 'z';
}

SRT_Bool
SRT_IsUpper(int c) {
	return c >= 'A' && c <= 'Z';
}

SRT_Bool
SRT_IsWhitespace(int c) {
	return
		(c == '\t' ||
		 c == '\n' ||
		 c == '\v' ||
		 c == '\f' ||
		 c == '\r' ||
		 c == ' ');
}

SRT_Bool
SRT_IsLatin(int c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

char*
SRT_LStrip(char* buf) {
	while (SRT_IsWhitespace(*buf) && *buf++)
		{ }

	return buf;
}

char*
SRT_RStrip(char* buf) {
	size_t len = strlen(buf);
	char* m = buf + len;

	do {
		m--;
	} while (len-- && SRT_IsWhitespace(*m));

	*(m + 1) = '\0';

	return buf;
}

char*
SRT_Strip(char* buf) {
	return SRT_LStrip(SRT_RStrip(buf));
}

char*
SRT_ToUpper(char* buf) {
	char* m = buf;

	do {
		if (SRT_IsLower(*m))
			*m &= '_';
	} while (*++m);

	return buf;
}

char*
SRT_ToLower(char* buf) {
	char* m = buf;

	do {
		if (SRT_IsUpper(*m))
			*m |= ' ';
	} while (*++m);

	return buf;
}

char*
SRT_StrDup(const char* src) {
	size_t len = strlen(src) + 1;
	char* res = malloc(len);

	if (!res)
		return NULL;

	memcpy(res, src, len);

	return res;
}

int
SRT_Abs(int a) {
	return (a < 0)? -a : a;
}

int
SRT_Sign(int a) {
	return (a > 0) - (a < 0);
}

int
SRT_Min(int a, int b) {
	return (a < b)? a : b;
}

int
SRT_Max(int a, int b) {
	return (a > b)? a : b;
}
