#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>

FILE *fp;
char c,prev_char='\0';

const char *keywords[] = {  "auto", "break", "case", "char", "const", "continue",
                            "default", "do", "double", "else", "enum", "extern",
                            "float", "for", "goto", "if", "int", "long", "register",
                            "return", "short", "signed", "sizeof", "static", "struct",
                            "switch", "typedef", "union", "unsigned", "void", "volatile",
                            "while"  };
                            
const char *typeName[] = {	"Special Character",				//1
							"Arithematic Operator",				//2
							"Arithematic Assignment Operator",	//3	
							"Assignment Operator",				//4
							"Relational Operator",				//5
							"Bitwise Operator",					//6
							"Logical Operator",					//7
							" "  	};			
char getChar()
{
    prev_char=c;
    c=fgetc(fp);
    return c;
}

void parse_ppd()
{
    int i=0;
    do{
        printf("%c",c!='\n'?c:' ');
	    i++;
        if(c == '\n')
            break;
        getChar();
    }while(1);
    getChar();
    printf("%-*c - Preprocessor Directive\n",30-i,' ');
}

void parse_fn(int l)
{
    int i=0;
    do{
        printf("%c", c);
	i++;
        if(c == ')')
            break;
        getChar();
    }while(1);
    getChar();
    printf("%-*c - Function Call\n",30-i-l,' ');
}

void parse_num()
{
    char num[100];
    int j=0;
    do{
        num[j++] = c;
        getChar();
    }while(isdigit(c));
    num[j] = '\0';
    printf("%-30s - Integer Constant\n", num);
}

void parse_name()
{
    char name[100];
    int j=0;
    do{
        name[j++] = c;
        getChar();
    }while(isalnum(c));
    name[j] = '\0';
    printf("%s", name);
    for (int j = 0; j < sizeof(keywords) / sizeof(*keywords); j++) {
        if(!strcmp(name, keywords[j])){
            printf("%-*c - Keyword\n",(int)(30-strlen(name)),' ');
            return;
        }
    }
    if(c=='(')
        parse_fn(strlen(name));
    else
       printf("%-*c - Identifier\n",(int)(30-strlen(name)),' ');
}

int getType()
{
    char spl[] = ";,.[](){}",arithOperators[] = "+-*/%";;
    int i,type=0;
    switch(c)
    {
        case ';':case ',':case '[':case ']':
        case '(':case ')':case '{':case '}':case '.':   printf("%c",c),getChar(),type=1;break;
        case '+':case '-':case '*':case '/':case '%':   printf("%c",c);
                                                        type=2;
                                                        if(getChar()=='=')
                                                        {
                                                            printf("%c",c);
                                                            getChar();
                                                            type=3;
                                                        }
                                                        break;
        case '=':   printf("%c",c);
                    type=4;
                    if(getChar()=='=')
                    {
                        printf("%c",c);
                        getChar();
                        type=5;
                    }
                    break;
        case '<':   printf("%c",c);
                    type=5;
                    if(getChar()=='=')
                    {
                        printf("%c",c);
                        getChar();
                    }
                    else if(c=='<')
                    {
                        printf("%c",c);
                        getChar();
                        type=6;
                    }
                    break;
        case '>':   printf("%c",c);
                    type=5;
                    if(getChar()=='=')
                    {
                        printf("%c",c);
                        getChar();
                    }
                    else if(c=='>')
                    {
                        printf("%c",c);
                        getChar();
                        type=6;
                    }
                    break;
        case '!':   printf("%c",c);
                    type=7;
                    if(getChar()=='=')
                    {
                        printf("%c",c);
                        getChar();
                        type=5;
                    }
                    break;
        case '|':   printf("%c",c);
                    type=6;
                    if(getChar()=='|')
                    {
                        printf("%c",c);
                        getChar();
                        type=7;
                    }
                    break;
        case '&':   printf("%c",c);
                    type=6;
                    if(getChar()=='&')
                    {
                        printf("%c",c);
                        getChar();
                        type=7;
                    }
                    break;
        case '^':   printf("%c",c);
                    type=6;
        default:    type=0;
    }
    return type;
}
void helper()
{

}
void parse()
{
    int type,line_comment=0,block_comment=0;
    while(c!=EOF)
    {
        //printf("\n-----prev: %c || -----curr: %c\n",prev_char,c);
        // if(c=='/')
        // {
        //     getChar();
        //     if(c=='/')
        //         line_comment = 1,getChar();
        //     else if(c=='*')
        //         block_comment = 1,getChar();
        //     else if(c=='=')
        //         printf("%-30c - %s\n",prev_char, typeName[3-1]);
        //     else
        //         printf("%-30c - %s\n",prev_char, typeName[2-1]);
        // }
        // else if(c=='*')
        // {
        //     getChar();
        //     if(c=='/')
        //         block_comment=0,getChar();
        //     else
        //         if(!line_comment && !block_comment)
        //             printf("%-30c - %s\n",prev_char, typeName[2-1]);
        // }
        if (line_comment && c == '\n')
            line_comment = 0;
 
        else if  (block_comment && c == '*')
        {
            if(getChar()=='/')
            {
                block_comment=0;
                getChar();
            }

        }       

        else if (line_comment|| block_comment)
            getChar();

        else if(c=='/')
        {
            if(getChar()=='/')
            {
                line_comment=1;
                getChar();
            }
            else if(c=='*')
            {
                block_comment=1;
                getChar();
            }
        }



        // if (prev_char == '/' && c == '/')
        //     line_comment = 1,getChar();
        // else if (prev_char == '/' && c == '*')
        //     block_comment = 1,getChar();
        // else if (prev_char == '*' && c == '/')
        //     block_comment = 0;

        //if (!line_comment && !block_comment)
        else
        {
            if(isalpha(c))
                parse_name();
            else if(isdigit(c))
                parse_num();
            else if(c== '#')
                parse_ppd();
            else if((type=getType()))
                printf(" %30c %s\n",'-', typeName[type-1]);
            else
                getChar();
        }
            // else if (c == '\n') 
            // {
            //     line_comment = 0;
            //     getChar();
            // }
            // else
            //     getChar();
        //prev_char = c;
    }
}
