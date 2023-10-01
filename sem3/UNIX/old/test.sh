declare $( awk -F':' '{print "aa[$2]="$4}' emp.txt )
echo ${aa[*]}
