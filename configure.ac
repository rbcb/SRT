AC_PREREQ([2.68])
AC_INIT([srt], [0.1], [thedesignerpenguin@gmail.com], [srt])

# Hide away generated files in subdirs
AC_CONFIG_AUX_DIR([bin])
AC_CONFIG_MACRO_DIR([m4])

# Force automake all warnings are errors and non GNU structure
AM_INIT_AUTOMAKE([foreign dist-xz subdir-objects -Wall -Werror])

# Safety check
AC_CONFIG_SRCDIR([src/SRT_endian.h])

# The results of a config for inclusion in project
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_CC_C99
AC_PROG_SED
AC_PROG_MKDIR_P

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([limits.h stdint.h syslog.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
