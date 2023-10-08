#!/bin/bash

# 1

opts="O0 O2"
indexes="1a 1b 1c"
sorts="s us"

for i in $(seq 1 4); do
    filename="go_now$i.gpi"

    echo "#!/usr/bin/bash/gnuplot -persist" > $filename

    echo "reset" >> $filename
    echo "NO_ANIMATION = 1" >> $filename
    echo "set terminal svg size 1920, 1080 background rgb '#00FFFFFF' font 'Helvetica,20'" >> $filename
    echo set output "'./grafics/linepoints $i.svg'" >> $filename
    echo "set size ratio 0.61803" >> $filename

    echo "set xlabel 'Size array'" >> $filename
    echo "set ylabel 'Time ms'" >> $filename
    echo "set grid" >> $filename

    echo "set title 'linepoints $i'" >> $filename
    echo -n -e "plot " >> $filename


    if (( $i == 4 )); then
        echo \'./preproc_data/preproc_O2_1a_us_moustache.txt\' using 1:3:2:6:5 with candlesticks whiskerbars, \\ >> $filename
        echo \'./preproc_data/preproc_O2_1a_us_moustache.txt\' using 1:4:4:4:4 with candlesticks, \\ >> $filename
        echo \'./preproc_data/preproc_O2_1a_us_moustache.txt\' using 1:4 with linespoints, \\ >> $filename
        gnuplot $filename -persist
    else
        for index in $indexes; do
            for opt in $opts; do
                if (( $i == 1 )); then
                    echo \'./preproc_data/preproc_"$opt"_"$index"_s.txt\'  with linespoints, \\ >> $filename
                fi
                if (( $i == 2 )); then
                    echo \'./preproc_data/preproc_"$opt"_"$index"_us.txt\'  with linespoints, \\ >> $filename
                fi
            done
            if (( $i == 3 )); then
                for sort in $sorts; do
                    echo \'./preproc_data/preproc_O2_"$index"_"$sort".txt\' with lines, \\ >> $filename
                    echo \'./preproc_data/preproc_O2_"$index"_"$sort".txt\' with errorbars, \\ >> $filename
                    
                done
            fi
            gnuplot $filename -persist
        done
    fi
    rm -rf $filename
done

