%{
    #include<stdio.h>
    #include<stdlib.h>   
    #include "y.tab.h" 
    #include<string.h>
%}

%%
[a-zA-Z][a-zA-Z0-9_]* {yylval.str = strdup(yytext);return ID;}
"=" {yylval.str = strdup(yytext); return AOP;}
"+"|"*" {yylval.str = strdup(yytext); return MOP;}
. ;
%%
