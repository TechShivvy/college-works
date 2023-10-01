%{
#include<stdio.h>
int count = 0;
%}

%x C
%%
"/*".*"*/"	{count++;}
"/*"		{BEGIN C;}
<C>"*/"		{BEGIN 0;}
<C>\n		{;}
<C>.		{;}
\/\/.*		{count++;}
[ ]+   {}
%%

void main()
{
	char file[] = "data.c";
	yyin = fopen(file , "r");
	yylex();
	printf("Number of comment lines in c file %s is %d\n", file, count);
}

int yywrap()
{
	return 1;
}