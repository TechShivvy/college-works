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
    DEF = 258,                     /* DEF  */
    LPAREN = 259,                  /* LPAREN  */
    RPAREN = 260,                  /* RPAREN  */
    COLON = 261,                   /* COLON  */
    SEMI = 262,                    /* SEMI  */
    ASSIGN = 263,                  /* ASSIGN  */
    LBRACKET = 264,                /* LBRACKET  */
    RBRACKET = 265,                /* RBRACKET  */
    COMMA = 266,                   /* COMMA  */
    LBRACE = 267,                  /* LBRACE  */
    RBRACE = 268,                  /* RBRACE  */
    IF = 269,                      /* IF  */
    ELSE = 270,                    /* ELSE  */
    FOR = 271,                     /* FOR  */
    IN = 272,                      /* IN  */
    RANGE = 273,                   /* RANGE  */
    PRINT = 274,                   /* PRINT  */
    UNSORTED = 275,                /* UNSORTED  */
    SORTED = 276,                  /* SORTED  */
    NAME = 277,                    /* NAME  */
    NEWLINE = 278,                 /* NEWLINE  */
    INDENT = 279,                  /* INDENT  */
    DEDENT = 280,                  /* DEDENT  */
    PLUS = 281,                    /* PLUS  */
    MINUS = 282,                   /* MINUS  */
    TIMES = 283,                   /* TIMES  */
    DIVIDE = 284,                  /* DIVIDE  */
    NUMBER = 285,                  /* NUMBER  */
    UNARY_MINUS = 286              /* UNARY_MINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define DEF 258
#define LPAREN 259
#define RPAREN 260
#define COLON 261
#define SEMI 262
#define ASSIGN 263
#define LBRACKET 264
#define RBRACKET 265
#define COMMA 266
#define LBRACE 267
#define RBRACE 268
#define IF 269
#define ELSE 270
#define FOR 271
#define IN 272
#define RANGE 273
#define PRINT 274
#define UNSORTED 275
#define SORTED 276
#define NAME 277
#define NEWLINE 278
#define INDENT 279
#define DEDENT 280
#define PLUS 281
#define MINUS 282
#define TIMES 283
#define DIVIDE 284
#define NUMBER 285
#define UNARY_MINUS 286

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "4.y"

   char *str;
   unsigned long l;
   void * distr;
   void * command;
   int num;

#line 137 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
