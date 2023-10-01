#!/bin/bash
echo {a,b,c,c}{c,c,e,f} | tr ' ' '\n' | sort | uniq | awk '
{
	n += NR
}
END {
	print n
}
'
