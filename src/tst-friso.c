/*
 * Friso test program.
 *     Of couse you can make it a perfect demo for friso.
 * all threads or proccess share the same friso_t,
 *     defferent threads/proccess use defferent friso_task_t.
 * and you could share the friso_config_t if you wish...
 *
 * @author chenxin <chenxin619315@gmail.com>
 */
#include "friso_API.h"
#include "friso.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define __LENGTH__ 15
#define __INPUT_LENGTH__ 20480
#define ___EXIT_INFO___                    \
    println("Thanks for trying friso.");        \
break;

#define ___ABOUT___                    \
    println("+-----------------------------------------------------------+");    \
    println("| friso - a chinese word segmentation writen by c.          |");    \
    println("| bug report email - chenxin619315@gmail.com.               |");    \
    println("| or: visit http://code.google.com/p/friso.                 |");    \
    println("|     java edition for http://code.google.com/p/jcseg       |");    \
    println("| type 'quit' to exit the program.                          |");    \
    println("+-----------------------------------------------------------+");

//read a line from a command line.
static fstring getLine( FILE *fp, fstring __dst ) 
{
    register int c;
    register fstring cs;

    cs = __dst;
    while ( ( c = getc( fp ) ) != EOF ) {
        if ( c == '\n' ) break;
        *cs++ = c; 
    }
    *cs = '\0';

    return ( c == EOF && cs == __dst ) ? NULL : __dst;
}

/*static void printcode( fstring str ) {
  int i,length;
  length = strlen( str );
  printf("str:length=%d\n", length );
  for ( i = 0; i < length; i++ ) {
  printf("%d ", str[i] );
  }
  putchar('\n');
  }*/

int main(int argc, char **argv) 
{

    clock_t s_time, e_time;
    char line[__INPUT_LENGTH__] = {0};
    int i;
    fstring __path__ = NULL, mode = NULL;

    friso_t friso;
    friso_config_t config;
    friso_task_t task;

    //get the lexicon directory
    for ( i = 0; i < argc; i++ ) {
        if ( strcasecmp( "-init", argv[i] ) == 0 ) {
            __path__ = argv[i+1];
        }
    }
    if ( __path__ == NULL ) {
        println("Usage: friso -init lexicon path");
        exit(0);
    }

    s_time = clock();

    //initialize
    friso = friso_new();
    config = friso_new_config();
    /*friso_dic_t dic = friso_dic_new();
      friso_dic_load_from_ifile( dic, __path__, __LENGTH__ );
      friso_set_dic( friso, dic );
      friso_set_mode( friso, __FRISO_COMPLEX_MODE__ );*/
    if ( friso_init_from_ifile(friso, config, __path__) != 1 ) {
        printf("fail to initialize friso and config.\n");
        goto err;
    }

    switch ( config->mode ) {
    case __FRISO_SIMPLE_MODE__:
        mode = "Simple";
        break;
    case __FRISO_COMPLEX_MODE__:
        mode = "Complex";
        break;
    case __FRISO_DETECT_MODE__:
        mode = "Detect";
        break;
    }

    //friso_set_mode( config, __FRISO_DETECT_MODE__ );
    //printf("clr_stw=%d\n", friso->clr_stw);
    //printf("match c++?%d\n", friso_dic_match( friso->dic, __LEX_ENPUN_WORDS__, "c++" ));
    //printf("match(研究)?%d\n", friso_dic_match( friso->dic, __LEX_CJK_WORDS__, "研究"));

    e_time = clock();

    printf("Initialized in %fsec\n", (double) ( e_time - s_time ) / CLOCKS_PER_SEC );
    printf("Mode: %s\n", mode);
    printf("+-Version: %s (%s)\n", friso_version(), friso->charset == FRISO_UTF8 ? "UTF-8" : "GBK" );
    ___ABOUT___;

    //set the task.
    task = friso_new_task();

    while ( 1 ) {
        print("friso>> ");
        getLine( stdin, line );
        //exit the programe
        if ( strcasecmp( line, "quit" ) == 0 ) {
            ___EXIT_INFO___
        }

        //for ( i = 0; i < 1000000; i++ ) {
        //set the task text.
        friso_set_text( task, line );
        println("分词结果:");

        s_time = clock();
        while ( ( config->next_token( friso, config, task ) ) != NULL ) {
            //printf("%s[%d, %d, %d] ", task->token->word, 
            //        task->token->offset, task->token->length, task->token->rlen );
            printf("%s ", task->token->word );
        }
        //}
        e_time = clock();
        printf("\nDone, cost < %fsec\n", ( (double)(e_time - s_time) ) / CLOCKS_PER_SEC );

    }

    friso_free_task( task );

    //error block.
err:
    friso_free_config(config);
    friso_free(friso);
    

    return 0;
}
