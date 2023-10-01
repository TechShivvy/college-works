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
# define YYDEBUG 1
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
    AS = 258,                      /* AS  */
    DEF = 259,                     /* DEF  */
    FOR = 260,                     /* FOR  */
    FROM = 261,                    /* FROM  */
    IF = 262,                      /* IF  */
    IMPORT = 263,                  /* IMPORT  */
    IN = 264,                      /* IN  */
    RETURN = 265,                  /* RETURN  */
    WHILE = 266,                   /* WHILE  */
    KEYWORD = 267,                 /* KEYWORD  */
    IDENTIFIER = 268,              /* IDENTIFIER  */
    NUMBER = 269,                  /* NUMBER  */
    STRING = 270,                  /* STRING  */
    ARITH_ASSIGN_OP = 271,         /* ARITH_ASSIGN_OP  */
    ARITH_OP = 272,                /* ARITH_OP  */
    RELOP = 273,                   /* RELOP  */
    LOP = 274,                     /* LOP  */
    BOP = 275,                     /* BOP  */
    ASSIGN = 276,                  /* ASSIGN  */
    NEWLINE = 277,                 /* NEWLINE  */
    INDENT = 278,                  /* INDENT  */
    DEDENT = 279,                  /* DEDENT  */
    FUNCCALL = 280,                /* FUNCCALL  */
    SPL = 281,                     /* SPL  */
    COLON = 282,                   /* COLON  */
    COMMA = 283,                   /* COMMA  */
    LPAREN = 284,                  /* LPAREN  */
    RPAREN = 285,                  /* RPAREN  */
    LSQ = 286,                     /* LSQ  */
    RSQ = 287,                     /* RSQ  */
    ELIF = 288,                    /* ELIF  */
    ELSE = 289                     /* ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define AS 258
#define DEF 259
#define FOR 260
#define FROM 261
#define IF 262
#define IMPORT 263
#define IN 264
#define RETURN 265
#define WHILE 266
#define KEYWORD 267
#define IDENTIFIER 268
#define NUMBER 269
#define STRING 270
#define ARITH_ASSIGN_OP 271
#define ARITH_OP 272
#define RELOP 273
#define LOP 274
#define BOP 275
#define ASSIGN 276
#define NEWLINE 277
#define INDENT 278
#define DEDENT 279
#define FUNCCALL 280
#define SPL 281
#define COLON 282
#define COMMA 283
#define LPAREN 284
#define RPAREN 285
#define LSQ 286
#define RSQ 287
#define ELIF 288
#define ELSE 289

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 17 "yacc2.y"

   char *str;
   int num;

#line 140 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
