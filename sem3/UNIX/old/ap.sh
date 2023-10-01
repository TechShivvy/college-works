read -p "Enter the l n b of rec: " l b
read -p "Enter the r of circle: " r 
echo "Rectangle: "
ra=$(echo "$l*$b"|bc)
rp=$(echo "2*($l+$b)"|bc)
ca=$(echo "3.14*$r*$r"|bc)
cc=$(echo "2*3.14*$r"|bc)
echo "Area: $ra | Perimeter: $rp"
echo "Circle: "
echo "Area: $ca | Circumference: $cc"
