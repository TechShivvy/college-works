%{
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "y.tab.h"
#include <string.h>
#include "COMMON.h"

int yylex(void);
int yyerror();
int yywrap();

// optimisation functions
int isNumber(char* string);
int getNumericalValue(char* string);
int doMath(int a, int b, char* operator);



int error = 0;
extern int line; // reference to the line variable in the .l lex file. whatever you assign there can be accessed here.
extern FILE* yyin;
FILE* threeAddressCodeFile;
FILE* optimizedCodeFile;
FILE* codeGenerationFile;
int tempVariableNum = 0;
int isSyntaxCheckingOver = 0;
int isCodeOptimizationOver = 0;
int registerNum = 0;
%}

%token  ASSIGNMENT 

%union { 
	char* str; 
}

%token<str> OPERATOR ID NUMBER // only need these when you are printing them %s expects type string //use token<str> for terminals
%type<str> operand 

%%
program: statement | program statement;
statement: 		ID ASSIGNMENT operand OPERATOR operand 	{	
															if(!isSyntaxCheckingOver) { 
																fprintf(threeAddressCodeFile, "t%d = %s %s %s\n", tempVariableNum, $3, $4, $5);
																fprintf(threeAddressCodeFile, "%s = t%d\n", $1, tempVariableNum);
																tempVariableNum++;
															} else if (!isCodeOptimizationOver && isSyntaxCheckingOver) { // code optimisation
																int leftIsNum = isNumber($3);
																int rightIsNum = isNumber($5);
																if(leftIsNum && rightIsNum) {
																	// perform constant folding: t0 = 5+7 will be t0 = 12 
																	int left = getNumericalValue($3);
																	int right = getNumericalValue($5);
																	int result = doMath(left, right, $4);
																	fprintf(optimizedCodeFile, "%s = %d\n", $1, result);
																} else if (leftIsNum || rightIsNum) {
																	// algebraic identity
																	int left = getNumericalValue($3);
																	int right = getNumericalValue($5);

																	if(left == 1  && strcmp($4, "*")==0) {
																		fprintf(optimizedCodeFile, "%s = %s\n", $1, $5);
																	} else if (right == 1 && strcmp($4, "*")==0) {
																		fprintf(optimizedCodeFile, "%s = %s\n", $1, $3);
																	} else if (left == 0 && strcmp($4, "*")==0) {
																		fprintf(optimizedCodeFile, "%s = %d\n", $1, 0);
																	} else if (right == 0 && strcmp($4, "*")==0) {
																		fprintf(optimizedCodeFile, "%s = %d\n", $1, 0);
																	} 
																	else if (right == 0 && (strcmp($4, "+")==0 || strcmp($4, "-")==0)) {
																		fprintf(optimizedCodeFile, "%s = %s\n", $1, $3);
																	} else if (left == 0 && (strcmp($4, "+")==0 || strcmp($4, "-")==0)) {
																		fprintf(optimizedCodeFile, "%s = %s\n", $1, $5);
																	} else {
																		fprintf(optimizedCodeFile, "%s = %s %s %s\n", $1, $3, $4, $5);
																	}
																} else {
																	fprintf(optimizedCodeFile, "%s = %s %s %s\n", $1, $3, $4, $5);
																}
															} else { // code generation
																/*
																	// mov source, destination
																	t0 = 5 + b
																	mov 5, r0
																	add b, r0
																	mov r0, t0
																*/
																//printf("aaaa");
																fprintf(codeGenerationFile, "mov %s, r%d\n", $3, registerNum);
																if(strcmp($4, "+")==0) {
																	fprintf(codeGenerationFile, "add %s, r%d\n", $5, registerNum);
																} else if(strcmp($4, "-")==0) {
																	fprintf(codeGenerationFile, "sub %s, r%d\n", $5, registerNum);
																} else if(strcmp($4, "*")==0) {
																	fprintf(codeGenerationFile, "mul %s, r%d\n", $5, registerNum);
																} else if(strcmp($4, "/")==0) {
																	fprintf(codeGenerationFile, "div %s, r%d\n", $5, registerNum);
																}
																fprintf(codeGenerationFile, "mov r%d, %s\n", registerNum, $1);
																registerNum++;
															}
														}

			|	ID ASSIGNMENT operand OPERATOR operand OPERATOR operand {
																			fprintf(threeAddressCodeFile, "t%d = %s %s %s\n", tempVariableNum, $3, $4, $5);
																			fprintf(threeAddressCodeFile, "t%d = t%d %s %s\n", tempVariableNum+1, tempVariableNum, $6, $7);
																			fprintf(threeAddressCodeFile, "%s = t%d\n", $1, tempVariableNum+1);
																			tempVariableNum += 2;
																		}
			|	ID ASSIGNMENT operand 	{
											if(!isSyntaxCheckingOver) {
												fprintf(threeAddressCodeFile, "%s = %s\n", $1, $3);
											} else if(!isCodeOptimizationOver) {
												fprintf(optimizedCodeFile, "%s = %s\n", $1, $3);
											} else {
												fprintf(codeGenerationFile, "mov %s, %s\n", $3, $1);
											}
										};

operand: ID | NUMBER
%%

int isNumber(char* string) {
	int isNum;
	return (sscanf(string, "%d", &isNum) == 1);
}

int getNumericalValue(char* string) {
	int num;
	sscanf(string, "%d", &num);
	return num;
}

// return a operator b value
int doMath(int a, int b, char* operator) {
	// printf("a:%d, b:%d, op: [%s]\n", a, b, operator); // debugging
	if(strcmp(operator, "+") == 0) {
		return a + b;
	} else if (strcmp(operator, "-") == 0) {
		return a - b;
	} else if (strcmp(operator, "*") == 0) {
		return a * b;
	} else if (strcmp(operator, "/") == 0) {
		return a / b;
	} else if (strcmp(operator, "%") == 0) {
		return a % b;
	}
}

int yyerror() {
	if(!isSyntaxCheckingOver) {
		printf("There is an error %d\n", line);
    	error = 1;
	}
    
}

int yywrap() {
    return 1;
}

int main(void){
	yyin = fopen("input", "r+");
	if(!yyin) {
		printf("File not found!\n");
		return 0;
	}

	// Syntax and three address code
	threeAddressCodeFile = fopen("threeAddressCode.txt", "w");

	yyparse();
	isSyntaxCheckingOver = 1;
	fclose(threeAddressCodeFile);
	fclose(yyin);
	if(!error) {
		printf("The program has no syntax errors!\n");
		error = 0;
	}
	else {
		printf("The program has syntax errors :(\n");
		return 0;
	}
	

	// Code optimisation
	yyin = fopen("threeAddressCode.txt", "r+");
	if(!yyin) {
		printf("File not found!\n");
		return 0;
	}
	optimizedCodeFile = fopen("optimizedCode.txt", "w");

	yyparse();
	isCodeOptimizationOver = 1;
	fclose(threeAddressCodeFile);
	fclose(yyin);

	// Code Generation
	yyin = fopen("optimizedCode.txt", "r+");
	if(!yyin) {
		printf("File not found!\n");
		return 0;
	}
	codeGenerationFile = fopen("codeGeneration.txt", "w");
	yyparse();
	fclose(codeGenerationFile);
	fclose(yyin);
	return 0;
}