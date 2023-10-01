y=(for i in $(ls -d */); do echo ${i%%/}; done)
for i in y; do
	echo i
