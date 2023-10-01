%{
#include<stdio.h>
#include<string.h>
#include"y.tab.h"
int l=0,open=0;
%}

%option noyywrap
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
{keyword}                    return KEYWORD;
{identifier}                 return IDENTIFIER;
[0-9]+                       return CONSTANT;
{floating}                   return DOUBLE_CONSTANT;
\"([^"\\\n]|\\.|\\\n)*\"     return STRING;
[\+\-\*/%]=                  return ARITH_ASSIGN_OP;
[\+\-\*/%]                   return ARITH_OP;
==|!=|<=|>=|<|>              return RELOP;
&&|\|\||!                    return LOP;
[&|^]|<<|>>                  return BOP;
=                            return ASSIGN;
{identifier}\s*\(           {
                              int i;
                              for(i=0;yytext[i]!='(' && yytext[i]!=' ';i++);
                              char c=yytext[i];
                              yytext[i]='\0';
                              if(strstr("ifwhileswitch",yytext))
                                return CONDWITHBRAC;
                              else
                              {
                                yytext[i]=c;
                                printf(" %s",yytext);
                                l+=strlen(yytext);
                                open++;
                                BEGIN F;
                              }
                            }                           
<F>.                        { 
                              printf("%s",yytext);
                              l++;
                              open+=(yytext[0]=='(');
                              open-=(yytext[0]==')');
                              if(!open)
                              {
                                return FUNCCALL;
                                l=0;
                                BEGIN 0;
                              }
                            }
{ws}|#.*	            { }
[\n]+			    return NEWLINE;
.                           { return  SPL;}

%%
