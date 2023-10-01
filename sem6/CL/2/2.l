%{
#include<stdio.h>
#include<string.h>
int l=0,open=0;
%}

%option noyywrap
keyword     auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while
identifier  [[:alpha:]_][[:alnum:]_]*
floating    [0-9]+\.[0-9]+([eE][+-]?[0-9]+)?
/*function    printf|scanf|getch|clrscr*/
%x F C

%%

\/\*	                      { BEGIN C;}
<C>.|\n                     { }                
<C>\*\/                     { BEGIN 0;}
{keyword}                   { printf(" %-30s - Keyword\n",yytext);}
{identifier}                { printf(" %-30s - Identifier\n",yytext); }
[0-9]+                      { printf(" %-30s - Constant\n",yytext); }
{floating}                  { printf(" %-30s - Double Constant\n",yytext); }
\"([^"\\\n]|\\.|\\\n)*\"    { printf(" %-30s - String\n",yytext);   }
[\+\-\*/%]=                 { printf(" %-30s - Arithematic Assignment operator\n",yytext);}
[\+\-\*/%]                  { printf(" %-30s - Artithematic operator\n",yytext);}
==|!=|<=|>=|<|>             { printf(" %-30s - Relational operator\n",yytext);}
\+{2}|\-{2}                 { printf(" %-30s - Unary operator\n",yytext);}
&&|\|\||!                   { printf(" %-30s - Logical operator\n",yytext);}
[&|^]|<<|>>                 { printf(" %-30s - Bitwise operator\n",yytext);}
=                           { printf(" %-30s - Assignment operator\n",yytext);}
{identifier}\s*\(           {
                              int i;
                              for(i=0;yytext[i]!='(' && yytext[i]!=' ';i++);
                              char c=yytext[i];
                              yytext[i]='\0';
                              if(strstr("ifwhileforswitch",yytext))
                              {
                               	//unput('(');
                               	//yyless(2);
                               	printf(" %-30s - Keyword\n",yytext);
                               	yytext[i]=c;
                              	//unput('(');		
                              	yyless(i);		// same as unput();
                               	//printf(" %-30s - Keyword\n %-30s - Special Charcter\n",yytext,"(\0");
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
                                printf("%*c Function Call\n",32-l,'-');
                                l=0;
                                BEGIN 0;
                              }
                            }
[ \t\s]+|\n|\/\/.*          { }
.                           { printf(" %-30s - Special character\n",yytext);}

%%

int main(int argc,char** argv)
{
    yylex();
    //FILE *fp = fopen("input.c", "r");    
    //yyin = fp;
    //yylex();
    //fclose(fp);
    return 0;
}
