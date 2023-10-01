BEGIN{
print "\nInventory Report\n"
print "Part No.\tPrice\tQuantity on Hand\tReorder point\tMinimum Order\tOrder Amount"
}
{   
oa=($3<$4)?$4+$5-$3:0 
printf("%d\t\t%d\t%d\t\t\t%d\t\t%d\t\t%d\n",$1,$2,$3,$4,$5,oa)
}
END{
print "\nEND OF REPORT"
}
