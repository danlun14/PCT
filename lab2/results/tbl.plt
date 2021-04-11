set terminal png size 1000, 450 font 'Verdana, 10'
set output 'result.png' 
set title "DGEMV"
set ylabel 'Num threads'
set xlabel 'Speedup'
set xzeroaxis lt -1
set yzeroaxis lt -1
set key left top

set grid xtics lc rgb  '#555555' lw 1 lt 0
set grid ytics lc rgb  '#555555' lw 1 lt 0

set xtics axis
set ytics axis
plot 'linear.txt' using 1:2 with linespoints lw 1 lt rgb 'purple' title 'linear', \
 'par15.txt' using 1:2 with linespoints lw 1 lt rgb 'red' title 'N=15000', \
 'par25.txt' using 1:2 with linespoints lw 1 lt rgb 'blue' title 'N=25000', \
 'par40.txt' using 1:2 with linespoints lw 1 lt rgb 'green' title 'N=40000(LIM)', \
 'par_init15.txt' using 1:2 with linespoints lw 1 lt rgb 'yellow' title 'N=15000(par init)'