#!/bin/bash
gradecalculator()
{
	if [ $a -ge 91 ]; then 
		grade="S"
	elif [ $a -ge 81 ] ; then
		grade="A"
	elif [ $a -ge 71 ]; then
		grade="B"
	elif [ $a -ge 61 ]; then
		grade="C"
	elif [ $a -ge 57 ]; then
		grade="D"
	elif [ $a -ge 51 ]; then
		grade="E"
	else
		grade="U"
	fi
	echo "$a : $grade"
}
echo grades:
for a; do
	gradecalculator $a
done
