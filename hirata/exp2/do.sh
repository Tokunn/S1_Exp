#!/usr/bin/env sh

g++ fft2.cpp
#./a.out ../waves/nazoa.txt
#./a.out ../waves/nazob.txt
./a.out ../waves/nazoc.txt
#./a.out ./8.csv
#gnuplot -e "set term png; set xlabel \"Frequency [Hz]\"; set ylabel \"Power [dB]\"; set grid;  set output 'imgoutput.png'; plot 'output.csv'"
gnuplot -e "set term png; set xlabel \"Time\"; set ylabel \"Frequency [Hz]\"; set zlabel \"Power [dB]\"; set grid;  set output 'imgoutput.png'; splot 'output.csv'"
#gnuplot -e "set term png; set xlabel \"Time\"; set ylabel \"Frequency [Hz]\"; set zlabel \"Power [dB]\"; set grid;  set output 'imgoutput.png'; splot 'output.csv' with lines"
eog imgoutput.png
