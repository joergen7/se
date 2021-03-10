/*
 * S-Expression Parser
 *
 * Copyright 2021 Jörgen Brandt <joergen@cuneiform-lang.org>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

%option yylineno
%option noyywrap
%option nounput
%option nodefault
%option reentrant
%option bison-bridge
%option bison-locations
%option prefix="se"

%{
#include "se.tab.hh"
static void unescape( char* s );
%}

%%

"("                     { return se::parser::token::LPAREN; }
")"                     { return se::parser::token::RPAREN; }
"#t"                    { yylval->bool_val = true; return se::parser::token::TRUE; }
"#f"                    { yylval->bool_val = false; return se::parser::token::FALSE; }
"-"?[1-9][0-9]*|"0"     { yylval->int_val = atol( yytext ); return se::parser::token::INT; }
\"([^\"\\]|\\[\"\\])*\" { unescape( yytext ); yylval->str_val = new std::string { yytext }; return se::parser::token::STRING; }
[ \r\t]                 {}
\n                      { ++yylloc->begin.line; }
.                       { return se::parser::token::SEUNDEF; }


%%

static void unescape( char* s )
{
  size_t len = strlen( s );
  size_t i = 0;
  size_t j = 1;
  while( j < len-1 )
  {
    if( s[j] == '\\' )
      ++j;
    s[i] = s[j];
    ++i;
    ++j;
  }
  s[i] = '\0';
}
