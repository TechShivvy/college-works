%{
#include<stdlib.h>
#include<stdio.h>
#include "y.tab.h"
#include<string.h>
int yyerror();
int yylex(void);
int error=0;
int temp=0;
%}

%token id num AOP MOP
%union {char* str;}
%type<str> stmt exp id num AOP MOP 

%%
stmts:stmt stmts {} | stmt {};
stmt:id AOP exp {printf("%s %s %s\n",$1,$2,$3);sprintf($$,"%s %s %s\n",$1,$2,$3);};
exp:id MOP exp {printf("t%d = %s %s %s\n",temp,$1,$2,$3);sprintf($$,"t%d",temp);temp++;}
   |id MOP id {printf("t%d=%s %s %s\n",temp,$1,$2,$3);sprintf($$,"t%d",temp);temp++;}
   |id{sprintf($$,"%s",$1);}
   |num MOP exp{printf("t%d=%s %s %s\n",temp,$1,$2,$3);sprintf($$,"t%d",temp);temp++;};

%%
int yywrap(){return 1;}

int yyerror(){
    error=1;
    return 0;
}

int main(){
	yyparse();
	if(!error) {printf("passed\n");}
	else printf("failed\n");

}
