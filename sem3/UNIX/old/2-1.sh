#!/bin/bash
countlines()
{
     count=$(cat $1|wc -l)
}
read  -p "Enter filename : " filename
countlines $filename
echo "Number of lines : $count"

