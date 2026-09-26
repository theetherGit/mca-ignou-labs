# plot_cwnd.gp -- MCSL-223 Session 9, Q24 (gnuplot alternative to plot_cwnd.py)
# Run after the simulation:  gnuplot plot_cwnd.gp
# cwnd.txt columns: time (s), congestion window (bytes)

set terminal pngcairo size 900,540
set output "cwnd.png"
set title "TCP cwnd on the 1 Mbit/s dumbbell bridge under UDP load"
set xlabel "Time (s)"
set ylabel "Congestion window (bytes)"
set key left top
set grid
set arrow from 20, graph 0 to 20, graph 1 nohead dt 2 lc rgb "dark-orange"
set label "Rate1 = 500 kbit/s (half the bridge)" at 20.3, graph 0.95 tc rgb "dark-orange"
set arrow from 30, graph 0 to 30, graph 1 nohead dt 2 lc rgb "red"
set label "Rate2 = 1 Mbit/s (whole bridge)" at 30.3, graph 0.85 tc rgb "red"

plot "cwnd.txt" using 1:2 with steps lw 1.5 title "cwnd (bytes)"
