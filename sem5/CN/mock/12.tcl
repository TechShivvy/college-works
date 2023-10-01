set ns [new Simulator]
#$ns rtproto DV

set tr [open out.tr w]
$ns trace-all $tr
set nf [open out.nam w]
$ns namtrace-all $nf

set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]

$n1 label "node 1"
$n2 label-color blue

$ns color 1 red
$ns color 2 blue

$ns duplex-link $n1 $n3 10Mb 10ms DropTail
$ns duplex-link $n2 $n3 10Mb 10ms DropTail
$ns duplex-link $n3 $n4 2Mb 10ms DropTail
$ns duplex-link $n4 $n5 10Mb 10ms DropTail
$ns duplex-link $n4 $n6 10Mb 10ms DropTail

$ns duplex-link-op $n1 $n3 orient right-down
$ns duplex-link-op $n2 $n3 orient right-up
$ns duplex-link-op $n3 $n4 orient right
$ns duplex-link-op $n4 $n5 orient right-up
$ns duplex-link-op $n4 $n6 orient right-down

$ns queue-limit $n3 $n4 10

set tcp15 [new Agent/TCP]
$ns attach-agent $n1 $tcp15
set sink1 [new Agent/TCPSink]
$ns attach-agent $n5 $sink1
$ns connect $tcp15 $sink1
$tcp15 set fid_ 1

set tcp26 [new Agent/TCP]
$ns attach-agent $n2 $tcp26
set sink2 [new Agent/TCPSink]
$ns attach-agent $n6 $sink2
$ns connect $tcp26 $sink2
$tcp26 set fid_ 2

set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp15
set ftp2 [new Application/FTP]
$ftp2 attach-agent $tcp26



proc finish {} {
global ns nf
$ns flush-trace
close $nf
exec nam out.nam &
exit 0
}

$ns at 0.0 "$ftp1 start"
$ns at 0.5 "$ftp2 start"
$ns rtmodel-at 3.0 down $n3 $n4 
$ns rtmodel-at 3.5 up $n3 $n4
$ns at 4.0 "$ftp1 stop"
$ns at 4.5 "$ftp2 stop"
$ns at 6.0 "finish"
$ns run
