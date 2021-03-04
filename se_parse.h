/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_SE_SE_PARSE_H_INCLUDED
# define YY_SE_SE_PARSE_H_INCLUDED
/* Debug traces.  */
#ifndef SEDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define SEDEBUG 1
#  else
#   define SEDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define SEDEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined SEDEBUG */
#if SEDEBUG
extern int sedebug;
#endif
/* "%code requires" blocks.  */
#line 8 "se_parse.y"

#include "se.h"

#line 61 "se_parse.h"

/* Token kinds.  */
#ifndef SETOKENTYPE
# define SETOKENTYPE
  enum setokentype
  {
    SEEMPTY = -2,
    SEEOF = 0,                     /* "end of file"  */
    SEerror = 256,                 /* error  */
    SEUNDEF = 257,                 /* "invalid token"  */
    SE_LPAREN = 258,               /* SE_LPAREN  */
    SE_RPAREN = 259,               /* SE_RPAREN  */
    SE_TRUE = 260,                 /* SE_TRUE  */
    SE_FALSE = 261,                /* SE_FALSE  */
    SE_INT = 262,                  /* SE_INT  */
    SE_STRING = 263,               /* SE_STRING  */
    SE_ERROR = 264                 /* SE_ERROR  */
  };
  typedef enum setokentype setoken_kind_t;
#endif

/* Value type.  */
#if ! defined SESTYPE && ! defined SESTYPE_IS_DECLARED
union SESTYPE
{
#line 29 "se_parse.y"

  char *str_value;
  long int_value;
  se_t *e_value;

#line 93 "se_parse.h"

};
typedef union SESTYPE SESTYPE;
# define SESTYPE_IS_TRIVIAL 1
# define SESTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined SELTYPE && ! defined SELTYPE_IS_DECLARED
typedef struct SELTYPE SELTYPE;
struct SELTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define SELTYPE_IS_DECLARED 1
# define SELTYPE_IS_TRIVIAL 1
#endif



int separse (void *scanner, se_t **result);
/* "%code provides" blocks.  */
#line 18 "se_parse.y"


typedef enum {
  SE_PARSE_OK,
  SE_PARSE_ERROR_SYNTAX,
  SE_PARSE_ERROR_MEM
} se_parse_t;

se_parse_t se_parse_string( se_t **result, const char *s );

#line 130 "se_parse.h"

#endif /* !YY_SE_SE_PARSE_H_INCLUDED  */
