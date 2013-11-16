/**
 * friso fstring split function implments defined
 * 	in header file friso_API.h . 
 *
 * @author chenxin <chenxin619315@gmail.com>
 * @date   2013-06-08
 */
#include <stdlib.h>
#include <string.h>
#include "friso_API.h"

/**
 * create a new string_split_entry.
 *
 * @param	source
 * @return	string_split_t;	
 */
FRISO_API string_split_t new_string_split( 
		fstring delimiter, 
		fstring source ) 
{
	string_split_t e = ( string_split_t ) 
		FRISO_MALLOC( sizeof( string_split_entry ) );
	if ( e == NULL ) {
		___ALLOCATION_ERROR___;
	}

	e->delimiter = delimiter;
	e->delLen = strlen(delimiter);
	e->source = source;
	e->srcLen = strlen(source);
	e->idx = 0;

	return e;
}

FRISO_API void string_split_reset( 
		string_split_t sst, 
		fstring delimiter, 
		fstring source ) 
{
	sst->delimiter = delimiter;
	sst->delLen = strlen(delimiter);
	sst->source = source;
	sst->srcLen = strlen(source);	
	sst->idx = 0;
}

FRISO_API void string_split_set_source( 
		string_split_t sst, fstring source ) 
{
	sst->source = source;
	sst->srcLen = strlen(source);
	sst->idx = 0;
}

FRISO_API void string_split_set_delimiter( 
		string_split_t sst, fstring delimiter ) 
{
	sst->delimiter = delimiter;
	sst->delLen = strlen( delimiter );
	sst->idx = 0;
}

FRISO_API void free_string_split( string_split_t sst ) 
{
	FRISO_FREE(sst);
}

/**
 * get the next split fstring, and copy the 
 * 	splited fstring into the __dst buffer . 
 *
 * @param	string_split_t
 * @param	__dst
 * @return	fstring (NULL if reach the end of the source 
 * 		or there is no more segmentation)
 */
FRISO_API fstring string_split_next( 
		string_split_t sst, fstring __dst) 
{
	uint_t i, _ok;
	fstring _dst = __dst;

	//check if reach the end of the fstring
	if ( sst->idx >= sst->srcLen ) return NULL;

	while ( 1 ) 
	{
		_ok = 1;
		for ( i = 0; i < sst->delLen 
				&& (sst->idx + i < sst->srcLen); i++ ) 
		{
			if ( sst->source[sst->idx+i] != sst->delimiter[i] ) 
			{
				_ok = 0;
				break;
			}
		}	

		//find the delimiter here,
		//break the loop and self plus the sst->idx, then return the buffer . 
		if ( _ok == 1 ) {
			sst->idx += sst->delLen;
			break;
		}

		//coy the char to the buffer
		*_dst++ = sst->source[sst->idx++];
		//check if reach the end of the fstring
		if ( sst->idx >= sst->srcLen ) break;
	}

	*_dst = '\0';
	return _dst;
}
