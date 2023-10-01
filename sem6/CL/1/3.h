#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>

struct symbolTable
{
    char name[100];
    char type[100];
    long bytes;
    long long add;
    long val;
};

FILE *fp;
int cnt=0,identifier=0,assign=0;
struct symbolTable st[100];
char c,prev_char='\0',keyword[100],var[100];

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

int getSize(char *type)
{
    if(!strcmp(type,"int")||!strcmp(type,"float"))
        return 4;
    else if(!strcmp(type,"long")||!strcmp(type,"double"))
        return 8;
    else if(!strcmp(type,"char"))
        return 1;
    else if(!strcmp(type,"short"))
        return 2;
}

int visited(char *arg)
{
    for(int i=0;i<cnt;i++)
        if(!strcmp(st[i].name,arg))
            return 1;
    return 0;
}
void printTable()
{
    //"---------------------------------------------------------------------"
    printf("\n %.*s\n", 15*5-6, "=====================================================================");
    printf(" %-15s %-15s %-15s %-15s %-15s\n","Identifier","Type","Bytes","Address","Value");
    printf(" %.*s\n", 15*5-6, "=====================================================================");
    //rintf(" %*s\n",4+15*5,"-");
    for(int i=0;i<cnt;i++)
        printf(" %-15s %-15s %-15ld %-15lld %-15ld\n",st[i].name,st[i].type,st[i].bytes,st[i].add,st[i].val),i==cnt-1?:0;
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
    st[cnt-1].val=atoll(num);
    if(identifier && assign)
    {
        for(int i=0;i<cnt;i++)
        {
            if(!strcmp(var,st[i].name))
            {
                st[i].val=atoll(num);
                break;
            }
        }
    }
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
            if(!strstr(name,"intfloatlongdoublecharshort"))
                strcpy(keyword,name);
            return;
        }
    }
    if(c=='(')
        parse_fn(strlen(name));
    else
    {
        printf("%-*c - Identifier\n",(int)(30-strlen(name)),' ');
        if(!visited(name))
        {
            strcpy(st[cnt].name,name);
            strcpy(st[cnt].type,keyword);
            st[cnt].bytes=getSize(keyword);
            st[cnt].add=(cnt?st[cnt-1].add+st[cnt].bytes:1000);
            st[cnt++].val=0;
            identifier=1;
            strcpy(var,name);
        }
    }
}

int getType()
{
    char spl[] = ";,.[](){}",arithOperators[] = "+-*%/";;
    int i,type=0;
    switch(c)
    {
        case ';':bzero(keyword,100),identifier=0,assign=0;
        case ',':case '[':case ']':
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
    assign=(type==3||type==4);
    return type;
}
int parse()
{
    int type,line_comment=0,block_comment=0;
    while(c!=EOF)
    {   
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
    }
    return !block_comment;
}
