#!/bin/bash
read -p  "Enter exp: " str
read -p "Enter pat: " pat
s=${str//"$pat"/;}
s=$(echo $s | tr -c ';' ' ')
echo $s | wc -w
