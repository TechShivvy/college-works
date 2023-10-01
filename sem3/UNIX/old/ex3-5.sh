#!/bin/bash
if [ -d "mydir" ]
	then
		echo "Directory mydir exists"
		l=`ls -l mydir|wc -l`
		((l=l-1))
		echo "Total no. of files in mydir : $l"
else
		mkdir mydir
fi
for i in "$@"
	do
		if [ -f "$i" ]
			then
				echo "File $i exists"
		else
			
				touch  "$i"
				mv $i mydir
		fi
	done
echo "Contents of mydir : "
echo "$(ls -l mydir|tail +2)"

