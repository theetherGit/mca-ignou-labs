# plot_bytes.gp -- MCSL-223 Session 7, Q18
# Run after the simulation:  gnuplot plot_bytes.gp
# Reads the four "time bytes" files and draws them on one chart.

set terminal pngcairo size 900,540
set output "bytes.png"
set title "Cumulative bytes received at each sink (2 Mbit/s CSMA bus)"
set xlabel "Time (s)"
set ylabel "Bytes received"
set key left top
set grid

plot "tcp1-bytes.txt" using 1:2 with lines lw 2 title "TCP1 n0 to n2 (8080)", \
     "tcp2-bytes.txt" using 1:2 with lines lw 2 title "TCP2 n1 to n3 (8081)", \
     "udp1-bytes.txt" using 1:2 with lines lw 2 title "UDP1 n2 to n0 (9000)", \
     "udp2-bytes.txt" using 1:2 with lines lw 2 title "UDP2 n3 to n1 (9001)"
