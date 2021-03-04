#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "se.h"

static void se_print_list( se_t *e );
static void se_print_str( se_t *e );

se_t *se_bool( bool value ) {
  se_t *r = malloc( sizeof( se_t ) );
  r->type = SE_TYPE_BOOL;
  r->data.bool_value = value;
  return r;
}

se_t *se_int( long value ) {
  se_t *r = malloc( sizeof( se_t ) );
  r->type = SE_TYPE_INT;
  r->data.int_value = value;
  return r;
}

se_t *se_str( char *value ) {
  se_t *r = malloc( sizeof( se_t ) );
  r->type = SE_TYPE_STR;
  r->data.str_value = value;
  return r;
}

se_t *se_nil() {
  se_t *r = malloc( sizeof( se_t ) );
  r->type = SE_TYPE_NIL;
  return r;
}

se_t *se_cons( se_t *car, se_t *cdr )
 {
  se_t *r = malloc( sizeof( se_t ) );
  r->type = SE_TYPE_CONS;
  r->data.cons_value[0] = car;
  r->data.cons_value[1] = cdr;
  return r;
}

void se_free( se_t *e ) {

  switch( e->type ) {

    case SE_TYPE_BOOL :
    case SE_TYPE_INT :
    case SE_TYPE_NIL :
      free( e );
      break;

    case SE_TYPE_STR :
      free( e->data.str_value );
      free( e );
      break;

    case SE_TYPE_CONS :
      se_free( e->data.cons_value[0] );
      se_free( e->data.cons_value[1] );
      free( e );
      break;
  }
}

void se_println( se_t *e ) {
  se_print( e );
  printf( "\n" );
}

void se_print( se_t *e ) {

  switch( e->type ) {

    case SE_TYPE_BOOL :
      if( e->data.bool_value )
        printf( "#t" );
      else
        printf( "#f" );
      break;

    case SE_TYPE_INT :
      printf( "%ld", e->data.int_value );
      break;

    case SE_TYPE_STR :
      se_print_str( e );
      break;

    case SE_TYPE_NIL :
    case SE_TYPE_CONS :
      se_print_list( e );
      break;
  }
}

static void se_print_list( se_t *e ) {

  printf( "(" );

  bool comma = false;
  se_t *e1 = e;
  while( e1->type != SE_TYPE_NIL ) {

    if( comma )
      printf( " " );
    comma = true;

    se_print( e1->data.cons_value[0] );

    e1 = e1->data.cons_value[1];
  }

  printf( ")" );
}

static void se_print_str( se_t *e ) {

  char *s = e->data.str_value;
  size_t len = strlen( s );

  printf( "\"" );

  for( size_t i = 0; i < len; ++i )
    switch( s[i] ) {

      case '\\' :
        printf( "\\\\" );
        break;

      case '"' :
        printf( "\\\"" );
        break;

      default :
        printf( "%c", s[i] );
        break;
    }

  printf( "\"" );
}