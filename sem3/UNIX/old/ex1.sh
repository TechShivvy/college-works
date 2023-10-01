Script started on 2021-12-13 09:33:34+05:30 [TERM="xterm-256color" TTY="/dev/pts/0" COLUMNS="58" LINES="29"]
]0;cse1100@brokolee: ~[01;32mcse1100@brokolee[00m:[01;34m~[00m$ cat ex1-15[K2.sh
cat: ex1-12.sh: No such file or directory
]0;cse1100@brokolee: ~[01;32mcse1100@brokolee[00m:[01;34m~[00m$ cat ex1-12.sh[C[1Pex1-12.sh>ex1-12.sh
#!/bin/bash
echo Enter marks:
read m{1..5}
for i in {1..5}; do
	((total+="m"$i))
done
]0;cse1100@brokolee: ~[01;32mcse1100@brokolee[00m:[01;34m~[00m$ cat>ex1-12.sh[1Pex1-12.sh[1Pex1-12.sh[1Pex1-12.sh[1Pex1-12.shbex1-12.shaex1-12.shsex1-12.shhex1-12.sh ex1-12.sh[C[C[C[C[C[C[C[C[C 50 50 50 50 50
Enter marks:
50 50 50 50 50
]0;cse1100@brokolee: ~[01;32mcse1100@brokolee[00m:[01;34m~[00m$ bash ex1-12.sh 50 50 50 50 50[C[C[C[C[C[C[C[C[C[C[C[C[C[C[C[C[C[C[C[C[16Pcat>ex1-12.shbash ex1-12.sh 50 50 50 50 50[K[K[K[K[K[K[K[K[K[K[K[K[K[K[K][K
Enter marks:
50 05 05     50 50 505 0    100
]0;cse1100@brokolee: ~[01;32mcse1100@brokolee[00m:[01;34m~[00m$ bash ex1-12.sh 50 50 50 50 50[C[C[C[C[C[C[C[C[C[C[C[C[C[C[C[C[C[C[C[C[16Pcat>ex1-12.sh
#!/bin/bash
echo Enter marks:
read m{1..5}
for i in {1..5}; do
	((total+="m"$i))
done
echo Total = $total
]0;cse1100@brokolee: ~[01;32mcse1100@brokolee[00m:[01;34m~[00m$ cat>ex1-12.shbash ex1-12.sh
Enter marks:
50 50 50 50 100
Total = 300
]0;cse1100@brokolee: ~[01;32mcse1100@brokolee[00m:[01;34m~[00m$ script [K[K[K[K[K[K[Kexit
exit

Script done on 2021-12-13 09:51:36+05:30 [COMMAND_EXIT_CODE="0"]
