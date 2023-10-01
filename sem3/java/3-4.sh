#!/bin/bash
i=1
ans=1
read -p "Enter base number : " m
read -p "Enter power : " n
if [ $n -gt 0 ] ; then
        while [ "$i" -le "$n" ]
        do
                (( ans=$ans*$m ))
                let "i+=1"
        done
        echo "Exponent is : "$ans
else
        echo "Enter a positive power "
fi

