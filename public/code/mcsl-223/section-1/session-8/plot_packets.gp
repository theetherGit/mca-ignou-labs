# plot_packets.gp -- MCSL-223 Session 8, Q19
# Run after the simulation:  gnuplot plot_packets.gp
# packets.txt columns: time, TCP packets in the last second, UDP packets in the last second

set terminal pngcairo size 900,540
set output "packets.png"
set title "Packets received per second at the dumbbell sinks"
set xlabel "Time (s)"
set ylabel "Packets / s"
set key left top
set grid
set arrow from 20, graph 0 to 20, graph 1 nohead dt 2 lc rgb "gray40"
set label "UDP starts (Rate1)" at 20.3, graph 0.92

plot "packets.txt" using 1:2 with linespoints lw 2 title "TCP sink n4 (8080)", \
     "packets.txt" using 1:3 with linespoints lw 2 title "UDP sink n5 (9000)"
