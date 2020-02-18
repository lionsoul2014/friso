/**
 * friso fstring split test program .
 *
 * @author  lionsoul<chenxin619315@gmail.com>
*/

#include "friso_API.h"
#include <stdio.h>
#include <stdlib.h>

int main ( int argc, char **args ) 
{
    fstring source = ",I am a chinese,,my name is Lion,and i am the author of friso,bug report email chenxin619315@gmail.com,qq:1187582057";         
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
