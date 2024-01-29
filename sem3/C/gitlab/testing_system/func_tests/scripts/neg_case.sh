#!/bin/bash

file1=$1

# Обработка ошибок
if [ -z "$file1" ]; then
    echo 'Недостаточно переменных' >&2
    exit 2
fi

# Создание временного файла
file_tmp=$(mktemp)

# получаем код возврата
./app.exe < "$file1" > "$file_tmp"
exit_test=$?

if [ "$exit_test" == 0 ]; then
    exit 1
else
    exit 0
fi

# Удаляем временные файлы
rm "$file_tmp"