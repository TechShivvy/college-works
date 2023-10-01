#!/bin/bash
finfo () {
if test ! -e $1; then
	echo "File doesnt exist"
	exit 1;
fi
echo "File exists"
if test -f $1; then
	echo "Regular file"
elif test -d $1; then
	echo "Directory"
fi
if test -r $1; then
	echo "Readable"
else
	echo "Not readable"
fi
if test -w $1; then
	echo "Writable"
else
	echo "Not writable"
fi
if test -x $1; then
	echo "Executable"
else
	echo "Not executable"
fi
if test -O $1; then
	echo "You are the owner of the file"
else
	echo "You aren't the owner of the file"
fi
}

for arg; do
	echo "$arg :"    
	finfo $arg
	echo ""
done
