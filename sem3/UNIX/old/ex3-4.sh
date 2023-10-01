#!/bin/bash
temp=$1
while [ $temp -ne 0 ]
do
    reverse=$reverse$((temp%10))
    temp=$((temp/10))
done
echo "Reverse of $1 is $reverse"
