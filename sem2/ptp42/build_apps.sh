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


for row in $(seq "$beg_size" "$step" "$end_size" ); do
    for opt in $opts; do
        for cach in $cachs; do
            gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -g3 -Wfloat-equal -Wfloat-conversion \
                -$opt -D COLUMNS=$col -D ROWS=$row -o ./apps/app_"$opt"_"$cach"_"$col"x"$row".exe main_"$cach".c
        done
    done
    echo -n -e "$col x $row \r"
done



