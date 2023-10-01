%{
    #include<stdio.h>
    #include<string.h>

    #define DEBUG 0 // Set this to 0 to disable printf statements

    #define print(fmt, ...)\
                    do{ if(DEBUG) printf(fmt,##__VA_ARGS__);}while(0)

%}

%option main noyywrap

keyword     int|float|for|while|else|if|break
identifier  [[:alpha:]_][[:alnum:]_]*    
digit       [0-9]
constant    [+-]{digit}+(\.{digit}+([eE][+-]?{digit}+)?)?

%%

{keyword}       print(" %-30s - keyword",yytext);
{identifier}    print(" %-30s - identifier",yytext);
{constant}      print(" %-30s - constant",yytext);
.               ;

%%