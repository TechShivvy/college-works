BEGIN{
print "Weekly Report"
print "F-name\tL-name\tRate\tHours\tPay"
}
{
pay=($4>40)?$4*$3*1.5:$4*$3 
payroll+=pay
printf("%s\t%s\t%0.2f\t%d\t%0.2f\n",$1,$2,$3,$4,pay)
}
END{
print ""
print "Total Payroll: " payroll
}
