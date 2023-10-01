#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char buffer[]) {
    char keywords[32][10] = { "auto", "break", "case", "char", "const", "continue", "default",
                             "do", "double", "else", "enum", "extern", "float", "for", "goto",
                             "if", "int", "long", "register", "return", "short", "signed",
                             "sizeof", "static", "struct", "switch", "typedef", "union",
                             "unsigned", "void", "volatile", "while"
                           };
    int i, flag = 0;

    for (i = 0; i < 32; ++i) {
        if (strcmp(keywords[i], buffer) == 0) {
            flag = 1;
            break;
        }
    }

    return flag;
}

int isIdentifier(char buffer[])
{
    if (isalpha(buffer[0]) || buffer[0] == '_') 
    {
        for (int i = 1; i < strlen(buffer); ++i)
            if (!(isalnum(buffer[i]) || buffer[i] == '_'))
                return 0;
    }
    else
    	return 0;
    return 1;
}

int isArithOper(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
        return 1;
    return 0;
}

int isArithAssignOper(char buffer[]) {
    char operators[6][3] = { "+=", "-=", "*=", "/=", "%=", "++"};
    int i, flag = 0;

    for (i = 0; i < 6; ++i) {
        if (strcmp(operators[i], buffer) == 0) {
            flag = 1;
            break;
        }
    }

    return flag;
}

int isRelOper(char c) {
    if (c == '>' || c == '<' || c == '!' || c == '=')
        return 1;
    return 0;
}

int isBitOper(char c) {
    if (c == '&' || c == '|' || c == '^' || c == '~')
        return 1;
    return 0;
}

int isUnaryOper(char c) {
    if (c == '-' || c == '+' || c == '!' || c == '&' || c == '*')
        return 1;
    return 0;
}

int isAssignOper(char c) {
    if (c == '=')
        return 1;
    return 0;
}

int isSpecialChar(char c) {
    if (c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' || c == ',' ||
        c == ';' || c == '.' || c == ':' || c == '?')
        return 1;
    return 0;
}

int isPreprocessor(char buffer[]) {
    if (buffer[0] == '#')
        return 1;
    return 0;
}

int isFunctionCall(char buffer[]) {
    int i, flag = 0;

    for (i = 0; i < strlen(buffer); ++i) {
        if (buffer[i] == '(') {
            flag = 1;
            break;
        }
    }

    return flag;
}

void checkAndPrint(char buffer[]) {
    int i, j = 0, flag = 0;
    char temp[20];

    for (i = 0; i <= strlen(buffer); ++i) {
        if (isalpha(buffer[i]) || isdigit(buffer[i]) || buffer[i] == '_' ||
            isArithOper(buffer[i]) || isRelOper(buffer[i]) ||
            isBitOper(buffer[i]) || isSpecialChar(buffer[i]) || buffer[i]=='#') {
            temp[j++] = buffer[i];
        } else if ((buffer[i] == ' ' || buffer[i] == '\0') && (j != 0)) {
            temp[j] = '\0';
            j = 0;
	    printf("\n---%s---\n",temp);
            if (isKeyword(temp)) {
                printf("%-20s\t- Keyword\n", temp);
            } else if (isIdentifier(temp)) {
                printf("%-20s\t- Identifier\n",temp);
            } else if (isArithOper(temp[0])) {
                printf("%-20c\t- Arithmetic operator\n",temp[0]);
            } else if (isArithAssignOper(temp)) {
                printf("%-20s\t- Arithmetic assignment operator\n",temp);
            } else if (isRelOper(temp[0])) {
                printf("%-20c\t- Relational operator\n", temp[0]);
            } else if (isBitOper(temp[0])) {
                printf("%-20c\t- Bitwise operator\n", temp[0]);
            } else if (isUnaryOper(temp[0])) {
                printf("%-20c\t- Unary operator\n", temp[0]);
            } else if (isAssignOper(temp[0])) {
                printf("%-20c\t- Assignment operator\n", temp[0]);
            } else if (isSpecialChar(temp[0])) {
                printf("%-20c\t- Special character\n", temp[0]);
            } else if (isPreprocessor(temp)) {
                printf("%-20s\t- Preprocessor directive\n", temp);
            } else if (isFunctionCall(temp)) {
                printf("%-20s\t- Function call\n", temp);
            }

            memset(temp, 0, sizeof(temp));
        }
    }
}

int main() {
    char buffer[512];
    int line = 0;
    char *filename = "/home/cse1100/SSN/sem6/CL/input.c";
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening file\n");
        return 0;
    }

    while (fgets(buffer, 512, fp)) {
        checkAndPrint(buffer);
    }

    fclose(fp);
    return 0;
}

