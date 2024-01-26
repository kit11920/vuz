#!/bin/bash

pos=$1
neg=$2

# Обработка ошибок
if [[ -z "$pos" || -z "$neg" ]]; then
    echo 'Недостаточно переменных' >&2
    exit 2
fi

mkdir ./func_tests/data


for (( i=1; i <= pos; i++ )); do
    if [ "$i" -lt 10 ]; then
        touch "./func_tests/data/pos_0${i}_in.txt"
        touch "./func_tests/data/pos_0${i}_out.txt"
    else
        touch "./func_tests/data/pos_${i}_in.txt"
        touch "./func_tests/data/pos_${i}_out.txt"
    fi
done

for ((i=1; i <= neg; i++)); do
    if [ "$i" -lt 10 ]; then
        touch "./func_tests/data/neg_0${i}_in.txt"
        touch "./func_tests/data/neg_0${i}_out.txt"
    else
        touch "./func_tests/data/neg_${i}_in.txt"
        touch "./func_tests/data/neg_${i}_out.txt"
    fi
done

