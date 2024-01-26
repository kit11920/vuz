#!/bin/bash

strr=""
len_str=0

file1=$1
file2=$2

# Обработка ошибок
if [[ -z "$file1" || -z "$file2" ]]; then
    echo 'Недостаточно переменных' >&2
    exit 2
elif [[ ! -f "$file1" || ! -f "$file2" ]]; then
    echo 'Должно быть задано 2 файла' >&2
    exit 2
elif [[ ! ( -z "$3" || "$3" == '-v' ) ]]; then
    echo 'Третий параметр задан не верно' >&2
    exit 2
fi

# Создание временного файла
tmpfile1=$(mktemp)
# echo $tmpfile1

saving=0    # флаг сохраняем ли мы сейчас текст
# Чтение файла по строкам
# IFS= - чтобы не урезалить двойные пробелы и табуляции
while IFS= read -r line || [[ -n "$line" ]]; do # [[ -n "$line" ]] предотвращает игнорирование последней строки если она не оканчивается \n
    if [[ $line == *"$strr"* && $saving == 0 ]]; then
        i=0
        while ! [[ ${line:i:$len_str} == "$strr" ]]; do
            i=$((i + 1))
        done

        echo "${line:$((i+len_str))}" > "$tmpfile1"
        saving=1
    elif [ $saving == 1 ]; then 
        echo "$line" >> "$tmpfile1"
    fi
done < "$file1"

if [ -n "$3" ]; then
    IFS=""
    echo "$(cat "$tmpfile1" )" $'\n'
    IFS="$IFS_OLD"
fi


# Создание временного файла
tmpfile2=$(mktemp)
# echo $tmpfile2
# trap "rm -f $tmpfile2" EXIT SIGKILL # ВЫполняет действие "" после получения сигнала (Безусловное завершение процесса))    (-f игнорирует несуществующие файлы)

saving=0    # флаг сохраняем ли мы сейчас текст
# Чтение файла по строкам
# IFS= - чтобы не урезалить двойные пробелы и табуляции
while IFS= read -r line || [[ -n "$line" ]]; do # [[ -n "$line" ]] предотвращает игнорирование последней строки если она не оканчивается \n
    if [[ $line == *"$strr"* && $saving == 0 ]]; then
        i=0
        while ! [[ ${line:i:$len_str} == "$strr" ]]; do
            i=$((i + 1))
        done

        echo "${line:$((i+ len_str))}" > "$tmpfile2"
        saving=1
    elif [ $saving == 1 ]; then 
        echo "$line" >> "$tmpfile2"
    fi
done < "$file2"

if [ -n "$3" ]; then
    IFS=""
    echo "$(cat "$tmpfile2" )" $'\n'
    IFS="$IFS_OLD"
fi


if cmp "$tmpfile1" "$tmpfile2" &> /dev/null; then
    if [ -n "$3" ]; then
        echo "Текст в файлах после подстроки $strr один и тот же"
    fi
    exit 0
else
    if [ -n "$3" ]; then
        echo "Текст в файлах после подстроки $strr разный"
    fi
    exit 1
fi

# Удаляем временные файлы
rm "$tmpfile1"
rm "$tmpfile2"
