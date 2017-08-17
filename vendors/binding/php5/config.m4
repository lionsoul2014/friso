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

   # --with-friso -> check with-path
   SEARCH_PATH="/usr/local /usr"     # you might want to change this
   SEARCH_FOR="lib/libfriso.so"  # you most likely want to change this
   if test -r $PHP_FRISO/$SEARCH_FOR; then # path given as parameter
     FRISO_DIR=$PHP_FRISO
   else # search default path list
     AC_MSG_CHECKING([for friso files in default path])
     for i in $SEARCH_PATH ; do
       if test -r $i/$SEARCH_FOR; then
         FRISO_DIR=$i
         AC_MSG_RESULT(found in $i)
       fi
     done
   fi
  
   if test -z "$FRISO_DIR"; then
     AC_MSG_RESULT([not found])
     AC_MSG_ERROR([Please reinstall the friso distribution])
   fi

   # --with-friso -> add include path
   PHP_ADD_INCLUDE($FRISO_DIR/include)

   # --with-friso -> check for lib and symbol presence
   LIBNAME=friso # you may want to change this
   LIBSYMBOL=friso_new # you most likely want to change this 

   PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
   [
     PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $FRISO_DIR/lib, FRISO_SHARED_LIBADD)
     AC_DEFINE(HAVE_FRISOLIB,1,[ ])
   ],[
     AC_MSG_ERROR([wrong friso lib version or lib not found])
   ],[
     -L$FRISO_DIR/lib -lm
   ])
  
   PHP_SUBST(FRISO_SHARED_LIBADD)

  PHP_NEW_EXTENSION(friso, friso.c, $ext_shared)
fi
