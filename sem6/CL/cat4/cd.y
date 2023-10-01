%{
    #include<stdio.h>
    #include<stdlib.h>   
    #include "y.tab.h" 
    int yyerror();
    int yylex(void);
    int error=0;
    int temp = 0;
%}

%token<str> ID AOP MOP
%union{ char* str;}
%type<str> expr stmt 

%%
stmts : stmt stmts {} | stmt {};
stmt : ID AOP expr {printf("%s %s %s\n",$1,$2,$3);sprintf($$,"%s %s %s\n",$1,$2,$3);};
expr : ID MOP expr {printf("t%d = %s %s %s\n",temp,$1,$2,$3);sprintf($$,"t%d",temp); temp++;} | 
       ID MOP ID {printf("t%d = %s %s %s\n",temp,$1,$2,$3);Ssprintf($$,"t%d",temp); temp++;} | 
       ID {sprintf($$,"%s",$1);};
%%

int yywrap(){return 1;}

int yyerror(){
error = 1;
return 0; }

int main(){
    yyparse();
    if(!error)printf("Passed\n");
    else printf("Failed\n");
}