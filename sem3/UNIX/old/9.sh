read -p "Enter: " fd           
if test -f $fd; then
	echo "It is file"
elif test -d $fd; then
	echo "It is a Directory"
else
	echo "It is not reg file or direc!"
fi
ls -ld $fd
