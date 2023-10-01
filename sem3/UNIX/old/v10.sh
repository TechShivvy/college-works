if test -f $arg; then
	echo "It is a file"
elif test -d $arg; then
		echo "It is a Directory"
else
	echo "It is not reg file or direc!"
fi
ls -ld $arg
