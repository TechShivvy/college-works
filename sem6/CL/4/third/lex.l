%{
#include<stdio.h>
#include<string.h>
#include"y.tab.h"
int l=0,open=0;
%}

%option noyywrap
%option yylineno
keyword     False|None|True|and|as|assert|async|await|break|class|continue|def|del|elif|else|except|finally|for|from|global|if|import|in|is|lambda|nonlocal|not|or|pass|raise|return|try|while|with|yield
identifier  [[:alpha:]_][[:alnum:]_]*
floating    [0-9]+\.[0-9]+([eE][+-]?[0-9]+)?
digit       [0-9]
letter      [a-zA-Z]
intnum      {digit}+
ws          [ \t\n]+

%x F C

%%

'''	                     BEGIN C;
<C>.|\n                                      
<C>'''                       BEGIN 0;
"def"                         return DEF;
"else"                        return ELSE;
"for"                         return FOR;
"if"                          return IF;
"in"                          return IN;
"return"                      return RETURN;
{identifier}                  return IDENTIFIER;
[0-9]+                        return CONSTANT;
[\+\-\*/%]                    return ARITH_OP;
==|!=|<=|>=|<|>               return RELOP;
=                             return ASSIGN;
"[".*"]"                      return ARRAY;
\n[\t]+                       return DEDENT;
[\t]*                         return INDENT;
[\n]                         {yylineno++;return NEWLINE;};            
.                             ;
%%
