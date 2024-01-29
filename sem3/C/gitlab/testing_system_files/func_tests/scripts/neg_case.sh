#!/bin/bash

in_file=$1
args_file=$2

# # Обработка ошибок
# if [[ -z "$file1" || -z "$file2" || -z "$args_file" ]]; then
#    echo 'Недостаточно переменных' >&2
#    exit 2
# fi

# Создание временного файла
file_tmp=$(mktemp)

file_exe=./app.exe
args=$(<"$args_file")

eval ./app.exe $args >"$file_tmp"

rc=$?

if [ "$rc" == 0 ]; then
    exit 1
else
    exit 0
fi

# Удаляем временные файлы
rm "$file_tmp"
