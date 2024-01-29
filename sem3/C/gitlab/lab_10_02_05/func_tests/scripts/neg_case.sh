#!/bin/bash

file1=$1
use_valgrind=$2

# Обработка ошибок
if [ -z "$file1" ]; then
    echo 'Недостаточно переменных' >&2
    exit 2
fi

# Создание временного файла
file_tmp=$(mktemp)

if [[ -n "$use_valgrind" ]]; then
    valgrind -q --leak-check=yes --undef-value-errors=yes --track-origins=yes --error-exitcode=111 ./app.exe < "$file1" > "$file_tmp"
    exit_test=$?
else
    ./app.exe < "$file1" > "$file_tmp"
    exit_test=$?
fi

if [ "$exit_test" == 0 ]; then
    exit 1
else
    exit 0
fi

# Удаляем временные файлы
rm "$file_tmp"