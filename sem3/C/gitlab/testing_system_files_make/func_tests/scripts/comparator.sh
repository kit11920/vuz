#!/bin/bash

# сравнивает числа в файле (целые, дробные и в экспоненциальной записи)

file1=$1
file2=$2

# Обработка ошибок
if [[ -z "$file1" || -z "$file2" ]]; then
    echo 'Недостаточно переменных' >&2
    exit 2
elif [[ ! ( -z "$3" || "$3" == '-v' ) ]]; then
    echo 'Третий параметр задан не верно' >&2
    exit 2
fi

# Создание временного файла
tmpfile1=$(mktemp)
# echo $tmpfile1

frst=1
while IFS= read -r line || [[ -n "$line" ]]; do
    for item in $line; do
        item="$( tr -d "[:space:]" <<< "$item" )"
        # echo "$item"
        if [[ $item =~ ^[+-]?[0-9]*[.][0-9]+[eEеЕ][+-]?[0-9]+$ || $item =~ ^[+-]?[0-9]+([.][0-9]*)?[eEеЕ][+-]?[0-9]+$ || 
            $item =~ ^[+-]?[0-9]*[.][0-9]+$ || $item =~ ^[+-]?[0-9]+[.][0-9]*$ || $item =~ ^[+-]?[0-9]+$ ]]; then
            # двойные скобочки чтобы обработать строку с пробелом и не надо было ее заключать в кавычки
            if [ $frst == 1 ]; then
                echo "$item" > "$tmpfile1"
                frst=0
            else
                echo "$item" >> "$tmpfile1"
            fi
            # echo $ints1
        fi
    done
done < "$file1"

# Создание временного файла
tmpfile2=$(mktemp)
# echo $tmpfile2

frst=1
while IFS= read -r line || [[ -n "$line" ]]; do
    for item in $line; do
        item="$( tr -d "[:space:]" <<< "$item" )"
        # echo "$item"
        if [[ $item =~ ^[+-]?[0-9]*[.][0-9]+[eEеЕ][+-]?[0-9]+$ || $item =~ ^[+-]?[0-9]+([.][0-9]*)?[eEеЕ][+-]?[0-9]+$ || 
            $item =~ ^[+-]?[0-9]*[.][0-9]+$ || $item =~ ^[+-]?[0-9]+[.][0-9]*$ || $item =~ ^[+-]?[0-9]+$ ]]; then
            # двойные скобочки чтобы обработать строку с пробелом и не надо было ее заключать в кавычки
            # echo "       $item"
            if [ $frst == 1 ]; then
                echo "$item" > "$tmpfile2"
                frst=0
            else
                echo "$item" >> "$tmpfile2"
            fi
            # echo $ints1
        fi
    done
done < "$file2"


if [ -n "$3" ]; then
    IFS=""
    echo "$file1" $'\t' "$( < "$tmpfile1" tr '\n' ' ' ) " 
    IFS="$IFS_OLD"
fi

if [ -n "$3" ]; then
    IFS=""
    echo "$file2" $'\t' "$( < "$tmpfile2" tr '\n' ' ' ) " 
    IFS="$IFS_OLD"
fi

# $( cmp $tmpfile1 $tmpfile2 &>/dev/null ) 
if cmp "$tmpfile1" "$tmpfile2" &> /dev/null; then
    if [ -n "$3" ]; then
        echo "Последовательности чисел в файлах $file1 $file2 одинаковые"
    fi
    exit 0
else
    if [ -n "$3" ]; then
        echo "Последовательности чисел в файлах $file1 $file2 различны"
    fi
    exit 1
fi


# Удаляем временные файлы
rm "$tmpfile1"
rm "$tmpfile2"
