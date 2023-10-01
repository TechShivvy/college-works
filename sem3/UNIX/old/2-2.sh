#!/bin/bash
countwords()
{
        count=$(cat $file | grep -c $word)
}
read -p "Enter filename : " file
if test -f $file ;then
        read -p "Enter a word to search: " word
        countwords
        echo "Number of occurences of the word : $count"
else
        echo "File not found"
fi
