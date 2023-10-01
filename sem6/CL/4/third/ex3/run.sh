lex another.l
yacc -d another.y
gcc -w y.tab.c lex.yy.c
./a.out sample.txt