# gnuplot script: bytes received at n2 against time
# usage: gnuplot rx_bytes.plt   (reads rx-bytes.dat written by wifi_udp_trace)
set terminal pngcairo size 800,500
set output "rx-bytes.png"
set title "UDP bytes received at n2 (Session 5)"
set xlabel "Time (s)"
set ylabel "Cumulative bytes received"
set grid
set key left top
plot "rx-bytes.dat" using 1:2 with linespoints lw 2 pt 7 title "bytes at n2"
