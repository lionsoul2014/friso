#############################################################
# friso chinese word segmentation makefile.		            #
# @author	lionsoul 				                        #
# @email	chenxin619315@gmail.com   		                #
#############################################################

bin_PROGRAMS = friso
friso_CFLAGS = $(AM_CFLAGS)
friso_LDADD = libfriso.la -lm
friso_SOURCES = tst-friso.c

lib_LTLIBRARIES = libfriso.la

libfriso_la_LDFLAGS =		\
	-version-info 0:0:0	\
	-no-undefined

libfriso_la_LIBADD = -lm

libfriso_la_SOURCES =	\
	friso_API.h	\
	friso_ctype.h	\
	friso.h		\
	friso_array.c	\
	friso.c		\
	friso_ctype.c	\
	friso_GBK.c	\
	friso_hash.c	\
	friso_lexicon.c	\
	friso_link.c	\
	friso_string.c	\
	friso_UTF8.c

libfriso_includedir = $(pkgincludedir)
libfriso_include_HEADERS =	\
	friso.h			\
	friso_API.h		\
	friso_ctype.h
