#!/bin/bash
arr=(DS Java Unix)
select a in ${arr[@]}
	do
		if [ $REPLY -le 3 ]
			then
				i=1
				echo "User choice = $REPLY Value = $a"
				echo "Modified list : "
				echo "$i) $a"
				((i=i+1))
				for x in ${arr[@]}
					do
						if [[ $x != $a ]]
							then
								echo "$i) $x"
								((i=i+1))
						fi
					done 
		else
			echo "Invalid option !" 
		fi
	break 
	done

