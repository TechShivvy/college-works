#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_IDENTIFIER_LENGTH 32
#define NUM_KEYWORDS 32
#define NUM_ARITH_OPERS 6
#define NUM_ARITH_ASSIGN_OPERS 6
#define NUM_LOGICAL_OPERS 3

const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

const char arithOpers[] = {'+', '-', '*', '/', '%', '^'};

const char *arithAssignOpers[] = {
    "+=", "-=", "*=", "/=", "%=", "^="
};

const char *logicalOpers[] = {
    "&&", "||", "!"
};

int isKeyword(const char *identifier) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(identifier, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int isArithOper(char oper) {
    for (int i = 0; i < NUM_ARITH_OPERS; i++) {
        if (oper == arithOpers[i]) {
            return 1;
        }
    }
    return 0;
}

int isArithAssignOper(const char *oper) {
    for (int i = 0; i < NUM_ARITH_ASSIGN_OPERS; i++) {
        if (strcmp(oper, arithAssignOpers[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int isLogicalOper(const char *oper) {
    for (int i = 0; i < NUM_LOGICAL_OPERS; i++) {
        if (strcmp(oper, logicalOpers[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int isIdentifier(const char *identifier) {
    if (!isalpha(identifier[0]) && identifier[0] != '_') {
        return 0;
    }
    for (int i = 1; identifier[i]; i++) {
        if (!isalnum(identifier[i]) && identifier[i] != '_') {
            return 0;
        }
    }
    return 1;
}

int main() {
    char c, next, identifier[MAX_IDENTIFIER_LENGTH + 1];
    int i, inComment;

    inComment = 0;
    char *filename = "/home/cse1100/SSN/sem6/CL/input.c";
    FILE *fp=fopen(filename,"r");
	if(!fp)
	{
        	printf("\n The file could not be opened / Not available");
		return 0;
	}
	while((c=fgetc(fp))!=EOF) {
        if (inComment) {
            if (c == '*' && (next = fgetc(fp)) == '/') {
                inComment = 0;
                c = fgetc(fp);
            }
        } else if (c == '/' && (next = fgetc(fp)) == '*') {
            inComment = 1;
            c = fgetc(fp);
        } else if (isalpha(c) || c == '_') {
            i = 0;
            do {
                identifier[i++] = c;
                c = fgetc(fp);
            } while (isalnum(c) || c == '_');
            identifier[i] = '\0';
            if (isKeyword(identifier)) {
                printf("Keyword: %s\n", identifier);
            } else if (isIdentifier(identifier)) {
                printf("Identifier: %s\n", identifier);
            }
        } else if (isdigit(c)) {
            printf("Number: %c\n", c);
            while (isdigit(c = fgetc(fp)))
                printf("Number: %c\n", c);
        } else if (isArithOper(c)) {
            printf("Arithmetic operator: %c\n", c);
        } else {
            i = 0;
            identifier[i++] = c;
            while (!isspace(c = fgetc(fp)) && !isdigit(c) && !isalpha(c) && c != EOF) {
                identifier[i++] = c;
                if (isArithAssignOper(identifier)) {
                    printf("Arithmetic assignment operator: %s\n", identifier);
                    break;
                } else if (isLogicalOper(identifier)) {
                    printf("Logical operator: %s\n", identifier);
                    break;
                }
            }
            if (!isArithAssignOper(identifier) && !isLogicalOper(identifier)) {
                printf("Special character: %s\n", identifier);
            }
        }
    }
    return 0;
}

