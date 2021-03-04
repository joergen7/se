%locations
%define api.prefix {se}
%define api.pure full

%lex-param   {void *scanner}
%parse-param {void *scanner} {se_t **result}

%code requires {
#include "se.h"
}

%{
#include "se_parse.h"
#include "se_scan.h"
static void seerror( YYLTYPE *loc, yyscan_t scanner, se_t **result, const char *msg );
%}

%code provides {

typedef enum {
  SE_PARSE_OK,
  SE_PARSE_ERROR_SYNTAX,
  SE_PARSE_ERROR_MEM
} se_parse_t;

se_parse_t se_parse_string( se_t **result, const char *s );
}

%union {
  char *str_value;
  long int_value;
  se_t *e_value;
}

%type <e_value> e e_lst



%token SE_LPAREN
%token SE_RPAREN
%token SE_TRUE
%token SE_FALSE
%token <int_value> SE_INT
%token <str_value> SE_STRING
%token SE_ERROR

%%

script : e { *result = $1; }

e : SE_TRUE                   { $$ = se_bool( true ); }
  | SE_FALSE                  { $$ = se_bool( false ); }
  | SE_INT                    { $$ = se_int( $1 ); }
  | SE_STRING                 { $$ = se_str( $1 ); }
  | SE_LPAREN e_lst SE_RPAREN { $$ = $2; }
  ;

e_lst :         { $$ = se_nil(); *result = $$; }
      | e e_lst { $$ = se_cons( $1, $2 ); *result = $$; }
      ;

%%

static void seerror( YYLTYPE *loc, yyscan_t scanner, se_t **result, const char *msg ) {
  ( void )loc;
  ( void )scanner;
  ( void )result;
  ( void )msg;
}

se_parse_t se_parse_string( se_t **result, const char *s ) {
  yyscan_t scanner;
  selex_init( &scanner );
  se_scan_string( s, scanner );
  seset_lineno( 1, scanner );
  int r = yyparse( scanner, result );
  selex_destroy( scanner );

  if( r == 1 )
    return SE_PARSE_ERROR_SYNTAX;

  if( r != 0 )
    return SE_PARSE_ERROR_MEM;

  return SE_PARSE_OK;
}