#!/bin/bash
c=`cat $1 | wc -c`
w=`cat $1 | wc -w`
l=`grep -c "." $1`
echo Number of characters in $1 is $c
echo Number of words in $1 is $w
echo Number of lines in $1 is $l
echo
l2=`grep -c "." $2`
echo Number of lines in both $1 n $2 is $(($l2+$l))
