#!/bin/bash

opts="O0 Os O3"
cachs="ch nch"


col=100
beg_size=10
end_size=$(( 5001 + $beg_size ))
step=100
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

for i in $(seq "$count"); do
    for row in $(seq "$beg_size" "$step" "$end_size" ); do
        for opt in $opts; do
            for cach in $cachs; do
                echo -n -e "$i/$count $opt $cach  $col x $row \r"

                if [ ! -f "./data/data_"$opt"_"$cach"_"$col"x"$row".txt" ]; then
                    touch ./data/data_"$opt"_"$cach"_"$col"x"$row".txt
                fi

                ./apps/app_"$opt"_"$cach"_"$col"x"$row".exe >> ./data/data_"$opt"_"$cach"_"$col"x"$row".txt
            done
        done
    done
done
