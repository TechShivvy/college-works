#!/bin/bash
read -p "Enter a word: " str
if [ "$str" == $(echo "$str" |rev) ]; then
	echo Yes, it is a palindrome!
else
	echo No, it is not a palindrome.
fi

