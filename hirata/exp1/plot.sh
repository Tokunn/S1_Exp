#!/usr/bin/env sh

gnuplot -e "set term png; set xlabel \"Frequency [Hz]\"; set ylabel \"Power [dB]\"; set grid;  set output 'imgoutput.png'; plot 'output.csv' with lines"
