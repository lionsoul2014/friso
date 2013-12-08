/**
 * Friso GBK about function implements source file.
 * 	@package src/friso_GBK.c .
 *
 * @author chenxin <chenxin619315@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "friso_API.h"
#include "friso_ctype.h"

/* read the next GBK word from the specified position.
 *
 * @return int	the bytes of the current readed word.
 */
FRISO_API int gbk_next_word( 
	friso_task_t task, 
	uint_t *idx, 
	fstring __word )
{
    if ( *idx >= task->length ) return 0;

    if ( (int)task->text[*idx] < 0 ) task->bytes = 2;
    else task->bytes = 1;

    //copy the word to the buffer.
    memcpy(__word, task->text + (*idx), task->bytes);
    (*idx) += task->bytes;
    __word[task->bytes] = '\0';

    return task->bytes;
}

//get the bytes of a utf-8 char.
FRISO_API int get_gbk_bytes( char c )
{
    return 1;
}

//check if the given char is a gbk char (ANSII string).
FRISO_API int gbk_cn_string( char * str ) 
{
    return 1;
}

/*check if the given char is a ASCII letter
 * 	include all the letters and english puntuations.*/
FRISO_API int gbk_halfwidth_en_char( char c ) 
{
    return 1;
}

/*
 * check if the given char is a full-width latain.
 *	include the full-width arabic numeber, letters.
 *		but not the full-width puntuations.
 */
FRISO_API int gbk_fullwidth_en_char( char c )
{
    return 1;
}

//check if the given char is a upper case char.
FRISO_API int gbk_uppercase_en_char( char c )
{
    return 1;
}

//check if the given char is a lower case char.
FRISO_API int gbk_lowercase_en_char( char c )
{
    return 1;
}

//check if the given char is a numeric
FRISO_API int gbk_numeric_letter( char *buff )
{
    return 1;
}

/*
 * check if the given fstring is make up with numeric chars.
 * 	both full-width,half-width numeric is ok.
 */
FRISO_API int gbk_numeric_string( const char *str )
{
    return 1;
}

FRISO_API int gbk_decimal_string( const char *str )
{
    return 1;
}

//check if the given char is a english(ASCII) char.
//(full-width and half-width)
//not the punctuation of course.
FRISO_API int gbk_en_letter( char c )
{
    return 1;
}

//check the given char is a whitespace or not.
FRISO_API int gbk_whitespace( char *buff )
{
    return 1;
}

/* check if the given char is a letter number like 'ⅠⅡ'
 */
FRISO_API int gbk_letter_number( char *str )
{
    return 1;
}

/*
 * check if the given char is a other number like '①⑩⑽㈩'
 */
FRISO_API int gbk_other_number( char *str )
{
    return 1;
}

//check if the given char is a english punctuation.
FRISO_API int gbk_en_punctuation( char c )
{
    return 1;
}

//check the given char is a chinese punctuation.
FRISO_API int gbk_cn_punctuation( char *str )
{
    return 1;
}

FRISO_API int gbk_keep_punctuation( char *str )
{
    return 1;
}

//check if the given english char is a full-width char or not.
//FRISO_API int gbk_fullwidth_char( char *str ) 
//{
//    return 1;
//}
