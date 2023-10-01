#!/bin/bash
if test ! -e $arg; then
	echo "File doesnt exist"
	exit 1;
fi
echo "File exists"
if test -f $arg; then
	echo "Regular file"
elif test -d $arg; then
	echo "Directory"
fi
if test -r $arg; then
	echo "Readable"
else
	echo "Not readable"
fi
if test -w $arg; then
	echo "Writable"
else
	echo "Not writable"
fi
if test -x $arg; then
	echo "Executable"
else
	echo "Not executable"
fi
if test -O $arg; then
	echo "You are the owner of the file"
else
	echo "You aren't the owner of the file"
fi
