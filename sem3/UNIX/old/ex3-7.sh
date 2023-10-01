#!/bin/bash
read -p "Enter file and directory" file dir
if [[ ! -e $file ]]; then
	touch $file
fi
if [[ ! -e $dir ]]; then
	mkdir $dir
fi
