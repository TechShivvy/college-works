#!/bin/bash
echo Enter marks:
read m{1..5}
for i in {1..5}; do
	((total+="m"$i))
done
echo Total = $total
