%{
#include<stdio.h>
#include<string.h>

#define DEBUG 0 // Set this to 0 to disable printf statements

#define debug_printf(fmt, ...) \
            do { if (DEBUG) printf(fmt, ##__VA_ARGS__); } while (0)
    
#include"y.tab.h" 

int	l=0,open=0,top=0,which=0,N=100,d=0;
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

%x F C N D

%%
'''							BEGIN C;
<C>.|\n                                      
<C>'''						BEGIN 0;
":"                         {debug_printf(" %-30s - COLON\n",yytext);return COLON;}
","                         {debug_printf(" %-30s - COMMA\n",yytext);return COMMA;}
"["                         {debug_printf(" %-30s - LSQ\n",yytext);return LSQ;}
"]"                         {debug_printf(" %-30s - RSQ\n",yytext);return RSQ;}
"("                         {debug_printf(" %-30s - LPAREN\n",yytext);return LPAREN;}
")"                         {debug_printf(" %-30s - RPAREN\n",yytext);return RPAREN;}

"as"						{debug_printf(" %-30s - AS\n",yytext);return AS;}
"def"                       {debug_printf(" %-30s - DEF\n",yytext);return DEF;}
"elif"                      {debug_printf(" %-30s - ELIF\n",yytext);return ELIF;}
"else"                      {debug_printf(" %-30s - ELSE\n",yytext);return ELSE;}
"for"                       {debug_printf(" %-30s - FOR\n",yytext);return FOR;}
"from"						{debug_printf(" %-30s - FROM\n",yytext);return FROM;}
"if"                        {debug_printf(" %-30s - IF\n",yytext);return IF;}
"import"                    {debug_printf(" %-30s - IMPORT\n",yytext);return IMPORT;}
"in"                        {debug_printf(" %-30s - IN\n",yytext);return IN;}
"return"					{debug_printf(" %-30s - RETURN\n",yytext);return RETURN;}
"while"                     {debug_printf(" %-30s - WHILE\n",yytext);return WHILE;}

{keyword}                   { debug_printf(" %-30s - Keyword\n",yytext);return KEYWORD;}
{identifier}                { debug_printf(" %-30s - Identifier\n",yytext); return IDENTIFIER;}
"-"?[0-9]+|{floating}       { debug_printf(" %-30s - Constant\n",yytext); return NUMBER;}
\"([^"\\\n]|\\.|\\\n)*\"    { debug_printf(" %-30s - String\n",yytext);return STRING;}
[\+\-\*/%]=                 { debug_printf(" %-30s - Arithematic Assignment operator\n",yytext);return ARITH_ASSIGN_OP;}
[\+\-\*/%]                  { debug_printf(" %-30s - Artithematic operator\n",yytext);return ARITH_OP;}
==|!=|<=|>=|<|>             { debug_printf(" %-30s - Relational operator\n",yytext);return RELOP;}
&&|\|\||!                   { debug_printf(" %-30s - Logical operator\n",yytext);return LOP;}
[&|^]|<<|>>                 { debug_printf(" %-30s - Bitwise operator\n",yytext);return BOP;}
=                           { debug_printf(" %-30s - Assignment operator\n",yytext);return ASSIGN;}
[\n] 					    {
								yyless(0);
                                debug_printf(" %-30s - NEWLINE1\n",yytext);
                                BEGIN N;
                                return NEWLINE;
                            }
<N>[\n][\t]*                {
                                int len=strlen(yytext)-1,what=0;
                                yylineno++;
                                if(len>peek())
                                {
                                    push(len);
                                    debug_printf(" %-30s - INDENT\n",yytext+1);
                                    what=1;
                                    return INDENT;
                                }
                                else if(len<peek() || (!len && peek()) )
                                {
                                    do
                                    {
                                        debug_printf(" %-30s - DEDENT\n",yytext+1);
                                        pop();
                                        d++;
                                    }while(top && len<peek());
                                    BEGIN D;
                                    // if(top && len<peek())
                                    // {
                                    //     debug_printf(" %-30s - DEDENT\n",yytext+1);
                                    //     pop();
                                    // }
                                    
                                    // return DEDENT;
                                }
                                // if(!what)
                                //     return what+1?INDENT:DEDENT;
                            }
<D>[\n]                     ;
<D>.                        {
                                while(d--)
                                {
                                    yyless(0);
                                    return DEDENT;
                                }
                                yyless(0);
                                d=0;
                                BEGIN 0;
                            }   
<N>.                        {
                                yyless(strlen(yytext)-1);
                                BEGIN 0;
                            }  
{identifier}"("				{
								debug_printf(" %s",yytext);
								l+=strlen(yytext);
								open++;
								BEGIN F;
                            }                           
<F>.                        { 
								debug_printf("%s",yytext);
								l++;
								open+=(yytext[0]=='(');
								open-=(yytext[0]==')');
								if(!open)
								{
									debug_printf("%*c Function Call\n",32-l,'-');
                                    l=0;
									BEGIN 0;
									return FUNCCALL;
								}
                            }
{ws}|#.*	            	;   
.                           { debug_printf(" %-30s - Special character\n",yytext);return  SPL;}

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