read -p "Enter your basic pay " bp
TA=$(echo "0.15 * $bp"|bc)
DA=$(echo "0.02 * $bp"|bc) 
HRA=$(echo "0.1 * $bp"|bc)
IT=$(echo "0.05 * $bp"|bc)
PF=$(echo "0.1 * $bp"|bc)
netSal=$(echo "$bp + $TA + $DA +$HRA - $IT -$PF"|bc) 
echo "Net Salary: $netSal"
