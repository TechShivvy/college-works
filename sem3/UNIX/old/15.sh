#!/bin/bash
v0="1234abczip1234abc"
echo "v0=$v0"
#v1=$(echo $v0 | sed 's/abc/ABC/')
v1=${v0/abc/ABC}
echo "v1=$v1"
#v2=$(echo $v0 | sed 's/abc/ABC/g')
v2=${v0//abc/ABC}
echo "v2=$v2"
pat="1*4"
v3=${v0#1*4}
echo "v3=$v3"
v3=$(echo $v0 | rev)
v4=$(echo ${v3%%4*1} | rev )
echo "v4=$v4"
