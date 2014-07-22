dnl $Id$
dnl config.m4 for extension friso

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(friso, for friso support,
dnl Make sure that the comment is aligned:
dnl [  --with-friso             Include friso support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(friso, whether to enable friso support,
Make sure that the comment is aligned:
[  --enable-friso           Enable friso support])

if test "$PHP_FRISO" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-friso -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/friso.h"  # you most likely want to change this
  dnl if test -r $PHP_FRISO/$SEARCH_FOR; then # path given as parameter
  dnl   FRISO_DIR=$PHP_FRISO
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for friso files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       FRISO_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$FRISO_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the friso distribution])
  dnl fi

  dnl # --with-friso -> add include path
  dnl PHP_ADD_INCLUDE($FRISO_DIR/include)

  dnl # --with-friso -> check for lib and symbol presence
  dnl LIBNAME=friso # you may want to change this
  dnl LIBSYMBOL=friso # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $FRISO_DIR/lib, FRISO_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_FRISOLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong friso lib version or lib not found])
  dnl ],[
  dnl   -L$FRISO_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(FRISO_SHARED_LIBADD)

  PHP_NEW_EXTENSION(friso, friso.c, $ext_shared)
fi
