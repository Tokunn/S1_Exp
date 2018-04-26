#!/usr/bin/env sh

gnuplot -e "set term png; set output 'imgoutput.png'; plot 'output.csv' with lines"
