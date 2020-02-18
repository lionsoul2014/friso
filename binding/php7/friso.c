/*
   +----------------------------------------------------------------------+
   | PHP Version 7                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2016 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: dongyado<dongyado@gmail.com>                                 |
   +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include <zend_exceptions.h>
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_friso.h"

#ifdef FRISO_WINNT
#    define friso_default_conf_file "c:/windows/friso.ini"
#else
#    define friso_default_conf_file "/etc/friso/friso.ini"
#endif

/* If you declare any globals in php_friso.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(friso)
*/
zend_friso_globals friso_globals;

/* True global resources - no need for thread safety here */
static int le_friso = 1;


/* {{{ friso_functions[]
 *
 * Every user visible function must have an entry in friso_functions[].
 */
const zend_function_entry friso_functions[] = {
    PHP_FE(friso_split,        NULL)
    PHP_FE(friso_version,    NULL)
    PHP_FE(friso_charset,        NULL)
    PHP_FE(friso_dic_exist,    NULL)
    PHP_FE(friso_dic_get,        NULL)
    PHP_FE(friso_utf8_bytes,    NULL)
    PHP_FE(friso_utf8_ucode,    NULL)
    PHP_FE(friso_ucode_utf8,    NULL)
    {NULL, NULL, NULL}    /* Must be the last line in friso_functions[] */
};
/* }}} */


/* {{{ friso_module_entry
 */
zend_module_entry friso_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    "friso",
    friso_functions,
    PHP_MINIT(friso),
    PHP_MSHUTDOWN(friso),
    PHP_RINIT(friso),        /* Replace with NULL if there's nothing to do at request start */
    PHP_RSHUTDOWN(friso),    /* Replace with NULL if there's nothing to do at request end */
    PHP_MINFO(friso),
#if ZEND_MODULE_API_NO >= 20010901
    "0.1", /* Replace with version number for your extension */
#endif
    STANDARD_MODULE_PROPERTIES
};
/* }}} */


#ifdef COMPILE_DL_FRISO
ZEND_GET_MODULE(friso)
#endif


/* {{{ PHP_INI
 */
PHP_INI_BEGIN()
    PHP_INI_ENTRY("friso.ini_file", friso_default_conf_file, PHP_INI_SYSTEM, NULL)
PHP_INI_END()
/* }}} */


/* {{{ php_robbe_globals_construct */
static void php_friso_globals_construct(zend_friso_globals *friso_globals)
{
    friso_globals->friso = friso_new();
    friso_globals->config = friso_new_config();
    friso_init_from_ifile(friso_globals->friso,
            friso_globals->config, INI_STR("friso.ini_file"));
}
/* }}} */


/* {{{ php_robbe_globals_destruct*/
static void php_friso_globals_destruct(zend_friso_globals *friso_globals) 
{
    /*
     * cause friso_free will free the dictionary
     *        so here we don't have to call the friso_dic_free to free the
     *    the robbe_dic global variable.        
     */
    //friso_dic_free( friso_globals->friso_dic );
    //friso_globals->friso_dic = NULL;
    friso_free_config( friso_globals->config );
    friso_free( friso_globals->friso );
}
/* }}} */

#define FRISO_RET_WORD        (1 << 0)
#define FRISO_RET_TYPE        (1 << 1)
#define FRISO_RET_OFF        (1 << 2)
#define FRISO_RET_LEN         (1 << 3)
#define FRISO_RET_RLEN        (1 << 4)
#define FRISO_RET_POS        (1 << 5)


/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(friso)
{
    /*
     * register some contants that robbe may use
     *        at its following work.
     *    the constant is case sensitive and persitent.
     */
    REGISTER_LONG_CONSTANT("FRISO_SIMPLE",        __FRISO_SIMPLE_MODE__, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("FRISO_COMPLEX",        __FRISO_COMPLEX_MODE__, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("FRISO_DETECT",        __FRISO_DETECT_MODE__, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("FRISO_LEX_CJK",        __LEX_CJK_WORDS__, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("FRISO_LEX_STOP",    __LEX_STOPWORDS__, CONST_CS | CONST_PERSISTENT);

    //return parts for rb_split.
    REGISTER_LONG_CONSTANT("FRISO_RET_WORD",     FRISO_RET_WORD, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("FRISO_RET_TYPE",     FRISO_RET_TYPE, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("FRISO_RET_OFF",        FRISO_RET_OFF, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("FRISO_RET_LEN",        FRISO_RET_LEN, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("FRISO_RET_RLEN",    FRISO_RET_RLEN, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("FRISO_RET_POS",      FRISO_RET_POS, CONST_CS | CONST_PERSISTENT);

    //lex type constants.
    REGISTER_LONG_CONSTANT("FRISO_TYP_CJK",      __LEX_CJK_WORDS__, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("FRISO_TYP_ECM",      __LEX_ECM_WORDS__, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("FRISO_TYP_CEM",      __LEX_CEM_WORDS__, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("FRISO_TYP_EPUN",      __LEX_ENPUN_WORDS__, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("FRISO_TYP_PUN",      __LEX_OTHER_WORDS__, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("FRISO_TYP_UNK",      __LEX_UNKNOW_WORDS__, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("FRISO_TYP_OTR",      __LEX_OTHER_WORDS__, CONST_CS | CONST_PERSISTENT);

    REGISTER_INI_ENTRIES();
    /*initialize the globals variables.*/
    php_friso_globals_construct( &friso_globals );

    return SUCCESS;
}
/* }}} */


/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(friso)
{
    UNREGISTER_INI_ENTRIES();
    /*destruct the globals variables*/
    php_friso_globals_destruct(  &friso_globals );
    
    return SUCCESS;
}
/* }}} */


/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(friso)
{
    return SUCCESS;
}
/* }}} */


/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(friso)
{
    return SUCCESS;
}
/* }}} */


/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(friso)
{    
    php_info_print_table_start();
    php_info_print_table_row(2, "Friso Support", "enabled");
    php_info_print_table_row(2, "Version", FRISO_VERSION);
    php_info_print_table_row(2, "Bug Report", "dongyado@gmail.com");
    php_info_print_table_row(2, "Home page", "https://github.com/lionsoul2014/friso");
    php_info_print_table_end();

    DISPLAY_INI_ENTRIES();
}
/* }}} */


/* {{{ proto array friso_split(string str, long mode)
   Return a array contains all the split result with a specified mode */
PHP_FUNCTION(friso_split)
{
    char *_str = NULL, *_key;
    int idx, arg_count;
    zend_long rargs = 0;

	size_t slen, klen;
    zval ret, item;
	zval *cfg, *setting;

	zend_ulong num_key;
	zend_string *key;

    HashTable *cfgArr;
    HashPosition pointer;

    //get the arugments from the php layer.
    arg_count = ZEND_NUM_ARGS();
    switch ( arg_count )
    {
        case 2:
            if ( zend_parse_parameters(arg_count TSRMLS_CC, "sz",
                 &_str, &slen, &cfg) == FAILURE ) return;
            break;
        case 3:
            if (zend_parse_parameters( arg_count TSRMLS_CC, "szl",
                 &_str, &slen, &cfg, &rargs) == FAILURE ) return;
            break;
        default:
            WRONG_PARAM_COUNT;
    }


    //make sure the RB_RET_WORD will be returned.
    rargs |= FRISO_RET_WORD;

    friso_config_t config = NULL, nconfig = NULL;

    //check and initialize the friso.
    if ( Z_TYPE_P(cfg) != IS_NULL )
    {
        nconfig = friso_new_config();
        memcpy(nconfig, friso_globals.config, sizeof(friso_config_entry));

        //check the new setting.
        cfgArr = Z_ARRVAL_P(cfg);

		ZEND_HASH_FOREACH_KEY_VAL(cfgArr, num_key, key, setting)
		{
            if ( strcmp(ZSTR_VAL(key), "kpuncs") == 0 )
            {
				// memcpy(nconfig->kpuncs, val->value.str->val, val->value.str->len);
                memcpy(nconfig->kpuncs, Z_STRVAL_P(setting), Z_STRLEN_P(setting));
				nconfig->kpuncs[Z_STRLEN_P(setting)] = '\0';

				//php_printf("key : %s => %s, len : %ld", ZSTR_VAL(key), Z_STRVAL_P(setting), Z_STRLEN_P(seting));
				//php_printf("\n");
            } else {
				//php_printf("key : %s => %ld ", ZSTR_VAL(key), Z_LVAL_P(setting));
				//php_printf("\n");
                //convert_to_long_ex(val);
                if ( strcmp(ZSTR_VAL(key), "max_len") == 0 )
                    nconfig->max_len = (ushort_t) Z_LVAL_P(setting);

               else if ( strcmp(ZSTR_VAL(key), "r_name") == 0 )
                    nconfig->r_name = (ushort_t) Z_LVAL_P(setting);

               else if ( strcmp(ZSTR_VAL(key), "mix_len") == 0 )
                   nconfig->mix_len = (ushort_t) Z_LVAL_P(setting);

               else if ( strcmp(ZSTR_VAL(key), "lna_len") == 0 )
                   nconfig->lna_len = (ushort_t) Z_LVAL_P(setting);

               else if ( strcmp(ZSTR_VAL(key), "add_syn") == 0 )
                   nconfig->add_syn = (ushort_t) Z_LVAL_P(setting);

               else if ( strcmp(ZSTR_VAL(key), "clr_stw") == 0 )
                   nconfig->clr_stw = (ushort_t) Z_LVAL_P(setting);

               else if ( strcmp(ZSTR_VAL(key), "add_syn") == 0 )
                   nconfig->add_syn = (ushort_t) Z_LVAL_P(setting);

               else if ( strcmp(ZSTR_VAL(key), "keep_urec") == 0 )
                   nconfig->keep_urec = (ushort_t) Z_LVAL_P(setting);

               else if ( strcmp(ZSTR_VAL(key), "spx_out") == 0 )
                   nconfig->spx_out = (ushort_t) Z_LVAL_P(setting);

               else if ( strcmp(ZSTR_VAL(key), "nthreshold") == 0 )
                   nconfig->nthreshold = (uint_t) Z_LVAL_P(setting);

               else if ( strcmp(ZSTR_VAL(key), "mode") == 0 )
                   friso_set_mode(nconfig, (friso_mode_t)(Z_LVAL_P(setting)));

               else if ( strcmp(ZSTR_VAL(key), "en_sseg") == 0 )
                   nconfig->en_sseg = (ushort_t) Z_LVAL_P(setting);

               else if ( strcmp(ZSTR_VAL(key), "st_minl") == 0)
                   nconfig->st_minl = (ushort_t) Z_LVAL_P(setting);
            }
		} ZEND_HASH_FOREACH_END();
    }


    array_init(&ret);
    config = ( nconfig == NULL ) ? friso_globals.config : nconfig;

    //create a new friso task.
    friso_task_t task;
    task 	= friso_new_task();
    idx 	= 0;
    friso_set_text(task, _str);

	// to prevent segfault error when dic file not configure correct
	if (friso_globals.friso->dic == NULL) {
		zend_throw_exception(zend_exception_get_default(TSRMLS_C), 
				"[Error] can not load dictionry with lex_dir from ini file, please check the friso.ini", 0 TSRMLS_CC);

        RETURN_BOOL(0);
	}

    while ( config->next_token( friso_globals.friso, config, task ) != NULL )
    {
        array_init(&item);
        add_assoc_string(&item, "word", task->token->word);

        //check the append of type
        if ( (rargs & FRISO_RET_TYPE) != 0 )
            add_assoc_long(&item, "type", task->token->type);

        if ( (rargs & FRISO_RET_LEN) != 0 )
            add_assoc_long(&item, "len", task->token->length);

        if ( (rargs & FRISO_RET_RLEN) != 0 )
            add_assoc_long(&item, "rlen", task->token->rlen);

        if ( (rargs & FRISO_RET_OFF) != 0 )
            add_assoc_long(&item, "off", task->token->offset);

        if ( (rargs & FRISO_RET_POS) != 0 )
            add_assoc_string(&item, "pos", &(task->token->pos));

        //append the sub result.
        add_index_zval( &ret, idx++, &item );
	}

    //free the friso task.
    friso_free_task(task);
    if ( nconfig != NULL ) friso_free_config(nconfig);

	*(return_value) = ret;
}
/* }}} */


/* {{{ proto string friso_version()
   Return the current version of Friso. */
PHP_FUNCTION(friso_version)
{
    RETURN_STRINGL(FRISO_VERSION, strlen(FRISO_VERSION));
}
/* }}} */


/* {{{ proto string friso_charset()
   Return the current charset of friso. */
PHP_FUNCTION(friso_charset)
{
    char *charset = friso_globals.friso->charset == FRISO_UTF8 ? "UTF-8" : "GBK";
    RETURN_STRINGL(charset, strlen(charset));
}
/* }}} */


/* {{{ proto bool friso_dic_exist(long type, string str)
   Return a bool to confirm that the given str is a word in a specified dictionary. */
PHP_FUNCTION(friso_dic_exist)
{
    char *word = NULL;
    size_t wlen;
    long type;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ls", &type, &word, &wlen) == FAILURE) {
        return;
    }

    if ( friso_globals.friso->dic == NULL ) {
        RETURN_BOOL(0);
	}

    if ( type < 0 || type >= __FRISO_LEXICON_LENGTH__ )
        type = __LEX_CJK_WORDS__;

    wlen = friso_dic_match( friso_globals.friso->dic, type, word );

    RETURN_BOOL(wlen);
}
/* }}} */


/* {{{ proto array friso_dic_get(long type, string str)
   Return a array contains all the information of the given word.*/
PHP_FUNCTION(friso_dic_get)
{
    char *word = NULL;
    size_t wlen;
    long type;
    zval entry;
    lex_entry_t e;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ls", &type, &word, &wlen) == FAILURE) {
        return;
    }

    //check the dictionary
    if ( friso_globals.friso->dic == NULL )
        RETURN_BOOL(0);

    array_init( &entry );

    if ( type < 0 || type >= __FRISO_LEXICON_LENGTH__ ) {
        type = __LEX_CJK_WORDS__;
    }

	// php_printf(" type : %ld, word %s \n", type, word);
    e = friso_dic_get( friso_globals.friso->dic, type, word );
    if ( e != NULL ) {
        add_assoc_long( &entry, "length", e->length);
        add_assoc_long( &entry, "freq", e->fre);
        *( return_value ) = entry;
        return;
    }

    RETURN_BOOL(0);
}
/* }}} */


/* {{{ proto long friso_utf8_bytes(string str)
   Return the bytes that the utf-8 char takes.*/
PHP_FUNCTION(friso_utf8_bytes)
{
    char *word = NULL;
    size_t wlen, _bytes;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &word, &wlen) == FAILURE) {
        return;
    }

    if ( word == NULL ) RETURN_LONG(0);
    _bytes = get_utf8_bytes( word[0] );

    RETURN_LONG(_bytes);
}
/* }}} */


/* {{{ proto long friso_utf8_ucode(string str)
   Return the unicode of the given utf-8 char.*/
PHP_FUNCTION(friso_utf8_ucode)
{
    char *word = NULL;
    size_t wlen, _ucode;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &word, &wlen) == FAILURE) {
        return;
    }

    _ucode = get_utf8_unicode( word );

    RETURN_LONG(_ucode);
}
/* }}} */


/* {{{ proto string friso_ucode_utf8(long ucode)
   Return char that the a unicode pointed to.*/
PHP_FUNCTION(friso_ucode_utf8)
{
    unsigned long *ucode = NULL;
    size_t _bytes;
    char word[7];

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &ucode ) == FAILURE) {
        return;
    }

    _bytes = unicode_to_utf8( ( size_t ) ucode, word );
    word[_bytes] = '\0';

    RETURN_STRINGL( word, _bytes );
}
/* }}} */


/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
