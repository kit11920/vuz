#!/bin/bash

in_file=$1
out_file=$2
args_file=$3
use_valgrind=$4


# # Обработка ошибок
# if [[ -z "$in_file" || -z "$out_file" || -z "$args_file" ]]; then
#    echo 'Недостаточно переменных' >&2
#    exit 2
# fi

# записываем выходные данные app.exe во временной файл
# Создание временного файла
file_tmp=$(mktemp)

file_exe=./app.exe
args=$(<"$args_file")

# eval ./app.exe $args < "$in_file" >"$file_tmp"

# rc=$?

if [[ -n "$use_valgrind" && "$use_valgrind" == '-vg' ]]; then
    eval valgrind -q --leak-check=yes --undef-value-errors=yes --track-origins=yes --error-exitcode=111 ./app.exe "$args" < "$in_file" >"$file_tmp"
    rc=$?
else
    eval ./app.exe $args < "$in_file" >"$file_tmp"
    rc=$?
fi



# # считываем параметры записанные через пробел файле параметров командной строки
# read -r line < "$args_file"
# read -ra args <<< "$line" # записываем все параметры в массив args

# # записываем выходные данные app.exe во временной файл
# # Создание временного файла
# file_tmp=$(mktemp)
# ./app.exe "${args[@]}" < "$in_file" > "$file_tmp"
# rc=$?

#echo "${args[@]}"


# сравниваем ожидаемый результат и тот что получился в $filout_filee2
./func_tests/scripts/comparator.sh "$file_tmp" "$out_file"
comparator_exit=$?

# echo $rc
# echo $comparator_exit
if [[ $rc == 0 && $comparator_exit == 0 ]]; then
    exit 0
else
    exit 1
fi

# Удаляем временные файлы
rm "$file_tmp"


