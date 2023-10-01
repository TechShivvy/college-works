for i in `seq 1 2 5`; do
	echo "Tables of $i"
	for j in {1..10}; do
		echo "$i*$j=$(( $i*$j ))"
	done
	echo
done

