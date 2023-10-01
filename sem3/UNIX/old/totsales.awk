{
a[$1]+=$2
}
END{
split("January February March April May June July August September October November December",mon)
for(i in mon) 
{
printf("%s: %d\n",mon[i],a[mon[i]])
}
}
