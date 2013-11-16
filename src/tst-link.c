/*
 * link list test programe.
 * 
 * @author	chenxin
 * @email	chenxin619315@gmail.com
 */
#include "friso_API.h"

#include <stdio.h>
#include <stdlib.h>

int main( int argc, char **args ) {

    friso_link_t link;
    fstring keys[] = {
	"chenmanwen", "yangqinghua",
	"chenxin", "luojiangyan", "xiaoyanzi", "bibi",
	"zhangrenfang", "yangjian",
	"liuxiao", "pankai",
	"chenpei", "liheng", "zhangzhigang", "zhgangyishao", "yangjiangbo",
	"caizaili", "panpan", "xiaolude", "yintanwen"
    };
    int j, len = sizeof( keys ) / sizeof( fstring );

    link = new_link_list();

    //print the size of the link
    printf("size=%d\n", link->size );

    for ( j = 0; j < len; j++ ) {
	//link_add( link, keys[j] );
	link_list_add_last( link, keys[j] );
    }

    printf("size=%d\n", link->size );

    for ( j = 0; j < len / 2; j++ ) {
	//printf("idx=%d, remove %s\n", j, ( fstring ) link_remove( link, 0 ) );
	printf("idx=%d, remove %s\n", j, ( fstring ) link_list_remove_first( link ) );
    }

    printf("size=%d\n", link->size );

    //clear all the nodes
    link_list_clear( link );
    printf("size=%d, head->next->value=%s\n", link->size, ( fstring ) link->head->next->value );

    free_link_list( link );

    return 0;
}
