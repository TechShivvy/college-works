%{ 
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
#include <string.h>
%}

AOP "="
MOP "+"|"-"|"*"|"/"
id [a-zA-Z_][a-zA-Z0-9_]*
num [0-9]+"."?[0-9]*
%%
{num} {yylval.str=strdup(yytext);return num;}
{AOP} {yylval.str=strdup(yytext);return AOP;}
{MOP} {yylval.str=strdup(yytext);return MOP;}
{id} {yylval.str=strdup(yytext);return id;}
. ;

%%
