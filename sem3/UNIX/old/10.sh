if test -f $1; then
	echo "It is a file"
elif test -d $1; then
		echo "It is a Directory"
else
	echo "It is not reg file or direc!"
fi
ls -ld $1
