#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>

FILE *fp;
char c;

const char *keywords[] = {  "auto", "break", "case", "char", "const", "continue",
                            "default", "do", "double", "else", "enum", "extern",
                            "float", "for", "goto", "if", "int", "long", "register",
                            "return", "short", "signed", "sizeof", "static", "struct",
                            "switch", "typedef", "union", "unsigned", "void", "volatile",
                            "while"  };
                            
const char *typeName[] = {	"Special Character",				//1
							"Arithematic Opeartor",				//2
							"Arithematic Assignment Operator",	//3	
							"Assignment Operator",				//4
							"Relational Operator",				//5
							"Bitwise Operator",					//6
							"Logical Operator",					//7
							" "  	};			
char getChar()
{
    c=fgetc(fp);
    return c;
}

void parse_ppd()
{
    int i=0;
    do{
        printf("%c",c);
	i++;
        if(c == '>')
            break;
        getChar();
    }while(1);
    getChar();
    printf("%-*c - Preprocessor directive\n",30-i,' ');
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
    printf("%-*c - Function\n",30-i-l,' ');
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
    printf("%-30s - integer constant\n", num);
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
            printf("%-*c - keyword\n",(int)(30-strlen(name)),' ');
            return;
        }
    }
    if(c=='(')
        parse_fn(strlen(name));
    else
       printf("%-*c - identifier\n",(int)(30-strlen(name)),' ');
}

int SplChar()
{
    char spl[] = ";,.[](){}";
    int i;
    for (i = 0; i < 9; ++i)
    {
        if (c == spl[i])
        {
            printf("%c",c);
            getChar();
            return 1;
        }
    }
    return 0;
}

int ArithOper()
{
    char arithOperators[] = "+-*/%";//{'+', '-', '*', '/', '%'};
    int i;
    for (i = 0; i < 5; ++i)
    {
        if (c == arithOperators[i])
        {
            printf("%c",c);
            if(getChar()=='=')
            {
                printf("%c",c);
                getChar();
                return 3;
            }
            return 2;
        }
    }
    return 0;
}

int Equal()
{
    if(c=='=')
    {
        printf("%c",c);
        if(getChar()=='=')
        {
            printf("%c",c);
            getChar();
            return 5;
        }
        return 4;
    }
    return 0;
}

int LE()
{
    if(c=='<')
    {
        printf("%c",c);
        if(getChar()=='=')
        {
            printf("%c",c);
            getChar();
            return 5;
        }
        else if(c=='<')
        {
            printf("%c",c);
            getChar();
            return 6;
        }
        return 5;
    }
    return 0;
}

int GE()
{
    if(c=='>')
    {
        printf("%c",c);
        if(getChar()=='=')
        {
            printf("%c",c);
            getChar();
            return 5;
        }
        else if(c=='>')
        {
            printf("%c",c);
            getChar();
            return 6;
        }
        return 5;
    }
    return 0;
}

int Exclaim()
{
    if(c=='!')
    {
        printf("%c",c);
        if(getChar()=='=')
        {
            printf("%c",c);
            getChar();
            return 5;
        }
        return 7;
    }
    return 0;
}

int Or()
{
    if(c=='|')
    {
        printf("%c",c);
        if(getChar()=='|')
        {
            printf("%c",c);
            getChar();
            return 7;
        }
        return 6;
    }
    return 0;
}

int And()
{
    if(c=='&')
    {
        printf("%c",c);
        if(getChar()=='&')
        {
            printf("%c",c);
            getChar();
            return 7;
        }
        return 6;
    }
    return 0;
}

int Caps()
{
    if(c=='^')
    {
        printf("%c",c);
        return 6;
    }
    return 0;
}

int getType()
{
    // int val=SplChar();
    // if(!val)
    // 	val=ArithOper();
    // if(!val)
    //     val=Equal();
    // if(!val)
    //     val=LE();
    // if(!val)
    //     val=GE();
    // if(!val)
    //     val=Exclaim();
    // if(!val)
    //     val=Or();
    // if(!val)
    //     val=And();
    // if(!val)
    //     val=Caps();
    // return val;
    int val;
    !(val=SplChar()) && !(val=ArithOper()) && !(val=Equal()) && !(val=LE()) && !(val=GE()) && !(val=Exclaim()) && !(val=Or()) && !(val=And()) && !(val=Caps());
    return val;
}
void parse()
{
    int type;
    while(c!=EOF)
    {
        if(isalpha(c))
            parse_name();
        else if(isdigit(c))
            parse_num();
        else if(c== '#')
            parse_ppd();
        //else if (c == ';' || c == ',' || c == '.' || c == '[' || c == ']' || c == '(' || c == ')' || c == '{' || c == '}')
            //printf("%-30c - Special character\n",c),getChar();
        else if((type=getType()))
        {
           printf(" %30c %s\n",'-', typeName[type-1]);
        }
        else
            getChar();
    }
}
