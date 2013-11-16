/*
 * fstring handle mode test program.
 *
 * @author	chenxin <chenxin619315@gmail.com>
 */
#include "friso_API.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char **args ) {

    fstring str = "康熙字典部首, 符号和标点, 统一表意符号扩展 A ,CJK㈩兼Ⅱ容形式⑩.";
    char word[4];
    int bytes, t, j, length = strlen( str );
    string_buffer_t sb = new_string_buffer();

    printf("str=%s, length=%d\n", str, length );


    for ( t = 0; t < length; t += bytes ) {
	bytes = get_utf8_bytes( *(str + t) );
	if ( bytes == 0 ) continue;
	for ( j = 0; j < bytes; j++ )
	    word[j] = *(str + t + j );
	word[j] = '\0';
	string_buffer_append( sb, word );
	printf("word=%s\n", word );
    }

    printf("length=%d, buffer=%s\n", sb->length, sb->buffer );
    string_buffer_remove( sb, 0, 3 );
    printf("length=%d, buffer=%s\n", sb->length, sb->buffer );
    string_buffer_remove( sb, 0, 3 );
    printf("length=%d, buffer=%s\n", sb->length, sb->buffer );
    string_buffer_remove( sb, sb->length - 3, 6 );
    sb = string_buffer_trim( sb );
    printf("length=%d, buffer=%s\n", sb->length, string_buffer_devote( sb ) );

    //00011110 - yuan ma
    //11100001 - fa ma
    //11100010 - bu ma

    return 0;
}
