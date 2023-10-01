#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
void delay()
{
	for (int c = 1; c <= 32767; c++) 
       		for (int d = 1; d <= 32767; d++) 
       			{}
}	
char *strstrip(char *s)
{
        size_t size;
        char *end;

        size = strlen(s);

        if (!size)
                return s;

        end = s + size - 1;
        while (end >= s && isspace(*end))
                end--;
        *(end + 1) = '\0';

        while (*s && isspace(*s))
                s++;
	strcat(s,"\n");
        return s;
}
int main()
{
	char s[30];
	fgets(s, 30, stdin);
	printf("string:%s",s);
	strcpy(s,strstrip(s));
	printf("string:%s",s);
	printf("l:%ld",strlen(s));
	delay();
	printf("\rl:  ");
}
