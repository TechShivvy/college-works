#!/bin/bash
if [ -f "$1" ]
	then
		select ch in Title_case Upper_case Lower_Case
			do
				if [ $REPLY -le 3 ]
					then
						case $REPLY in
							1) cat $1|tr [:upper:] [:lower:]|sed -e 's/\<./\U&/g'
							break;;
							2) cat $1|tr [:lower:] [:upper:]
							break;;
							3) cat $1|tr [:upper:] [:lower:]
							break;;
						esac
				else
					echo "Invalid option !"
				fi
			break
			done
else
	echo "Invalid argument! File $1 doesn't exist!"
fi 
