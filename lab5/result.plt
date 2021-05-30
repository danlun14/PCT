set term png\
    size 1600, 1100\
    enhanced\
    font 'Arial, 14'

set output 'result.png'

set xzeroaxis lt -1
set yzeroaxis lt -1

set grid xtics lc rgb  '#555555' lw 1 lt 0
set grid ytics lc rgb  '#555555' lw 1 lt 0

set xtics 1
set ytics 1

set xlabel "Threads"
set ylabel "Speedup"

set key left top

set tmargin 5
set bmargin 5
set lmargin 5
set rmargin 5

set multiplot \
	title "Quick sort" \
	layout 2, 2 \
	scale 1.05 \
	offset 0.01, 0 \

set title 'Threashold 10'
plot 'result/th10-N1000.txt' using 1:2 with linespoints lw 1 lt rgb 'purple' title 'N 1000',\
    'result/th10-N10000.txt' using 1:2 with linespoints lw 1 lt rgb 'red' title 'N 10000',\
    'result/th10-N100000.txt' using 1:2 with linespoints lw 1 lt rgb 'green' title 'N 100000',\
    'result/th10-N1000000.txt' using 1:2 with linespoints lw 1 lt rgb 'blue' title 'N 1000000',\
    'result/th10-N10000000.txt' using 1:2 with linespoints lw 1 lt rgb 'black' title 'N 10000000',\
    'linear.txt' using 1:2 with linespoints lw 1 lt rgb 'orange' title 'linear'

set title 'Threashold 100'
plot 'result/th100-N1000.txt' using 1:2 with linespoints lw 1 lt rgb 'purple' title 'N 1000',\
    'result/th100-N10000.txt' using 1:2 with linespoints lw 1 lt rgb 'red' title 'N 10000',\
    'result/th100-N100000.txt' using 1:2 with linespoints lw 1 lt rgb 'green' title 'N 100000',\
    'result/th100-N1000000.txt' using 1:2 with linespoints lw 1 lt rgb 'blue' title 'N 1000000',\
    'result/th100-N10000000.txt' using 1:2 with linespoints lw 1 lt rgb 'black' title 'N 10000000',\
    'linear.txt' using 1:2 with linespoints lw 1 lt rgb 'orange' title 'linear'

set title 'Threashold 1000'
plot 'result/th1000-N1000.txt' using 1:2 with linespoints lw 1 lt rgb 'purple' title 'N 1000',\
    'result/th1000-N10000.txt' using 1:2 with linespoints lw 1 lt rgb 'red' title 'N 10000',\
    'result/th1000-N100000.txt' using 1:2 with linespoints lw 1 lt rgb 'green' title 'N 100000',\
    'result/th1000-N1000000.txt' using 1:2 with linespoints lw 1 lt rgb 'blue' title 'N 1000000',\
    'result/th1000-N10000000.txt' using 1:2 with linespoints lw 1 lt rgb 'black' title 'N 10000000',\
    'linear.txt' using 1:2 with linespoints lw 1 lt rgb 'orange' title 'linear'

set title 'Threashold 10000'
plot 'result/th10000-N1000.txt' using 1:2 with linespoints lw 1 lt rgb 'purple' title 'N 1000',\
    'result/th10000-N10000.txt' using 1:2 with linespoints lw 1 lt rgb 'red' title 'N 10000',\
    'result/th10000-N100000.txt' using 1:2 with linespoints lw 1 lt rgb 'green' title 'N 100000',\
    'result/th10000-N1000000.txt' using 1:2 with linespoints lw 1 lt rgb 'blue' title 'N 1000000',\
    'result/th1000-N10000000.txt' using 1:2 with linespoints lw 1 lt rgb 'black' title 'N 10000000',\
    'linear.txt' using 1:2 with linespoints lw 1 lt rgb 'orange' title 'linear'