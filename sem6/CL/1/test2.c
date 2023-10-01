#include <stdio.h>
#include <ctype.h>
#include <string.h>

char identifier[100];
int isKeyword(char buffer[]) {
    char keywords[32][10] = {"auto", "break", "case", "char", "const", "continue",
                             "default", "do", "double", "else", "enum", "extern",
                             "float", "for", "goto", "if", "int", "long", "register",
                             "return", "short", "signed", "sizeof", "static", "struct",
                             "switch", "typedef", "union", "unsigned", "void", "volatile",
                             "while"};
    int i, flag = 0;

    for (i = 0; i < 32; ++i) {
        if (strcmp(keywords[i], buffer) == 0) {
            flag = 1;
            break;
        }
    }

    return flag;
}

int isIdentifier(char buffer[]) {
    int flag = 0;
    if (isalpha(buffer[0]) || buffer[0] == '_') {
        flag = 1;
    }
    return flag;
}

int isArithOper(char c) {
    char arithOperators[] = {'+', '-', '*', '/', '%'};
    int i;
    for (i = 0; i < 5; ++i) {
        if (c == arithOperators[i]) {
            return 1;
        }
    }
    return 0;
}

int isRelOper(char c) {
    char relOperators[] = {'<', '>', '!'};
    int i;
    for (i = 0; i < 3; ++i) {
        if (c == relOperators[i]) {
            return 1;
        }
    }
    return 0;
}

int isBitOper(char c) {
    char bitOperators[] = {'&', '|', '~', '^'};
    int i;
    for (i = 0; i < 4; ++i) {
        if (c == bitOperators[i]) {
            return 1;
        }
    }
    return 0;
}

int isUnaryOper(char c) {
    char unaryOperators[] = {'+', '-', '!', '~'};
    int i;
    for (i = 0; i < 4; ++i) {
        if (c == unaryOperators[i]) {
            return 1;
        }
    }
    return 0;
}

int isAssignOper(char c) {
    if (c == '=') {
        return 1;
    }
    return 0;
}

int isSpecialChar(char c) {
    char specialChars[] = {'(', ')', '{', '}', '[', ']', ';', ',', '.'};
    int i;
    for (i = 0; i < 9; ++i) {
        if (c == specialChars[i]) {
            return 1;
        }
    }
    return 0;
}

void getToken(char buffer[], int *type) {
    int i = 0;
    char c = buffer[i];

    if (isKeyword(buffer)) {
        *type = 1;
    } else if (isIdentifier(buffer)) {
        *type = 2;
    } else if (isArithOper(c)) {
        *type = 3;
    } else if (isRelOper(c)) {
        *type = 4;
    } else if (isBitOper(c)) {
        *type = 5;
    } else if (isUnaryOper(c)) {
        *type = 6;
    } else if (isAssignOper(c)) {
        *type = 7;
    } else if (isSpecialChar(c)) {
        *type = 8;
    } else {
        *type = 0;
    }
}

int main() {
    char c, buffer[100];
    int type, i = 0, j = 0;

    //printf("Enter the C code: \n");
    char *filename = "/home/cse1100/SSN/sem6/CL/input.c";
    FILE *fp=fopen(filename,"r");
	if(!fp)
	{
        	printf("\n The file could not be opened / Not available");
		return 0;
	}
	while((c=fgetc(fp))!=EOF) {
        if (isalnum(c) || c == '_') {
            buffer[j++] = c;
        } else {
            buffer[j] = '\0';
            getToken(buffer, &type);
            if (type == 1) {
                printf("%s is a keyword\n", buffer);
            } else if (type == 2) {
                printf("%s is an identifier\n", buffer);
            } else if (type == 3) {
                printf("%c is an arithmetic operator\n", c);
            } else if (type == 4) {
                printf("%c is a relational operator\n", c);
            } else if (type == 5) {
                printf("%c is a bitwise operator\n", c);
            } else if (type == 6) {
                printf("%c is a unary operator\n", c);
            } else if (type == 7) {
                printf("%c is an assignment operator\n", c);
            } else if (type == 8) {
                printf("%c is a special character\n", c);
            }
            j = 0;
        }
    }

    return 0;
}

