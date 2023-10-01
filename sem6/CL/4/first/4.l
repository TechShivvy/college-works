%{
#include <stdio.h>
#include "y.tab.h"
//extern YYSTYPE yylval;
int indent_level = 0;
%}

%option noyywrap
%%

"def"               { return DEF; }
"("                 { return LPAREN; }
")"                 { return RPAREN; }
":"                 { return COLON; }
";"                 { return SEMI; }
"="                 { return ASSIGN; }
"["                 { return LBRACKET; }
"]"                 { return RBRACKET; }
","                 { return COMMA; }
"{"                 { return LBRACE; }
"}"                 { return RBRACE; }
"if"                { return IF; }
"else"              { return ELSE; }
"for"               { return FOR; }
"in"                { return IN; }
"range"             { return RANGE; }
"print"             { return PRINT; }
"Unsorted Array"    { return UNSORTED; }
"Sorted Array in Ascending Order:" { return SORTED; }
[0-9]+              { yylval.num = atoi(yytext); return NUMBER; }
[a-zA-Z][a-zA-Z0-9_]* { yylval.str = strdup(yytext); return NAME; }
[\n]+               {return NEWLINE; }
^[ \t]+              {
    int new_indent = yyleng - 1; // length of whitespace minus one
    if (new_indent > indent_level) {
        // increase indent level
        indent_level = new_indent;
        return INDENT;
    } else if (new_indent < indent_level) {
        // decrease indent level
        while (new_indent < indent_level) {
            indent_level--;
            return DEDENT;
        }
    }
}
[ \t]+		    { }	
.                   { printf("Unknown character: '%s'\n", yytext); }
%%
