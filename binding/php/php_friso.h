
#ifndef PHP_FRISO_H
#define PHP_FRISO_H

extern zend_module_entry friso_module_entry;
#define phpext_friso_ptr &friso_module_entry

#ifdef PHP_WIN32
#	define PHP_FRISO_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_FRISO_API __attribute__ ((visibility("default")))
#else
#	define PHP_FRISO_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#include <friso/friso_API.h>
#include <friso/friso.h>

PHP_MINIT_FUNCTION(friso);
PHP_MSHUTDOWN_FUNCTION(friso);
PHP_RINIT_FUNCTION(friso);
PHP_RSHUTDOWN_FUNCTION(friso);
PHP_MINFO_FUNCTION(friso);

PHP_FUNCTION(friso_split);
PHP_FUNCTION(friso_version);
PHP_FUNCTION(friso_charset);
PHP_FUNCTION(friso_dic_exist);
PHP_FUNCTION(friso_dic_get);
PHP_FUNCTION(friso_utf8_bytes);
PHP_FUNCTION(friso_utf8_ucode);
PHP_FUNCTION(friso_ucode_utf8);

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(friso)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(friso)
*/

typedef struct {
  friso_t friso;
  friso_config_t config;
} zend_friso_globals;

/* In every utility function you add that needs to use variables 
   in php_friso_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as FRISO_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define FRISO_G(v) TSRMG(friso_globals_id, zend_friso_globals *, v)
#else
#define FRISO_G(v) (friso_globals.v)
#endif

#endif	/* PHP_FRISO_H */

