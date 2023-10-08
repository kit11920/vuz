#!/bin/bash

opts="O0 O2"
indexes="1a 1b 1c"
sorts="s us"


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

for i in $(seq "$count"); do
    for opt in $opts; do
        for index in $indexes; do
            for sort in $sorts; do
                for size in $(seq "$beg_size" "$step" "$end_size"); do
                    echo -n -e "$i/$count $opt $index $sort $size \r"

                    if [ ! -f "./data/data_"$opt"_"$index"_"$sort"_"$size".txt" ]; then
                        touch ./data/data_"$opt"_"$index"_"$sort"_"$size".txt
                    fi

                    ./apps/app_"$opt"_"$index"_"$sort"_"$size".exe >> ./data/data_"$opt"_"$index"_"$sort"_"$size".txt
                done
            done
        done

        # size=$(( size + step ))
        #echo "$size"
    done
done
