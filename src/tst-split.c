#include <stdio.h>
#include <stdlib.h>
#include "friso_API.h"

/**
 * friso fstring split test program .
 *
 * @author chenxin<chenxin619315@gmail.com>
 * @date   2013-06-09
 */

int main ( int argc, char **args ) 
{
    fstring source = ",I am a chinese,,my name is chenxin,and i am the author of friso,bug report email chenxin619315@gmail.com,qq:1187582057";	     
    char buffer[128];
    string_split_t split = new_string_split(",", source );

    printf("sst->idx=%d\n", split->idx);
    printf("sst->srcLen=%d\n", split->srcLen);
    printf("sst->delLen=%d\n", split->delLen);

    while ( string_split_next(split, buffer) != NULL) {
	printf("buffer:%s\n", buffer);
    }

    free_string_split(split);

    return 0;
}

