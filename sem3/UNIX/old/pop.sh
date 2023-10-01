#!/bin/bash
pop=80000
men=$(echo "$pop*0.52"|bc)
women=$(echo "$pop-$men"|bc)
tl=$(echo "$pop*0.52"|bc)
im=$(echo "$men*0.65"|bc)
iw=$(echo "$tl-$im"|bc)
echo "Population: $pop"
echo "No of Men: $men" 
echo "No of Women : $women"
echo "No. of illiterate ppl: $tl"
echo "No. of ill. Men: $im"
echo "No. of ill. women: $iw"
