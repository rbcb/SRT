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
AC_CONFIG_HEADERS([src/SRT_config.h])

# Checks for programs.
AC_PROG_CC_C99
AC_PROG_CPP
AC_LANG([C])

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdio.h stdlib.h malloc.h stddef.h stdarg.h string.h inttypes.h stdint.h limits.h math.h time.h unistd.h syslog.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_DEFINE(M_PI, math.h)
AC_CHECK_DEFINE(CHAR_BIT, limits.h)

# Checks for library functions.
AC_CHECK_FUNCS([malloc calloc realloc free memset memcpy memmove strlen strnlen strcmp vsnprintf snprintf])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
