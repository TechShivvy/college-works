lex part1.l
yacc -dvtg part2345.y
gcc lex.yy.c y.tab.c -ll -lm
./a.out
echo "Three address code"
cat threeAddressCode.txt
echo "Optimized code"
cat optimizedCode.txt
echo "Code Generation"
cat codeGeneration.txt

