#!/bin/bash
n=`grep -o $1 $2 | wc -l `
echo "No. of occurrences of $1 in file $2 : $n"

