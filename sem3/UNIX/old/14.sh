#!/bin/bash
touch File{1..8}
perm=(701 400 300 676 045 177 234 507)
for i in {1..8}; do
	file="File"$i
	chmod ${perm[$((i-1))]} $file
	ls -l $file
	if test -r $file; then
		let "r+=1"
	fi
	if test -w $file; then
		let "w+=1"
	fi
	if test -x $file; then
		let "x+=1"
	fi
done
echo -e "\nNo. of:\nReadable Files: $r\nWritable Files: $w\nExecutable Files: $x"
