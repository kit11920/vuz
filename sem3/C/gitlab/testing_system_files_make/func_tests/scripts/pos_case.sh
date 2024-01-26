#!/bin/bash

expected_out_file=$1
args_file=$2
use_valgrind=$3


args=$(<"$args_file")

if [[ -n "$use_valgrind" && "$use_valgrind" == '-vg' ]]; then
    eval valgrind -q --leak-check=yes --undef-value-errors=yes --track-origins=yes --error-exitcode=111 ./app.exe "$args" 
    rc=$?
else
    eval ./app.exe "$args"
    rc=$?
fi



# считываем параметры записанные через пробел файле параметров командной строки
read -r line < "$args_file"
read -ra args <<< "$line" # записываем все параметры в массив args

if [[ ${args[1]} == 'a' || ${args[1]} == 'm']]
    real_out_file=${args[3]}
else
    real_out_file=${args[2]}

# сравниваем ожидаемый результат и тот что получился в $filout_filee2
./func_tests/scripts/comparator.sh "$real_out_file" "$expected_out_file"
comparator_exit=$?


if [[ $rc == 0 && $comparator_exit == 0 ]]; then
    exit 0
else
    exit 1
fi



