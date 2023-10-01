#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
    char c, prev_char = '\0';
    int line_comment = 0, block_comment = 0;
    char *filename="/home/cse1100/SSN/sem6/CL/input.c";
    FILE *fp=fopen(filename,"r");
    while ((c = fgetc(fp)) != EOF) {
        if (prev_char == '/' && c == '/')
            line_comment = 1;
        else if (prev_char == '/' && c == '*')
            block_comment = 1;
        else if (prev_char == '*' && c == '/')
            block_comment = 0;

        if (!line_comment && !block_comment)
            putchar(c);
        else if (c == '\n')
            line_comment = 0;

        prev_char = c;
    }
    return 0;
}
/*

 inComment = 0;
    while ((c = getchar()) != EOF) {
        if (c == '/' && !inComment) {
            if ((c = getchar()) == '*') {
                inComment = 1;
                printf("/*");
            } else {
                ungetc(c, stdin);
                c = '/';
            }
        }
        if (inComment) {
            putchar(c);
            if (c == '*') {
                if ((c = getchar()) == '/') {
                    inComment = 0;
                    printf("/");
                    putchar(c);
                } else {
                    ungetc(c, stdin);
                    c = '*';
                }
            }
            continue;
        }
        if (isalpha(c) || c == '_') {
            i = 0;
            do {
                identifier[i++] = c;
                if (i >= MAX_IDENTIFIER_LENGTH) {
                    printf("Error: identifier too long\n");
                    break;
                }
                c = getchar();
            } while (isalnum(c) || c == '_');
            ungetc(c, stdin);
            identifier[i] = '\0';
            if (isKeyword(identifier)) {
                printf("keyword: %s\n", identifier);
            } else if (isIdentifier(identifier)) {
                printf("identifier: %s\n", identifier);
            } else {
                printf("Error: invalid identifier\n");

*/