#!/bin/bash

in_file=$1
args_file=$2
use_valgrind=$3

# # Обработка ошибок
# if [[ -z "$file1" || -z "$file2" || -z "$args_file" ]]; then
#    echo 'Недостаточно переменных' >&2
#    exit 2
# fi

# Создание временного файла
file_tmp=$(mktemp)

args=$(<"$args_file")

if [[ -n "$use_valgrind" && "$use_valgrind" == '-vg' ]]; then
    eval valgrind -q --leak-check=yes --undef-value-errors=yes --track-origins=yes --error-exitcode=111 ./app.exe "$args" >"$file_tmp"
    rc=$?
else
    eval ./app.exe "$args" >"$file_tmp"
    rc=$?
fi


if [ "$rc" == 0 ]; then
    exit 1
else
    exit 0
fi

# Удаляем временные файлы
rm "$file_tmp"
