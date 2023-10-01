%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "y.tab.h"


int yylex(void);

int yyerror(char* s);

extern int yylval;

int stack[100]={0};
int top=0;



%}

newline \n

blank [ ]

tab [\t]

letter [a-zA-Z]

digit  [0-9]

assignment "="

arithop "+"|"-"|"/"|"*"|"%"|"//"

arithass "+="|"-="|"*="|"/="|"%="|"//="

relop ">"|">="|"<"|"<="|"=="|"!="

logicop "and"|"or"|"not"

import "import"
as "as"
from "from"
if "if"

keyword "def"|"False"|"await"|"else"|"pass"|"None"|"break"|"except"|"in"|"raise"|"True"|"class"|"finally"|"is"|"return"|"and"|"continue"|"for"|"lambda"|"try"|"def"|"nonlocal"|"while"|"assert"|"del"|"global"|"not"|"with"|"async"|"elif"|"and"|"yield"

identifier [a-zA-Z_][a-zA-Z0-9_]*

spl ("#"|"."|","|"("|")"|"'"|"["|"]"|":")

integer [0-9]+

float [0-9]+(\.[0-9]+)?([eE][+-]?[0-9]+)?

string (\"([^\"\n]|(\\\n))*\")|(\'([^\'\n]|(\\\n))*\')



%%

{newline}{tab}* {
				 int x=strlen(yytext)-1;
				 printf(" \n----%d -----\t",x);
				 if(stack[top]==x);
				 else if(stack[top]<x){top+=1;stack[top]=x; printf("INDENT\t");return INDENT;}
				 else{
					do
					{
						top-=1;
						if(stack[top]==x){printf("DEDENT\t");return DEDENT;}
						else if( stack[top]<x){ 
							char msg[25];
  							sprintf(msg,"indendation error");
  							yyerror(msg);
  							}
					}while(top>0);
					if(top==0 && stack[top]!=x){
						char msg[25];
  							sprintf(msg,"indendation error");
  							yyerror(msg);
					}
			

				 }
				}
{blank}   ;


\"\"\"([^"]|\n)*\"\"\" printf("%s : Multiline comment\n",yytext);
"#".* 	printf("%s : Single line comment\n",yytext);



{logicop} {printf("%s : Logic operator\n",yytext); return LOGICOP;}
{relop} {printf("%s : Relational operator\n",yytext); return RELOP;}
{arithop} {printf("%s : Arithmetic operator\n",yytext); return ARITHOP;}
{arithass} {printf("%s : Arithmetic assignment operator\n",yytext); return ARITHASS;}
{assignment} {printf("%s : Assignment operator\n",yytext); return ASSIGNOP;}

{import} {printf("%s : keyword\n",yytext); return IMPORT;}
{as} {printf("%s : keyword\n",yytext); return AS;}
{from} {printf("%s : keyword\n",yytext); return FROM;}
{if} {printf("%s : keyword\n",yytext); return IF;}

{keyword} {printf("%s : Keyword\n",yytext); return KEYWORD;}
{identifier} {printf("%s : Identifier\n",yytext);return IDENTIFIER;}
{spl} {printf("%s : special character\n",yytext); return *yytext;}
{integer} {printf("%s : Integer constant\n",yytext); return INT;}
{float} {printf("%s : Float constant\n",yytext); return FLOAT;}
{string} {printf("%s : String constant\n",yytext); return STRING;}

. {
	char msg[25];
	sprintf(msg,"Unknown token, <%s> \n",yytext);
	yyerror(msg);
}

%% 


