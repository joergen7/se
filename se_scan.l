%option noyywrap
%option nodefault
%option prefix="se"
%option yylineno
%option reentrant
%option bison-bridge
%option bison-locations

%{
#include "se_parse.h"
typedef SESTYPE YYSTYPE;
typedef SELTYPE YYLTYPE;
static void de_escape( char* s );
%}


%%

"("                     { return SE_LPAREN; }
")"                     { return SE_RPAREN; }
"#t"                    { return SE_TRUE; }
"#f"                    { return SE_FALSE; }
"-"?[1-9][0-9]*|"0"     { yylval->int_value = atol( yytext ); return SE_INT; }
\"([^\"\\]|\\[\"\\])*\" { de_escape( yytext ); yylval->str_value = strdup( yytext ); return SE_STRING; }
[ \n\r\t]               {}
[^ \n\r\t\(\)]*         { return SE_ERROR; }

%%

static void de_escape( char* s ) {
  size_t len = strlen( s );
  size_t i = 0;
  size_t j = 1;
  while( j < len-1 ) {
    if( s[j] == '\\' )
      ++j;
    s[i] = s[j];
    ++i;
    ++j;
  }
  s[i] = '\0';
}

