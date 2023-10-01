#!/bin/bash
if test -f "$1" ; then
while true; do
		PS3="Choice: "
		select ch in Title_case Upper_case Lower_Case Exit; do
				if [ $REPLY -le 4 ];then
						y=($(cat $1))
						echo
						case $REPLY in
							1) cat $1|tr [:upper:] [:lower:]|sed -e 's/\<./\U&/g';;
							2) cat $1|tr [:lower:] [:upper:];;
							3) cat $1|tr [:upper:] [:lower:];;
							4) exit 1;;
						esac
						echo 
				else
					echo -e "\nInvalid option !\n"
				fi
			break
			done
done
else
	echo "Invalid argument! File $1 doesn't exist\n"
fi 

