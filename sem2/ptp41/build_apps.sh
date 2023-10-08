#!/bin/bash

opts="O0 O2"
indexes="1a 1b 1c"
sorts="s us"


beg_size=10
end_size=$(( 10001 + $beg_size ))
step=500

if [ -n "$1" ]; then
    beg_size=$1
fi
if [ -n "$2" ]; then
    end_size=$2
fi
if [ -n "$3" ]; then
    step=$3
fi

size=$beg_size

for size in $(seq "$beg_size" "$step" "$end_size" ); do
    for opt in $opts; do
        for index in $indexes; do
            for sort in $sorts; do
                #echo "gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -g3 -Wfloat-equal -Wfloat-conversion -$opt -D LEN_ARR=$size -o ./apps/app_$opt_$index_$sort_$size.exe main_$index_$sort.c"
                gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -g3 -Wfloat-equal -Wfloat-conversion \
                    -$opt -D LEN_ARR=$size -o ./apps/app_"$opt"_"$index"_"$sort"_"$size".exe main_"$index"_"$sort".c -lm
            done
        done
    done

    echo -n -e "$size \r"
done

