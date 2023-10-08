#!/bin/bash


beg_size=10
end_size=$(( 10001 + $beg_size ))
step=500
count=5

if [ -n "$1" ]; then
    beg_size=$1
fi
if [ -n "$2" ]; then
    end_size=$2
fi
if [ -n "$3" ]; then
    step=$3
fi
if [ -n "$4" ]; then
    count=$4
fi

size=$beg_size

opts="O0 O2"
indexes="1a 1b 1c"
sorts="s us"

for index in $indexes; do
    for opt in $opts; do
        for sort in $sorts; do

            echo "# Size midt mint maxt" > "./preproc_data/preproc_"$opt"_"$index"_"$sort".txt"
            for size in $(seq "$beg_size" "$step" "$end_size"); do
                echo -n -e "prep $opt $index $sort $size \r"

                filename="stats_.gpi"

                echo "#!/usr/bin/bash/gnuplot -persist" > $filename

                echo stats \'./data/data_"$opt"_"$index"_"$sort"_"$size".txt\' nooutput >> $filename
                echo set print \'stats.txt\' >> $filename
                echo     print STATS_mean >> $filename
                echo     print STATS_min >> $filename
                echo     print STATS_lo_quartile >> $filename
                echo     print STATS_median >> $filename
                echo     print STATS_up_quartile >> $filename
                echo     print STATS_max >> $filename
                echo unset print >> $filename

                echo -n " $size" >> "./preproc_data/preproc_"$opt"_"$index"_"$sort".txt"
                gnuplot $filename -persist
                i=0
                while read stats; do
                    if [[ $i == 0 || $i == 1 || $i == 5 ]]; then
                        echo -n " $stats" >> "./preproc_data/preproc_"$opt"_"$index"_"$sort".txt"
                    fi
                    i=$(( $i + 1 ))
                done < "stats.txt"
                rm "stats.txt"
                echo "" >> "./preproc_data/preproc_"$opt"_"$index"_"$sort".txt"

            done 
        done
    done
done

# график с усами
opt="O2"
index="1a"
sort="us"

echo "# Size mint 1stQuartile Median 3rdQuartile maxt" >> "./preproc_data/preproc_"$opt"_"$index"_"$sort"_moustache.txt"
for size in $(seq "$beg_size" "$step" "$end_size"); do
    echo -n -e "prep moustache $opt $index $sort $size \r"

    filename="stats_.gpi"

    echo "#!/usr/bin/bash/gnuplot -persist" > $filename

    echo stats \'./data/data_"$opt"_"$index"_"$sort"_"$size".txt\' nooutput >> $filename
    echo set print \'stats.txt\' >> $filename
    echo     print STATS_mean >> $filename
    echo     print STATS_min >> $filename
    echo     print STATS_lo_quartile >> $filename
    echo     print STATS_median >> $filename
    echo     print STATS_up_quartile >> $filename
    echo     print STATS_max >> $filename
    echo unset print >> $filename

    echo -n " $size" >> "./preproc_data/preproc_"$opt"_"$index"_"$sort"_moustache.txt"
    gnuplot $filename -persist

    i=0
    while read stats; do
        if [[ $i == 1 ]]; then
            echo -n " $stats" >> "./preproc_data/preproc_"$opt"_"$index"_"$sort"_moustache.txt"
        else
            i=1
        fi
    done < "stats.txt"
    rm "stats.txt"
    echo "" >> "./preproc_data/preproc_"$opt"_"$index"_"$sort"_moustache.txt"
done
rm $filename
