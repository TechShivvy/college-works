#!/bin/bash
read -p "Enter file path to copy: " filename
read -p "Enter destination folder path: " path
until ( cp $filename $path ) 
do
        echo "Waiting to copy"
        sleep 5
done

