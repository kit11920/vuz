#!/bin/bash

file1=$1
file2=$2
use_valgrind=$3

# Обработка ошибок
if [[ -z "$file1" || -z "$file2" ]]; then
    echo 'Недостаточно переменных' >&2
    exit 2
fi

# записываем выходные данные app.exe во временной файл
# Создание временного файла
file_tmp=$(mktemp)


if [[ -n "$use_valgrind" && "$use_valgrind" == '-vg' ]]; then
    eval valgrind -q --leak-check=yes --undef-value-errors=yes --track-origins=yes --error-exitcode=111 ./app.exe < "$file1" > "$file_tmp"
    app_exit=$?
else    
    ./app.exe < "$file1" > "$file_tmp"
    app_exit=$?
fi

# сравниваем ожидаемый результат и тот что получился в $file2
./func_tests/scripts/comparator.sh "$file_tmp" "$file2"
comparator_exit=$?

if [[ $app_exit == 0 && $comparator_exit == 0 ]]; then
    exit 0
else
    exit 1
fi

# Удаляем временные файлы
rm "$file_tmp"
