#!/bin/bash
read -p "Enter cost price: " cp
read -p "Enter selling price: " sp
if [ "$sp" -ge "$cp" ]; then
	echo "profit=$(($sp-$cp))"
else
	echo "loss=$(($cp-$sp))"
fi
