/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    KEYWORD = 258,                 /* KEYWORD  */
    IDENTIFIER = 259,              /* IDENTIFIER  */
    CONDWITHBRAC = 260,            /* CONDWITHBRAC  */
    FUNCCALL = 261,                /* FUNCCALL  */
    CONSTANT = 262,                /* CONSTANT  */
    DOUBLE_CONSTANT = 263,         /* DOUBLE_CONSTANT  */
    STRING = 264,                  /* STRING  */
    ARITH_ASSIGN_OP = 265,         /* ARITH_ASSIGN_OP  */
    ARITH_OP = 266,                /* ARITH_OP  */
    RELOP = 267,                   /* RELOP  */
    LOP = 268,                     /* LOP  */
    BOP = 269,                     /* BOP  */
    ASSIGN = 270,                  /* ASSIGN  */
    SPL = 271,                     /* SPL  */
    NEWLINE = 272,                 /* NEWLINE  */
    WS = 273,                      /* WS  */
    COMMENT = 274,                 /* COMMENT  */
    FUNCTION_OPEN = 275            /* FUNCTION_OPEN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define KEYWORD 258
#define IDENTIFIER 259
#define CONDWITHBRAC 260
#define FUNCCALL 261
#define CONSTANT 262
#define DOUBLE_CONSTANT 263
#define STRING 264
#define ARITH_ASSIGN_OP 265
#define ARITH_OP 266
#define RELOP 267
#define LOP 268
#define BOP 269
#define ASSIGN 270
#define SPL 271
#define NEWLINE 272
#define WS 273
#define COMMENT 274
#define FUNCTION_OPEN 275

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 15 "4.y"

    char name[100];
    char value[100];

#line 112 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
