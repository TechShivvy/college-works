#!/bin/bash
read -p "Enter the password " pw
l="${#pw}"    
echo "$pw" | grep [A-Z] | grep [a-z] | grep [0-9]
if [[ $? -ne 0 || l -le 7 ]]; then
	echo "Weak Password"
else
        echo "Strong password" 
fi

