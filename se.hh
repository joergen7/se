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

#ifndef __se__
#define __se__

#include <memory>
#include <string>
#include <stdexcept>

namespace se
{
  class exp
  {
    public:
      exp( void ) = default;
      exp( const exp& other ) = default;
      exp( exp& other ) = default;
      virtual exp& operator=( const exp& other ) = default;
      virtual exp& operator=( exp&& other ) = default;
      virtual ~exp( void ) = default;
      virtual std::string format( void ) = 0;
  };

  class bool_exp : public exp
  {
    public:
      bool_exp( bool value );
      virtual std::string format( void );

    private:
      bool value;
  };

  class int_exp : public exp
  {
    public:
      int_exp( long value );
      virtual std::string format( void );
    private:
      long value;
  };

  class str_exp : public exp
  {
    public:
      str_exp( const std::string& value );
      virtual std::string format( void );

    private:
      std::string value;
  };

  class nil_exp : public exp
  {
    public:
      virtual std::string format( void );
  };

  class cons_exp : public exp
  {
    public:
      cons_exp( std::unique_ptr<exp> car, std::unique_ptr<exp> cdr );
      virtual std::string format( void );
      std::unique_ptr<exp> rm_car( void );
      std::unique_ptr<exp> rm_cdr( void );

    private:
      std::unique_ptr<exp> car;
      std::unique_ptr<exp> cdr;
  };

  class parse_error : public std::runtime_error
  {
    public:
      parse_error( int line, const std::string& msg );
    private:
      const int line;
      const std::string msg;
  };

  std::unique_ptr<exp> parse( const std::string& s );
}

#endif