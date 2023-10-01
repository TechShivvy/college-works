%{
#include<stdio.h>
#include<string.h>
#include"y.tab.h"
int	l=0,open=0,top=0;
int stack[100]={0};
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
'''							BEGIN C;
<C>.|\n                                      
<C>'''						BEGIN 0;

"as"						return AS;
"def"                       return DEF;
"else"                      return ELSE;
"for"                       return FOR;
"from"						return FROM;
"if"                        return IF;
"import"					return IMPORT;
"in"                        return IN;
"return"					return RETURN;

{keyword}                   return KEYWORD;
{identifier}                return IDENTIFIER;
[0-9]+|{floating}           return NUMBER;
\"([^"\\\n]|\\.|\\\n)*\"    return STRING;
[\+\-\*/%]=                 return ARITH_ASSIGN_OP;
[\+\-\*/%]                  return ARITH_OP;
==|!=|<=|>=|<|>             return RELOP;
&&|\|\||!                   return LOP;
[&|^]|<<|>>                 return BOP;
=                           return ASSIGN;
[\n][\t]* 					{
								int x=strlen(yytext)-1;
								yylineno++;
								//printf(" \n----%d -----\t",x);
								if(stack[top]==x)
									;
								else if(stack[top]<x)
								{	
									top+=1;
									stack[top]=x; 
									return INDENT;
								}
								else
								{
									do
									{
										top-=1;
										if(stack[top]==x)
											return DEDENT;
										else if( stack[top]<x)
										{ 
											char msg[25];
											sprintf(msg,"indendation error");
											yyerror(msg);
										}
									}while(top>0);
									if(top==0 && stack[top]!=x)
									{
										char msg[25];
										sprintf(msg,"indendation error");
										yyerror(msg);
									}
								}
							}
{identifier}\s*\(           {
                            	int i;
								for(i=0;yytext[i]!='(' && yytext[i]!=' ';i++);
								char c=yytext[i];
								yytext[i]='\0';
								if(strstr("if while switch",yytext))
								{
									//unput('(');
									//yyless(2);
									//printf(" %-30s - Keyword\n",yytext);
									yytext[i]=c;
									//unput('(');		
									yyless(i);		// same as unput()
									//printf(" %-30s - Keyword\n %-30s - Special Charcter\n",yytext,"(\0");
									return COND;
								}
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
{ws}|#.*	            	;
.                           return  SPL;

%%
