#!/bin/bash

# 1

type_sorts="mysort qsort"
sorts="s us"

filename="go_now.gpi"

for sort in $sorts; do

    echo "#!/usr/bin/bash/gnuplot -persist" > $filename

    echo "reset" >> $filename
    echo "NO_ANIMATION = 1" >> $filename
    echo "set terminal svg size 1920, 1080 background rgb '#00FFFFFF' font 'Helvetica,20'" >> $filename
    echo set output "'./data_time/linepoints $sort.svg'" >> $filename
    echo "set size ratio 0.61803" >> $filename

    echo "set xlabel 'Len array'" >> $filename
    echo "set ylabel 'Time ms'" >> $filename
    echo "set grid" >> $filename

    echo "set title 'linepoints'" >> $filename
    echo -n -e "plot " >> $filename

    for type_sort in $type_sorts; do
        # for sort in $sorts; do
        echo \'./data_time/"$type_sort"_"$sort".txt\' with linespoints, \\ >> $filename
        # done
    done

    gnuplot $filename -persist
    rm -rf $filename

done

