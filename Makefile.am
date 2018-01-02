# Should be able to include headers from anywhere
AM_CPPFLAGS = -I$(top_srcdir)/src

# Exectutable name, though configure should be run
# from within the bin dir
bin_PROGRAMS = srt

# Source file list
# look for better way of handling subdir
srt_SOURCES = \
	src/SRT_define.h \
	src/SRT_endian.h \
	src/SRT_log.c \
	src/SRT_log.h \
	src/SRT_error.c \
	src/SRT_error.h \
	src/SRT_main.c

# Tests

# Git ignore
MAINTAINERCLEANFILES = \
	$(GITIGNORE_MAINTAINERCLEANFILES_TOPLEVEL) \
	$(GITIGNORE_MAINTAINERCLEANFILES_MAKEFILE_IN) \
	$(GITIGNORE_MAINTAINERCLEANFILES_M4_GETTEXT) \
	$(GITIGNORE_MAINTAINERCLEANFILES_M4_LIBTOOL)

-include $(top_srcdir)/git.mk
