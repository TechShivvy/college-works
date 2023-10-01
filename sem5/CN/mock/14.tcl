set ns [new Simulator]
$ns rtproto LS

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
$ns duplex-link-op $n2 $n3 queuePos 0.5

$ns queue-limit $n3 $n4 7

proc finish {} {
global ns nf
$ns flush-trace
close $nf
exec nam out.nam &
#exec xgraph congestionreno.xg -geometry 300x300 &
#exec xgraph congestiontahoe.xg -geometry 300x300 &
exit 0
}

set tcp [new Agent/TCP]
$ns attach-agent $n1 $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n5 $sink
$ns connect $tcp $sink

set tcpr [new Agent/TCP/Reno]
$ns attach-agent $n2 $tcpr
set sinkr [new Agent/TCPSink]
$ns attach-agent $n6 $sinkr
$ns connect $tcpr $sinkr

set ftp [new Application/FTP]
$ftp attach-agent $tcp
set ftpr [new Application/FTP]
$ftpr attach-agent $tcpr

$tcp attach $tr
$tcp tracevar cwnd_
$tcp tracevar ssthresh_
$tcp tracevar ack_
$tcp tracevar maxseq_

proc plotWindow {tcpSource outfile} {
   global ns
   set now [$ns now]
   set cwnd [$tcpSource set cwnd_]
   puts  $outfile  "$now $cwnd"
   $ns at [expr $now+0.1] "plotWindow $tcpSource  $outfile"
}

set outfile [open  "congestiontahoe.xg"  w]
$ns  at  0.0  "plotWindow $tcp  $outfile"

set outfile [open  "congestionreno.xg"  w]
$ns  at  0.0  "plotWindow $tcpr  $outfile"

$ns at 0.0 "$ftp start"
$ns at 0.0 "$ftpr start"
$ns at 6.0 "finish"

$ns run

