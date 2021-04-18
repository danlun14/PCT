set terminal png size 1000, 450 font 'Verdana, 10'
set output 'result.png' 
set title "DGEMV"
set ylabel 'Speedup'
set xlabel 'Threads'
set xzeroaxis lt -1
set yzeroaxis lt -1
set key left top

set grid xtics lc rgb  '#555555' lw 1 lt 0
set grid ytics lc rgb  '#555555' lw 1 lt 0

set xtics axis
set ytics axis
plot 'linear' using 1:2 with linespoints lw 1 lt rgb 'purple' title 'Linear speedup', \
 'MC_n1E7' using 1:2 with linespoints lw 1 lt rgb 'red' title 'Monte Carlo speedup(n=1E7)', \
 'MC_n1E8' using 1:2 with linespoints lw 1 lt rgb 'blue' title 'Monte Carlo speedup(n=1E8)', \
 'RecInt' using 1:2 with linespoints lw 1 lt rgb 'green' title 'Runge rule speedup'
