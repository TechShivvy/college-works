#!/bin/bash
mkcd(){
	readarray -d / -t dir <<< "$1"
	for i in "${dir[@]}"
		do
			`mkdir $i`
		done
	cd $i
	pwd
}
mkcd d1/d2/d3

