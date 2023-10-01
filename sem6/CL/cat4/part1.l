%{
#include "y.tab.h"
#include "COMMON.h"
int line = 1;

%}


arithOp "+"|"-"|"*"|"/"|"%" 
assignOp "="
number "-"?[0-9][0-9]*
id [a-zA-Z_][a-zA-Z_0-9]*

%%
{arithOp}				{if(!isSyntaxCheckingOver) {printf("%-100s | %-100s \n", yytext, "Arithmatic operator");} yylval.str = strdup(yytext); return OPERATOR;}  // putting the operator matched into a variable called str which is present in the union in .y file
{assignOp}				{if(!isSyntaxCheckingOver) {printf("%-100s | %-100s \n", yytext, "Assignment operator");} return ASSIGNMENT;} // printing:  yytext or value that matched | what is it?
{id}					{if(!isSyntaxCheckingOver) {printf("%-100s | %-100s \n", yytext, "Identifier");} yylval.str = strdup(yytext); return ID;}
{number}				{if(!isSyntaxCheckingOver) {printf("%-100s | %-100s \n", yytext, "Number");} yylval.str = strdup(yytext); return NUMBER;}
\n                      {++line;}   // isSyntaxCheckingOver is a variable that is present in my custom common.h which is modified from the yacc file 
.					    {}
%%
