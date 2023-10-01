%{
#include<stdio.h>
#include<string.h>
#include"y.tab.h" 
int	l=0,open=0,top=0,which=0,N=100;
int stack[100]={0};

void push(int x){
    if(top != N-1)
        stack[++top] = x;
}

int pop(){
    top--;
}

int peek(){
    return stack[top];
}

%}

%option noyywrap
keyword     False|None|True|and|as|assert|async|await|break|class|continue|def|del|elif|else|except|finally|for|from|global|if|import|in|is|lambda|nonlocal|not|or|pass|raise|return|try|while|with|yield
identifier  [[:alpha:]_][[:alnum:]_]*
floating    [0-9]+\.[0-9]+([eE][+-]?[0-9]+)?
digit       [0-9]
letter      [a-zA-Z]
intnum      {digit}+
ws          [ \t]+

%x F C N

%%
'''							BEGIN C;
<C>.|\n                                      
<C>'''						BEGIN 0;
":"                         {printf(" %-30s - COLON\n",yytext);}
","                         {printf(" %-30s - COMMA\n",yytext);}
"["                         {printf(" %-30s - LSQ\n",yytext);}
"]"                         {printf(" %-30s - RSQ\n",yytext);}
"("                         {printf(" %-30s - LPAREN\n",yytext);}
")"                         {printf(" %-30s - RPAREN\n",yytext);}

"as"						{printf(" %-30s - AS\n",yytext);}
"def"                       {printf(" %-30s - DEF\n",yytext);}
"else"                      {printf(" %-30s - ELSE\n",yytext);}
"for"                       {printf(" %-30s - FOR\n",yytext);}
"from"						{printf(" %-30s - FROM\n",yytext);}
"if"                        {printf(" %-30s - IF\n",yytext);}
"import"                    {printf(" %-30s - IMPORT\n",yytext);}
"in"                        {printf(" %-30s - IN\n",yytext);}
"return"					{printf(" %-30s - RETURN\n",yytext);}
"while"                     {printf(" %-30s - WHILE\n",yytext);}

{keyword}                   { printf(" %-30s - Keyword\n",yytext);}
{identifier}                { printf(" %-30s - Identifier\n",yytext);}
[0-9]+|{floating}           { printf(" %-30s - Double Constant\n",yytext);}
\"([^"\\\n]|\\.|\\\n)*\"    { printf(" %-30s - String\n",yytext);}
[\+\-\*/%]=                 { printf(" %-30s - Arithematic Assignment operator\n",yytext);}
[\+\-\*/%]                  { printf(" %-30s - Artithematic operator\n",yytext);}
==|!=|<=|>=|<|>             { printf(" %-30s - Relational operator\n",yytext);}
&&|\|\||!                   { printf(" %-30s - Logical operator\n",yytext);}
[&|^]|<<|>>                 { printf(" %-30s - Bitwise operator\n",yytext);}
=                           { printf(" %-30s - Assignment operator\n",yytext);}
[\n] 					    {
								yyless(0);
                                printf(" %-30s - NEWLINE1\n",yytext);
                                BEGIN N;
                            }
<N>[\n][\t]*                {
                                int len=strlen(yytext)-1;
                                yylineno++;
                                if(len>peek())
                                {
                                    push(len);
                                    printf(" %-30s - INDENT\n",yytext+1);
									// return INDENT;
                                }
                                else if(len<peek() || (!len && peek()) )
                                {
                                    do
                                    {
                                        printf(" %-30s - DEDENT\n",yytext+1);
                                        pop();
                                    }while(top && len<peek());
                                    // return DEDENT;
                                }
                                else
                                {
                                    // printf(" %-30s - NEWLINE2\n",yytext);
                                    // return NEWLINE;
                                }
                                BEGIN 0;
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
								}
                            }
{ws}|#.*	            	;
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