/*
 * dynamatic array test program.
 *
 * @author	chenxin
 * @email	chenxin619315@gmail.com
 */
#include "friso_API.h"
 
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char **args ) {
	
	//create a new array list.
	friso_array_t array = new_array_list();	
	fstring keys[] = {
		"chenmanwen", "yangqinghua",
		"chenxin", "luojiangyan", "xiaoyanzi", "bibi",
		"zhangrenfang", "yangjian",
		"liuxiao", "pankai",
		"chenpei", "liheng", "zhangzhigang", "zhgangyishao", "yangjiangbo",
		"caizaili", "panpan", "xiaolude", "yintanwen"
	};
	int j, idx = 2, len = sizeof( keys ) / sizeof( fstring );

	for ( j = 0; j < len; j++ ) {
		array_list_add( array, keys[j] );
	}

	printf("length=%d, allocations=%d\n", array->length, array->allocs );
	array_list_trim( array );
	printf("after tirm length=%d, allocations=%d\n", array->length, array->allocs );
	printf("idx=%d, value=%s\n", idx, ( fstring ) array_list_get( array, idx ) );

	printf("\nAfter set %dth item.\n", idx );
	array_list_set( array, idx, "chenxin__" );
	printf("idx=%d, value=%s\n", idx, ( fstring ) array_list_get( array, idx ) );

	printf("\nAfter remove %dth item.\n", idx );
	array_list_remove( array, idx );
	printf("length=%d, allocations=%d\n", array->length, array->allocs );
	printf("idx=%d, value=%s\n", idx, ( fstring ) array_list_get( array, idx ) );

	printf("\nInsert a item at %dth\n", idx );
	array_list_insert( array, idx, "*chenxin*" );
	printf("idx=%d, value=%s\n", idx, ( fstring ) array_list_get( array, idx ) );

	free_array_list( array );

	return 0;
}
