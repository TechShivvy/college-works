BEGIN{
print "\nPayroll Register"
print "\nEmployee No.\tDepartment\tPay Rate\tExempt\tHours Worked\tBase Pay\tOvertime Pay\n"
}
{
bp=$3*$5
op=($4=="N" && $5>40)?bp*1.5:0
tot+=(op!=0)?op:bp
printf("%d\t\t%d\t\t%0.2f\t\t%c\t%d\t\t%0.2f\t\t%0.2f\n",$1,$2,$3,$4,$5,bp,op)
}
END{
print "\nTotal Payroll: " tot
}
