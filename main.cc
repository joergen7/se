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

#include <string>
#include <iostream>
#include "se.hh"

int main( void )
{
  std::string s { "(\"bl\\\"u\\\"b\"\n(\"bla\"))\n" };
 
  std::unique_ptr<se::exp> e { se::parse( s ) };

  std::cout << e->format() << '\n';

  return 0;
}