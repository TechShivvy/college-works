read -p "Enter the temp in F:" f
echo "Temp in C: $(echo "($f-32)*5/9"|bc)"
