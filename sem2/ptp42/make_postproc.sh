#!/bin/bash

# 1

opts="O0 Os O3"
cachs="ch nch"

filename="go_now.gpi"

echo "#!/usr/bin/bash/gnuplot -persist" > $filename

echo "reset" >> $filename
echo "NO_ANIMATION = 1" >> $filename
echo "set terminal svg size 1920, 1080 background rgb '#00FFFFFF' font 'Helvetica,20'" >> $filename
echo set output "'./grafics/linepoints $i.svg'" >> $filename
echo "set size ratio 0.61803" >> $filename

echo "set xlabel 'Columns matrix'" >> $filename
echo "set ylabel 'Time ms'" >> $filename
echo "set grid" >> $filename

echo "set title 'linepoints'" >> $filename
echo -n -e "plot " >> $filename

for opt in $opts; do
    for cach in $cachs; do
        echo \'./preproc_data/preproc_"$opt"_"$cach".txt\' with linespoints, \\ >> $filename
    done
done

gnuplot $filename -persist
rm -rf $filename


