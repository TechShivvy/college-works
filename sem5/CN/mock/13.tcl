set ns [new Simulator]
#$ns rtproto LS

set nf [open out.nam w]
$ns namtrace-all $nf
set tr [open out.tr w]
$ns trace-all $tr

set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]
set n7 [$ns node]
set n8 [$ns node]

$ns duplex-link $n1 $n2 10Mb 10ms DropTail
$ns duplex-link $n2 $n3 10Mb 10ms DropTail
$ns duplex-link $n3 $n4 10Mb 10ms DropTail
$ns duplex-link $n4 $n5 10Mb 10ms DropTail
$ns duplex-link $n5 $n6 10Mb 10ms DropTail
$ns duplex-link $n6 $n7 10Mb 10ms DropTail
$ns duplex-link $n7 $n8 10Mb 10ms DropTail
$ns duplex-link $n8 $n1 10Mb 10ms DropTail

$ns duplex-link-op $n1 $n2 orient left-down
$ns duplex-link-op $n2 $n3 orient down
$ns duplex-link-op $n3 $n4 orient down
$ns duplex-link-op $n4 $n5 orient right-down
$ns duplex-link-op $n5 $n6 orient right-up
$ns duplex-link-op $n6 $n7 orient up
$ns duplex-link-op $n7 $n8 orient up
$ns duplex-link-op $n8 $n1 orient left-up

$n1 label "node1"
$n1 label-color blue

$ns color 1 blue

proc COMMENTED_OUT {} {
set tcp [new Agent/TCP]
$ns attach-agent $n1 $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n5 $sink
$ns connect $tcp $sink

set ftp [new Application/FTP]
$ftp attach-agent $tcp
}

set udp [new Agent/UDP]
$udp set fid_ 1
$ns attach-agent $n1 $udp

set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp

set null [new Agent/Null]
$ns attach-agent $n5 $null
$ns connect $udp $null

proc finish {} {
global ns nf
$ns flush-trace
close $nf
exec nam out.nam &
exit 0
}

#$ns at 0.0 "$ftp start"
#$ns rtmodel-at 1.0 down $n3 $n4
#$ns rtmodel-at 2.0 up $n3 $n4

#$ns at 2.8 "$ftp stop"

$ns at 0.5 "$cbr start"

$ns rtmodel-at 1.0 down $n3 $n4
$ns rtmodel-at 1.0 down $n4 $n5

#$ns rtmodel-at 2.0 up $node3 $node4
#$ns rtmodel-at 2.0 up $node4 $node5

$ns at 3.0 "$cbr start"
$ns at 4.0 "$cbr stop"
$ns at 5.0 "finish"
$ns run

