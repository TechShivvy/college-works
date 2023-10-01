%{
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    
    int yylex(void);

    int yyerror(char* s);

    extern FILE* yyin;
    #include "y.tab.h"
    int error = 0;

    #include <fcntl.h>
    #include <unistd.h>
    
%}
%start program
%token IF IMPORT AS FROM INDENT DEDENT LOGICOP RELOP ARITHOP ARITHASS ASSIGNOP INFUN KEYWORD IDENTIFIER SPL INT FLOAT STRING

%%

program: statement program
|statement;

statement: import
|assignment
|funcall
|cond;

cond: IF expr ':' INDENT program DEDENT;

import: IMPORT IDENTIFIER
|IMPORT IDENTIFIER AS IDENTIFIER 
|FROM IDENTIFIER IMPORT IDENTIFIER 
|FROM IDENTIFIER IMPORT IDENTIFIER AS IDENTIFIER;

assignment: IDENTIFIER ASSIGNOP expr
| IDENTIFIER ARITHASS expr;

funcall: IDENTIFIER'('args')';
list: '['args']';

args: expr
|expr','args
|;

expr: IDENTIFIER
|funcall
|INT
|FLOAT
|STRING
|list
|expr ARITHOP expr
|expr RELOP expr
|expr LOGICOP expr
|'('expr')';








%%

int yyerror(char *s){
    fprintf(stderr, "Syntax is NOT valid! -> %s\n",s);
    error = 1;
    return 0;
}

int yywrap(){
    return 1;
}




int main(int argc, char **argv){
    
    if(argc != 2){
        fprintf(stderr, "Enter file name as argument!\n");
        return 1;
    }
    yyin = fopen(argv[1], "rt");
    if (!yyin){
        fprintf(stderr, "File not found!\n");
        return 2;
    }
    yyparse();
    if(!error){
        printf("Valid syntax!\n");
    }
    return 0;
}
