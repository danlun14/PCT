set terminal png size 1000, 450 font 'Verdana, 10'
set output 'total.png' 
set title "N-body"
set xlabel 'Num threads'
set ylabel 'Speedup'
set xzeroaxis lt -1
set yzeroaxis lt -1
set key left top

set grid xtics lc rgb  '#555555' lw 1 lt 0
set grid ytics lc rgb  '#555555' lw 1 lt 0

set xtics axis
set ytics axis
plot 'version1.txt' using 1:2 with linespoints lw 1 lt rgb 'purple' title 'Version 1 speedup', \
 'version2.txt' using 1:2 with linespoints lw 1 lt rgb 'red' title 'Version 2 speedup', \
 'version3.txt' using 1:2 with linespoints lw 1 lt rgb 'blue' title 'Version 3 speedup', \
 'version4.txt' using 1:2 with linespoints lw 1 lt rgb 'green' title 'Version 4 speedup', \
 'version5.txt' using 1:2 with linespoints lw 1 lt rgb 'yellow' title 'Version 5 speedup', \
 'linear.txt' using 1:2 with linespoints lw 1 lt rgb 'black' title 'Linear speedup'