#!/bin/bash

for FILE in *.dat; do
  gnuplot <<- EOF
  set yrange [0:2200]
  set term png
  set output "output.png"
  set style fill solid 0.5
  plot "${FILE}" using 1:2 smooth freq w boxes lc rgb"grey" title 'output',\
    "${FILE}" using 1:3 smooth freq w boxes lc rgb"red" title 'sensor',\
    "${FILE}" using 1:4 with lines title 'e0',\
    "${FILE}" using 1:5 with lines title 'e1',\
    "${FILE}" using 1:6 with lines title 'e2',\

EOF
done

