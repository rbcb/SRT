#include <stdio.h>

#include "SRT_endian.h"
#include "SRT_log.h"
#include "SRT_error.h"

SRT_Error example_divide(int* a, int b) {
	if (b == 0)
		return SRT_ErrorString("divide by zero");

	*a = *a / b;

	return SRT_STATUS_GOOD;
}

int main(int argc, char** argv) {
	SRT_LogInfo("running example");

	int dividend = 3;
	if (example_divide(&dividend, 0))
		SRT_ErrorLog();
}
