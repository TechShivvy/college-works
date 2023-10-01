%{
#include<stdio.h>
#include<string.h>
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

'''	                    { BEGIN C;}
<C>.|\n                     { }                
<C>'''                      { BEGIN 0;}
{keyword}                   { printf(" %-30s - Keyword\n",yytext);}
{identifier}                { printf(" %-30s - Identifier\n",yytext); }
[0-9]+                      { printf(" %-30s - Constant\n",yytext); }
{floating}                  { printf(" %-30s - Double Constant\n",yytext); }
\"([^"\\\n]|\\.|\\\n)*\"    { printf(" %-30s - String\n",yytext);   }
[\+\-\*/%]=                 { printf(" %-30s - Arithematic Assignment operator\n",yytext);}
[\+\-\*/%]                  { printf(" %-30s - Artithematic operator\n",yytext);}
==|!=|<=|>=|<|>             { printf(" %-30s - Relational operator\n",yytext);}
&&|\|\||!                   { printf(" %-30s - Logical operator\n",yytext);}
[&|^]|<<|>>                 { printf(" %-30s - Bitwise operator\n",yytext);}
=                           { printf(" %-30s - Assignment operator\n",yytext);}
{identifier}\s*\(           {
                              int i;
                              for(i=0;yytext[i]!='(' && yytext[i]!=' ';i++);
                              char c=yytext[i];
                              yytext[i]='\0';
                              if(strstr("ifwhileswitch",yytext))
                             {	//ungetc(yytext[i-1],stdin); 
                              	//printf(" %-30s - Keyword\n",yytext);
                                printf(" %-30s - Keyword\n %-30s - Special Charcter\n",yytext,"(\0");
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
{ws}|#.*	            { }
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
