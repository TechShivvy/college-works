%{
#include<stdio.h>
#include<string.h>
#include"y.tab.h" 
int	l=0,open=0,top=0,which=0;
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
":"                         {printf(" %-30s - COLON\n",yytext);return COLON;}
","                         {printf(" %-30s - COMMA\n",yytext);return COMMA;}
"["                         {printf(" %-30s - LSQ\n",yytext);return LSQ;}
"]"                         {printf(" %-30s - RSQ\n",yytext);return RSQ;}
"("                         {printf(" %-30s - LPAREN\n",yytext);return LPAREN;}
")"                         {printf(" %-30s - RPAREN\n",yytext);return RPAREN;}

"as"						{printf(" %-30s - AS\n",yytext);return AS;}
"def"                       {printf(" %-30s - DEF\n",yytext);return DEF;}
"else"                      {printf(" %-30s - ELSE\n",yytext);return ELSE;}
"for"                       {printf(" %-30s - FOR\n",yytext);return FOR;}
"from"						{printf(" %-30s - FROM\n",yytext);return FROM;}
"if"                        {printf(" %-30s - IF\n",yytext);return IF;}
"import"                    {printf(" %-30s - IMPORT\n",yytext);return IMPORT;}
"in"                        {printf(" %-30s - IN\n",yytext);return IN;}
"return"					{printf(" %-30s - RETURN\n",yytext);return RETURN;}
"while"                     {printf(" %-30s - WHILE\n",yytext);return WHILE;}

{keyword}                   { printf(" %-30s - Keyword\n",yytext);return KEYWORD;}
{identifier}                { printf(" %-30s - Identifier\n",yytext); return IDENTIFIER;}
[0-9]+|{floating}           { printf(" %-30s - Double Constant\n",yytext); return NUMBER;}
\"([^"\\\n]|\\.|\\\n)*\"    { printf(" %-30s - String\n",yytext);return STRING;}
[\+\-\*/%]=                 { printf(" %-30s - Arithematic Assignment operator\n",yytext);return ARITH_ASSIGN_OP;}
[\+\-\*/%]                  { printf(" %-30s - Artithematic operator\n",yytext);return ARITH_OP;}
==|!=|<=|>=|<|>             { printf(" %-30s - Relational operator\n",yytext);return RELOP;}
&&|\|\||!                   { printf(" %-30s - Logical operator\n",yytext);return LOP;}
[&|^]|<<|>>                 { printf(" %-30s - Bitwise operator\n",yytext);return BOP;}
=                           { printf(" %-30s - Assignment operator\n",yytext);return ASSIGN;}
[\n][\t]* 					{
								int x=strlen(yytext)-1;
								yylineno++;
								//printf(" \n----%d -----\t",x);
								if(stack[top]==x)
								{
									// printf(" %-30s - Here\n"," ");
									// if(which<0)
									// {
									// 	printf(" %-30s - DEDENT\n",yytext);
									// 	which=0;
									// 	return DEDENT;
									// }
								}
								else if(stack[top]<x)
								{	
									top+=1;
									stack[top]=x; 
									printf(" %-30s - INDENT\n",yytext);
									which=1;
									return INDENT;
								}
								else
								{
									do
									{
										top-=1;
										if(stack[top]==x)
										{
											printf(" %-30s - DEDENT\n",yytext);
											which=-1;
											return DEDENT;
										}
										else if(stack[top]<x)
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
{identifier}"("				{
								printf(" %s",yytext);
								l+=strlen(yytext);
								open++;
								BEGIN F;
                            }                           
<F>.                        { 
								printf("%s",yytext);
								l++;
								open+=(yytext[0]=='(');
								open-=(yytext[0]==')');
								if(!open)
								{
									printf("%*c Function Call\n",32-l,'-');
                                    l=0;
									BEGIN 0;
									return FUNCCALL;
								}
                            }
{ws}|#.*	            	;
.                           { printf(" %-30s - Special character\n",yytext);return  SPL;}

%%
// int main(int argc,char** argv)
// {
//     yylex();
//     //FILE *fp = fopen("input.c", "r");    
//     //yyin = fp;
//     //yylex();
//     //fclose(fp);
//     return 0;
// }