ls -l|awk '{if($5>20) print $5,$9}'|sort -nrk1,1
