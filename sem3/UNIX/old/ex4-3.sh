#!/bin/bash
for arg; do
	echo "$arg :"
	export arg
	sh ./v2-10.sh
	echo ""
done
