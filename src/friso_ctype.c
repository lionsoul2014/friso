/**
 * friso string type check function interface, 
 * 	like english/CJK, full-wdith/half-width, punctuation or not. 
 * @ses	friso_UTF8.c and friso_GBK.c for detail.
 *
 * @author chenxin <chenxin619315@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "friso_ctype.h"
#include "friso_API.h"

/* check if the specified string is a cn string.
 * 
 * @return int (true for cn string or false)
 * */
FRISO_API int friso_cn_string( 
	friso_charset_t charset, 
	friso_task_t task )
{
    if ( charset == FRISO_UTF8 )
	return utf8_cjk_string(task->unicode);
    else if ( charset == FRISO_GBK )
	return gbk_cn_string(task->buffer);
    return 0;
}

//check if the specified word is a whitespace.
FRISO_API int friso_whitespace( 
	friso_charset_t charset, 
	friso_task_t task )
{
    if ( charset == FRISO_UTF8 )
	return utf8_whitespace(task->unicode);
    else if ( charset == FRISO_GBK )
	return gbk_whitespace(task->buffer);
    return 0;
}

//check if the specified word is a english letter.
FRISO_API int friso_en_letter( 
	friso_charset_t charset, 
	friso_task_t task )
{
    if ( charset == FRISO_UTF8 )
	return utf8_en_letter( ( uint_t ) task->text[task->idx]);
    else if ( charset == FRISO_GBK )
	return gbk_en_letter( task->text + task->idx );
    return 0;
}

//check if the specified word is a half-width letter.
//	punctuations are inclued.
FRISO_API int friso_halfwidth_en_char( 
	friso_charset_t charset, 
	friso_task_t task )
{
    if ( charset == FRISO_UTF8 )
	return utf8_halfwidth_en_char(task->unicode);
    else if ( charset == FRISO_GBK )
	return gbk_halfwidth_en_char(task->buffer[0]);
    return 0;
}

//check if the specified word is a full-width letter.
//	full-width punctuations are not included.
FRISO_API int friso_fullwidth_en_char( 
	friso_charset_t charset, 
	friso_task_t task )
{
    if ( charset == FRISO_UTF8 )
	return utf8_fullwidth_en_char( task->unicode );
    else if ( charset == FRISO_GBK )
	return gbk_fullwidth_en_char( task->buffer );
    return 0;
}

//check if the specified word is an english punctuations.
FRISO_API int friso_en_punctuation(
	friso_charset_t charset,
	friso_task_t task )
{
    if ( charset == FRISO_UTF8 )  
	return utf8_en_punctuation( task->unicode );
    else if ( charset == FRISO_GBK ) 
	return gbk_en_punctuation( task->buffer[0] );
    return 0;
}

//check if the specified word ia sn chinese punctuation.
FRISO_API int friso_cn_punctuation( 
	friso_charset_t charset, 
	friso_task_t task )
{
    if ( charset == FRISO_UTF8 )
	return utf8_cn_punctuation( task->unicode );
    else if ( charset == FRISO_GBK )
	return gbk_cn_punctuation( task->buffer );
    return 0;
}

FRISO_API int friso_letter_number( 
	friso_charset_t charset, 
	friso_task_t task )
{
    return 0;
}

FRISO_API int friso_other_number( 
	friso_charset_t charset, 
	friso_task_t task )
{
    return 0;
}

//check if the word is a keep punctuation.
FRISO_API int friso_keep_punctuation( 
	friso_charset_t charset, 
	friso_task_t task )
{
    if ( charset == FRISO_UTF8 )
	return utf8_keep_punctuation( task->buffer );
    else if ( charset == FRISO_GBK )
	return gbk_keep_punctuation( task->buffer );
    return 0;
}

//check if the specified char is en english punctuation.
//	this function is the same as friso_en_punctuation.
FRISO_API int is_en_punctuation( 
	friso_charset_t charset, char c )
{
    if ( charset == FRISO_UTF8 )
	return utf8_en_punctuation( (uint_t) c);
    else if ( charset == FRISO_GBK )
	return gbk_en_punctuation( c );
    return 0;
}

//check the specified string is make up with numeric. 
FRISO_API int friso_numeric_string( 
	friso_charset_t charset, 
	char *buffer )
{
    if ( charset == FRISO_UTF8 )
	return utf8_numeric_string( buffer );
    else if ( charset == FRISO_GBK )
	return gbk_numeric_string( buffer );
    return 0;
}

//check the specified string is a decimal string.
FRISO_API int friso_decimal_string( 
	friso_charset_t charset, char *buffer )
{
    if ( charset == FRISO_UTF8 )
	return utf8_decimal_string( buffer );
    else if ( charset == FRISO_GBK )
	return gbk_decimal_string( buffer );
    return 0;
}

//check if the specified char is english uppercase letter.
//	included full-width and half-width letters.
FRISO_API int friso_uppercase_letter( 
	friso_charset_t charset, 
	friso_task_t task )
{
    if ( charset == FRISO_UTF8 )
	return utf8_uppercase_letter( task->unicode );
    else if ( charset == FRISO_GBK )
	return gbk_uppercase_letter( task->buffer );
    return 0;
}
