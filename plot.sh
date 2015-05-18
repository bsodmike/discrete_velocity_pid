#!/bin/bash

for FILE in *.dat; do
  gnuplot <<- EOF
  set yrange [0:2200]
  set term png
  set output "output.png"
  plot "${FILE}" using 1:2 with linespoints title 'output',\
    "${FILE}" using 1:3 with lines title 'e0',\
    "${FILE}" using 1:4 with lines title 'e1',\
    "${FILE}" using 1:5 with lines title 'e2',\

EOF
done

