#!/bin/bash
# Возвращает количество ошибочных файлов

count_errors=0
for file in *.sh; do
    shellcheck "$file"
    count_errors=$(( count_errors + $? ))
done

for file in ./func_tests/scripts/*.sh; do
    shellcheck "$file"
    count_errors=$(( count_errors + $? ))
done

echo "Количество ошибочных файлов $count_errors"
exit $count_errors
