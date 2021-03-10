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

#include "se.hh"

static std::string escape( const std::string& s );
static void escape_char( std::string& s, char c );

namespace se
{

  bool_exp::bool_exp( bool value ) :
  value { value }
  {}

  std::string bool_exp::format( void )
  {
    return value ? "#t" : "#f";
  }

  int_exp::int_exp( long value ) :
  value { value }
  {}

  std::string int_exp::format( void )
  {
    return std::to_string( value );
  }

  str_exp::str_exp( const std::string& value ) :
  value { value }
  {}

  std::string str_exp::format( void )
  {
    return "\""+escape( value )+"\"";
  }

  std::string nil_exp::format( void )
  {
    return "()";
  }

  cons_exp::cons_exp( std::unique_ptr<exp> car, std::unique_ptr<exp> cdr ) :
  car { std::move( car ) },
  cdr { std::move( cdr ) }
  {}

  std::string cons_exp::format( void )
  {
    std::string prefix { "("+car->format() };

    if( typeid( *cdr ) == typeid( nil_exp ) )
      return prefix+")";

    if( typeid( *cdr ) == typeid( cons_exp ) ) {
      std::string s { cdr->format() };
      return prefix+" "+s.substr( 1, std::string::npos );
    }

    return prefix+" . "+cdr->format()+")";
  }

  std::unique_ptr<exp> cons_exp::rm_car( void ) {
    return std::move( car );
  }

  std::unique_ptr<exp> cons_exp::rm_cdr( void ) {
    return std::move( cdr );
  }

  parse_error::parse_error( int line, const std::string& msg ) :
  std::runtime_error { "line "+std::to_string( line )+": "+msg },
  line               { line },
  msg                { msg }
  {}
}

static std::string escape( const std::string& s )
{
  std::string s1 { s };

  escape_char( s1, '\\' );
  escape_char( s1, '"' );

  return s1;
}

static void escape_char( std::string& s, char c )
{
  std::string t {'\\', c, '\0'};

  size_t p0 { 0 };
  while( true )
  {
    const size_t p1 { s.find( c, p0 ) };

    if( p1 == std::string::npos )
      break;

    s.replace( p1, 1, t );

    p0 = p1+2;
  }
}