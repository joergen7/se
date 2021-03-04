#include <stdlib.h>
#include <stdio.h>
#include "se_parse.h"

int main( void ) {

  char *s = "(1 #t (\"blub\"))";
  se_t *r = NULL;

  switch( se_parse_string( &r, s ) ) {
    
    case SE_PARSE_OK :
      break;

    case SE_PARSE_ERROR_SYNTAX :
      printf( "syntax error\n" );
      exit( EXIT_FAILURE );

    case SE_PARSE_ERROR_MEM :
      printf( "not enough memory\n" );
      exit( EXIT_FAILURE );
  }

  se_println( r );
  se_free( r );

  return EXIT_SUCCESS;
}