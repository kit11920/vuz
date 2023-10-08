#!/bin/bash

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

for size in $(seq "$beg_size" "$step" "$end_size" ); do
    echo -n -e "$size \r"
    gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -g3 -Wfloat-equal -Wfloat-conversion \
                    -O0 -D LEN_ARR=$size -o ./apps/app_1a_"$size"_rse.exe main_1a_rse.c -lm
    ./apps/app_1a_"$size"_rse.exe
done

