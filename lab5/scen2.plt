set term png\
    size 750, 2500\
    enhanced\
    font 'Arial, 14'

set output 'result2.png'

set xzeroaxis lt -1
set yzeroaxis lt -1

set grid xtics lc rgb  '#555555' lw 0 lt 0
set grid ytics lc rgb  '#555555' lw 0 lt 0

set ylabel "Speedup" 
set xlabel "Threads" 

set xtics axis
set ytics axis

set key left top

set multiplot \
	title "Quick Sort N fixed" \
	layout 5, 1 \
	scale 0.9 \
	offset 0.01, 0 \

set title 'N 10000'
plot 'result/threashold10_N10000.txt' using 1:2 with linespoints lw 1 lt rgb 'red' title 'Threashold 10',\
    'result/threashold100_N10000.txt' using 1:2 with linespoints lw 1 lt rgb 'green' title 'Threashold 100',\
    'result/threashold1000_N10000.txt' using 1:2 with linespoints lw 1 lt rgb 'blue' title 'Threashold 1000',\
    'result/threashold10000_N10000.txt' using 1:2 with linespoints lw 1 lt rgb 'black' title 'Threashold 10000',\
    'linear_sheet.txt' using 1:2 with linespoints lw 1 lt rgb 'orange' title 'Linear speedup'

set title 'N 100000'
plot 'result/threashold10_N100000.txt' using 1:2 with linespoints lw 1 lt rgb 'red' title 'Threashold 10',\
    'result/threashold100_N100000.txt' using 1:2 with linespoints lw 1 lt rgb 'green' title 'Threashold 100',\
    'result/threashold1000_N100000.txt' using 1:2 with linespoints lw 1 lt rgb 'blue' title 'Threashold 1000',\
    'result/threashold10000_N100000.txt' using 1:2 with linespoints lw 1 lt rgb 'black' title 'Threashold 10000',\
    'linear_sheet.txt' using 1:2 with linespoints lw 1 lt rgb 'orange' title 'Linear speedup'

set title 'N 1000000'
plot 'result/threashold10_N1000000.txt' using 1:2 with linespoints lw 1 lt rgb 'red' title 'Threashold 10',\
    'result/threashold100_N1000000.txt' using 1:2 with linespoints lw 1 lt rgb 'green' title 'Threashold 100',\
    'result/threashold1000_N1000000.txt' using 1:2 with linespoints lw 1 lt rgb 'blue' title 'Threashold 1000',\
    'result/threashold10000_N1000000.txt' using 1:2 with linespoints lw 1 lt rgb 'black' title 'Threashold 10000',\
    'linear_sheet.txt' using 1:2 with linespoints lw 1 lt rgb 'orange' title 'Linear speedup'

set title 'N 10000000'
plot 'result/threashold10_N10000000.txt' using 1:2 with linespoints lw 1 lt rgb 'red' title 'Threashold 10',\
    'result/threashold100_N10000000.txt' using 1:2 with linespoints lw 1 lt rgb 'green' title 'Threashold 100',\
    'result/threashold1000_N10000000.txt' using 1:2 with linespoints lw 1 lt rgb 'blue' title 'Threashold 1000',\
    'result/threashold10000_N10000000.txt' using 1:2 with linespoints lw 1 lt rgb 'black' title 'Threashold 10000',\
    'linear_sheet.txt' using 1:2 with linespoints lw 1 lt rgb 'orange' title 'Linear speedup'

set title 'N 100000000'
plot 'result/threashold10_N100000000.txt' using 1:2 with linespoints lw 1 lt rgb 'red' title 'Threashold 10',\
    'result/threashold100_N100000000.txt' using 1:2 with linespoints lw 1 lt rgb 'green' title 'Threashold 100',\
    'result/threashold1000_N100000000.txt' using 1:2 with linespoints lw 1 lt rgb 'blue' title 'Threashold 1000',\
    'result/threashold10000_N100000000.txt' using 1:2 with linespoints lw 1 lt rgb 'black' title 'Threashold 10000',\
    'linear_sheet.txt' using 1:2 with linespoints lw 1 lt rgb 'orange' title 'Linear speedup'

