dist_doc_DATA = AUTHORS ChangeLog COPYING INSTALL LICENSE NEWS README

ACLOCAL_AMFLAGS = -I build-aux/m4 -Wall -Werror

if DEBUG
AM_CFLAGS = -g3 -O0 -DDEBUG
else
AM_CFLAGS = -O2
endif

bin_PROGRAMS = \
	csgoprs

csgoprs_SOURCES = \
	src/utils.cc \
	src/main.cc
