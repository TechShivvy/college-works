%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
extern int yylex(void);
extern int yylineno;
extern char *yytext;
extern int yydebug;
void yyerror(const char *);

int nums[100];
int idx = 0;

%}

%union {
   char *str;
   int num;
}
// %token DEF LPAREN RPAREN COLON SEMI ASSIGN LBRACKET RBRACKET COMMA LBRACE RBRACE
// %token IF ELSE FOR IN RANGE PRINT UNSORTED SORTED
// %token NAME NEWLINE INDENT DEDENT PLUS MINUS TIMES DIVIDE
// %token<num> NUMBER
%token AS DEF ELSE FOR FROM IF IMPORT IN RETURN WHILE
%token KEYWORD IDENTIFIER NUMBER STRING
%token ARITH_ASSIGN_OP ARITH_OP
%token RELOP LOP BOP ASSIGN
%token NEWLINE INDENT DEDENT
%token FUNCCALL SPL
%token COLON COMMA LPAREN RPAREN LSQ RSQ
%start program

// %left PLUS MINUS
// %left TIMES DIVIDE
// %nonassoc UNARY_MINUS

%%


program: 
    statement program
    | statement
    ;

statement: 
    import
    | assignment
    | funcdef
    | for
    | cond
    | return
    | FUNCCALL
    ;

for:
    FOR IDENTIFIER IN FUNCCALL COLON INDENT program DEDENT
cond: 
    IF expr COLON INDENT program DEDENT
    ;

import: 
    IMPORT IDENTIFIER
    | IMPORT IDENTIFIER AS IDENTIFIER 
    | FROM IDENTIFIER IMPORT IDENTIFIER 
    | FROM IDENTIFIER IMPORT IDENTIFIER AS IDENTIFIER
    ;

funcdef: 
    DEF FUNCCALL COLON INDENT program DEDENT
    ;

return:
    RETURN expr
    ;

assignment: 
    expr ARITH_ASSIGN_OP expr
    | expr ASSIGN expr
    ;

list: LSQ args RSQ;

args: 
    | expr
    | expr COMMA args
    ;

expr: 
    IDENTIFIER
    | FUNCCALL
    | NUMBER
    | STRING
    | list
    | IDENTIFIER list
    | LPAREN expr RPAREN
    | IDENTIFIER list COMMA IDENTIFIER list
    | IDENTIFIER RELOP IDENTIFIER   
    | expr ARITH_OP expr
    | expr RELOP expr
    | expr LOP expr
    | expr BOP expr
    ;

%%
void yyerror(const char *s) {
fprintf(stderr, "Error on line %d: %s\n", yylineno, s);
}

int main(void) {
    yydebug=0;
    yyparse();
    return 0;
}
