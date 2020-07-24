#!/bin/sh
gnuplot<<EOF
set output "leprat_corrmsq_vma.ps" 
set terminal postscript enhanced
set term post color "Times-Roman" 20
set size ratio 1
set title "Upsilon Leptonic Decay Width Ratio"
set xrange [0:0.24]
set yrange [0:1.2]
set xlabel "m_{u/d}(GeV)"
set ylabel "({/Symbol G}_{ee}(2s)/{/Symbol G}_{ee}(1s))(M_{2s}/M_{1s})^2"
set label "\245" at 0.23,-0.06 font "Symbol,30"
set label "~" at 0.21,-0.025 rotate font "Symbol,34"
set label "~" at 0.212,-0.025 rotate font "Symbol,34"
set pointsize 1.2
plot "leprat_corrmsq_vma.dat" index 0 using 1:2:3 title 'Full Lattice QCD' w yerrorbars 1 4, \
     "leprat_corrmsq_vma.dat" index 1 using 1:2:3 title 'Quenched Lattice QCD' with yerrorbars 3 3, \
     "leprat_corrmsq_vma.dat" index 2 using 1:2:3 title 'Experimental Upsilon' with yerrorbars 2 2
     
EOF




