#!/bin/bash

file1=$1
file2=$2

# Обработка ошибок
if [[ -z "$file1" || -z "$file2" ]]; then
    echo 'Недостаточно переменных' >&2
    exit 2
fi

# записываем выходные данные app.exe во временной файл
# Создание временного файла
file_tmp=$(mktemp)
./app.exe < "$file1" > "$file_tmp"
app_exit=$?

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
