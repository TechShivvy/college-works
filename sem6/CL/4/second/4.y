%{
#include<stdio.h>
#include<string.h>
#include "y.tab.h"
extern int yylex(void);
extern int yylineno;
extern char *yytext;

void yyerror(char *);
%}

%token<name> KEYWORD IDENTIFIER CONDWITHBRAC FUNCCALL
%token<value> CONSTANT DOUBLE_CONSTANT STRING ARITH_ASSIGN_OP ARITH_OP RELOP LOP BOP ASSIGN SPL NEWLINE

%union {
    char name[100];
    char value[100];
}

%start program

%{
void print(char*, char*);
%}

%token WS
%token COMMENT
%token FUNCTION_OPEN

%{
#define MAX 100
char stack[MAX][MAX];
int top = -1;
void push(char*);
void pop();
int is_empty();
int is_full();
%}

%%
program:
    statements
    ;

statements:
    statement
    | statements NEWLINE statement
    | statements ";" NEWLINE statement
    ;

statement: 
	| simple
	| compound
	;

simple:
	expression
	| print
	;
	
expression:
	IDENTIFIER ASSIGN alnumlist
	;

alnumlist:
	alnum
	| alnum "," alnumlist
	;
	
alnum:
	IDENTIFIER
	| STRING
	| CONSTANT
	| DOUBLE_CONSTANT
	;
	
print:
	"print(" alnumlist ")"
	;

compound:
	if
	| for
	| funcdef
	| funccall
	;

if:
	"if(" cond ":"  NEWLINE statements "else" ":" statements
	| "if" cond ":" NEWLINE statements "else" ":" statements
	;
	
cond:
	alnum
	| alnum RELOP cond
	| alnum LOP cond
	| alnum BOP cond
	; 	

for:
	"for" IDENTIFIER "in range(" alnumlist "):" statements
	;
	
funcdef:
	"def" IDENTIFIER FUNCCALL ":"
	;

funccall:
	FUNCCALL
	;
	

    /*KEYWORD       { print($1, "Keyword"); }
    | IDENTIFIER  { print($1, "Identifier"); }
    | CONSTANT    { print($1, "Constant"); }
    | DOUBLE_CONSTANT { print($1, "Double Constant"); }
    | STRING      { print($1, "String"); }
    | ARITH_ASSIGN_OP { print($1, "Arithematic Assignment operator"); }
    | ARITH_OP    { print($1, "Artithematic operator"); }
    | REL_OP      { print($1, "Relational operator"); }
    | LOGICAL_OP  { print($1, "Logical operator"); }
    | BITWISE_OP  { print($1, "Bitwise operator"); }
    | ASSIGN_OP   { print($1, "Assignment operator"); }
    | FUNCTION_NAME FUNCTION_OPEN { push($1); push("("); }
    | SPECIAL_CHARACTER {
                            char* op = $1;
                            if (strcmp(op, "(") == 0) {
                                push(op);
                            } else if (strcmp(op, ")") == 0) {
                                pop();
                            }
                            print(op, "Special character");
                        }
    | COMMENT WS { }
    | WS          { }
    ;*/

%%
void print(char* str1, char* str2) {
    printf(" %-30s - %s\n", str1, str2);
}

void push(char* item) {
    if (is_full()) {
        printf("Stack Overflow\n");
        return;
    }
    strcpy(stack[++top], item);
}

void pop() {
    if (is_empty()) {
        printf("Stack Underflow\n");
        return;
    }
    top--;
}

int is_empty() {
    return top == -1;
}

int is_full() {
    return top == MAX-1;
}

void yyerror(char *s) {
    printf("%s\n", s);
}

int main() {
    yyparse();
    return 0;
}

