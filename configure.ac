#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.59])
AC_INIT([friso], [1.6.4], [chenxin619315@gmail.com])
AC_CONFIG_SRCDIR([src/friso_ctype.h])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([tar-pax foreign])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

# Checks for programs.
AC_PROG_CC

AC_PROG_LIBTOOL

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([memset strcasecmp strdup])

AC_CONFIG_FILES([
  Makefile
  src/Makefile
  friso.pc
  friso.ini
  vendors/Makefile
  vendors/dict/Makefile
  vendors/dict/GBK/Makefile
  vendors/dict/UTF-8/Makefile
])
AC_OUTPUT
