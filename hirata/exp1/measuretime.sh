#!/usr/bin/env sh

echo -e "\n\n-------------------\ndft"
time dft/a.out ../waves/sinewave.txt

echo -e "\n\n-------------------\ndft2048"
time 2048/dft2048 ../waves/sinewave.txt

echo -e "\n\n-------------------\nfft"
time fft/a.out ../waves/sinewave.txt

echo -e "\n\n-------------------\nfft2048"
time 2048/fft2048 ../waves/sinewave.txt

rm output.csv
