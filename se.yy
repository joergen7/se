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

%language "C++"
%locations
%define api.namespace {se}
%define api.prefix {se}

%lex-param {yyscan_t scanner}
%parse-param {void* scanner}
%parse-param {std::optional<std::unique_ptr<exp>>& maybe_exp}
%parse-param {std::optional<parse_error>& maybe_error}

%code requires {
#include "se.hh"
}

%code provides {
#define YYSTYPE union se::parser::semantic_type
#define YYLTYPE se::parser::location_type
}

%code top {
#include "se.tab.hh"
#include "se.lex.hh"
}

%union {
  se::exp* exp_val;
  std::string* str_val;
  long int_val;
  bool bool_val;
}

%destructor { delete $$; } <exp_val>
%destructor { delete $$; } <str_val>



%token LPAREN
%token RPAREN
%token <str_val> STRING
%token <int_val> INT
%token <bool_val> TRUE
%token <bool_val> FALSE

%type <exp_val> e e_lst


%%

script : e { maybe_exp.emplace( std::unique_ptr<exp> { $1 } ); }

e : STRING              { $$ = new str_exp( *$1 ); delete $1; }
  | INT                 { $$ = new int_exp( $1 ); }
  | TRUE                { $$ = new bool_exp( $1 ); }
  | FALSE               { $$ = new bool_exp( $1 ); }
  | LPAREN e_lst RPAREN { $$ = $2; }
  ;

e_lst :         { $$ = new nil_exp {}; }
      | e e_lst { $$ = new cons_exp( std::unique_ptr<exp> { $1 }, std::unique_ptr<exp> { $2 } ); }

%%

namespace se
{
  void parser::error( const location_type& loc, const std::string& msg )
  {
    maybe_error.emplace( parse_error { loc.begin.line, msg } );
  }

  std::unique_ptr<exp> parse( const std::string& s ) {
    yyscan_t scanner;
    selex_init( &scanner );
    se_scan_string( s.c_str(), scanner );

    std::optional<std::unique_ptr<exp>> maybe_exp {};
    std::optional<parse_error> maybe_error {};

    parser p { scanner, maybe_exp, maybe_error };
    int r = p.parse();

    selex_destroy( scanner );

    if( r == 1 )
      throw maybe_error.value();

    if( r != 0 )
      throw std::runtime_error( "not enough memory" );

    return std::move( maybe_exp.value() );
  }
}
