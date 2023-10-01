#!/bin/bash                       
mon=`date | cut -d \  -f3`
echo $mon>date.txt
alias getDay=`date | cut -d' ' -f1| cat > day.txt`
$getDay
