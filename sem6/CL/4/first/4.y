%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
extern int yylex(void);
extern int yylineno;
extern char *yytext;
void yyerror(const char *);

int nums[100];
int idx = 0;

%}

%union {
   char *str;
   unsigned long l;
   void * distr;
   void * command;
   int num;
}
%token DEF LPAREN RPAREN COLON SEMI ASSIGN LBRACKET RBRACKET COMMA LBRACE RBRACE
%token IF ELSE FOR IN RANGE PRINT UNSORTED SORTED
%token NAME NEWLINE INDENT DEDENT PLUS MINUS TIMES DIVIDE
%token<num> NUMBER
%start stmt_list

%left PLUS MINUS
%left TIMES DIVIDE
%nonassoc UNARY_MINUS

%%

program: stmt_list {printf("program\n");};

stmt_list: stmt		{printf("stmt_list1\n");}
         | stmt_list NEWLINE stmt	{printf("stmt_list2\n");};

stmt: simple_stmt	{printf("stmt1\n");}
    | compound_stmt{printf("stmt2\n");};

simple_stmt: small_stmt	{printf("simple_stmt1\n");}
           | small_stmt SEMI small_stmt {printf("simple_stat2\n");};

small_stmt: expr_stmt	{printf("small_stmt1\n");}
          | print_stmt{printf("small_stmt2\n");};

expr_stmt: NAME ASSIGN testlist {printf("expr_stmt\n");};

testlist: test	{printf("testlist1\n");}
        | test COMMA testlist {printf("testlist2\n");};

test: NAME {printf("test1\n");}
    | NUMBER {printf("test2\n");};

print_stmt: PRINT testlist {printf("print_stmt\n");};

compound_stmt: if_stmt	{printf("cmpd_stmt1\n");}
             | for_stmt	{printf("cmpd_stmt2\n");}
             | funcdef	{printf("cmpd_stmt3\n");};

if_stmt: IF test COLON suite	{printf("if_stmt1\n");}
       | IF test COLON suite ELSE COLON suite	{printf("if_stmt2\n");};

for_stmt: FOR NAME IN RANGE test COLON suite	{printf("for_stmt\n");} ;

funcdef: DEF NAME LPAREN arglist RPAREN COLON suite	{printf("funcdef_stmt\n");};

arglist: NAME	{printf("arglist1\n");}
       | NAME COMMA arglist	{printf("arg_list2\n");};

suite: NEWLINE INDENT stmt_list DEDENT	{printf("suite1\n");}
     | simple_stmt	{printf("suite2\n");};


%%
void yyerror(const char *s) {
fprintf(stderr, "Error on line %d: %s\n", yylineno, s);
}

int main(void) {
yyparse();
return 0;
}
