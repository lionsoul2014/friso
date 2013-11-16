/**
 * File Explain.
 * 
 * @author	chenxin
 * @see		http://www.webssky.com 
 */
#include "friso_API.h"

#include <stdio.h>

void print_hash_info( friso_hash_t _hash ) {
    printf("info:length=%d, size=%d, facotr=%f, threshold=%d\n", _hash->length, \
	    _hash->size, _hash->factor, _hash->threshold);
} 

int main(int argc, char **argv)
{
    friso_hash_t _hash = new_hash_table();
    char *names[] = {
	"陈满文", "阳清华",
	"陈鑫", "罗江艳",
	"小燕子", "比比",
	"张仁芳", "阳建",
	"陈配", "李恒",
	"张志刚", "张怡少",
	"阳江波", "蔡再利",
	"阳绘章", "尹唐文",
	"谭志鹏", "肖路德",
	"潘凯", "刘潇",
	"马朝辉", "张强",
	"殷美林", "元明清",
	"周安", "郭桥安",
	"刘敏", "黄广华",
	"李胜", "黄海清"
    }; 
    //char *str[] = {"陈鑫", "张仁芳", "比比"};
    char **str = names;
    int j, len = 30;

    print_hash_info( _hash );
    for ( j = 0; j < len; j++) {
	hash_put_mapping( _hash, names[j], names[j] );
    }

    print_hash_info( _hash );

    printf("Press any key to continue.");
    getchar();

    //remove mappings
    for ( j = 0; j < len; j++ ) {
	printf("Exist %s?%2d\n", str[j], hash_exist_mapping( _hash, str[j] ));
	printf("Now, remove %s\n", str[j]);
	hash_remove_mapping( _hash, str[j] );
	printf("Exist %s?%2d\n", str[j], hash_exist_mapping( _hash, str[j] ));
	printf("*********************************\n");
    }

    printf("Press any key to continue.");
    getchar();

    print_hash_info( _hash );
    //free the table
    free_hash_table( _hash, 0 );

    return 0;
}
