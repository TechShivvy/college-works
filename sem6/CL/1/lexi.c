#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<ctype.h>

char keywords[][10]={"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float",
"for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", "switch",
"typedef", "union", "unsigned", "void", "volatile", "while"};

int isKeywords(char *arg)
{
	for(int i=0;i<sizeof(keywords)/sizeof(keywords[0]);i++)
		if(!strcmp(arg,keywords[i]))
			return 1;
	return 0;
}

int isOperator(char ch)
{
	return (ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='%');
}

int isAssgnOperator(char *arg)
{
	return !(strcmp("+=",arg) && strcmp(arg,"-=") && strcmp(arg,"*=") && strcmp(arg,"/=") && strcmp(arg,"%="));
}

int isLogOperator(char *arg)
{
	return !(strcmp("&&",arg) && strcmp(arg,"||") && strcmp(arg,"!"));
}

int isRelOperator(char *arg)
{
	return !(strcmp("<",arg) && strcmp(arg,"<=") && strcmp(arg,">=") && strcmp(arg,">") && strcmp(arg,"==") && strcmp(arg,"!="));
}

int isBinOperator(char *arg)
{
	return !(strcmp("^",arg) && strcmp(arg,"&") && strcmp(arg,"<<") && strcmp(arg,">>") && strcmp(arg,"|"));
}

int isUnaryOperator(char *arg)
{
	return !(strcmp("-",arg) && strcmp(arg,"++") && strcmp(arg,"--"));
}

int isAssignment(char ch)
{
	return ch=='=';
}

int isSpl(char *arg)
{
	return !( strcmp(arg,";") &&  strcmp(arg,",") &&  strcmp(arg,".") &&  strcmp(arg,"[") &&  strcmp(arg,"]") &&  strcmp(arg,"(") &&  strcmp(arg,")") &&  strcmp(arg,"{") &&  strcmp(arg,"}") &&  strcmp(arg,"[]") );
}

int isFxnCall(char *arg)
{
	
}

void parse(char *filename)
{
	FILE *fp=fopen(filename,"r");
	if(!fp)
	{
        	printf("\n The file could not be opened / Not available");
		return ;
	}
	char c;
	while((c=fgetc(fp))!=EOF)
    	{
    		//printf("%c",c);
    		
    	}
	
	return;
}

int main()
{
	//mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	char *filename = "/home/cse1100/SSN/sem6/CL/input.c";
	
	/*int fd = open(filename, O_RDONLY),r;
	char buf[500]={0};
	read(fd,buf,sizeof(buf));
	printf("%s",buf);*/
	
	parse(filename);
	
	//isKeywords(" ");
	return 0;
}
