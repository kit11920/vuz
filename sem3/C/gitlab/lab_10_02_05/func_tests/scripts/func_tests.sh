#!/bin/bash
# Возвращает количество проваленых стестов

use_valgrind=$1

# echo $( find ../data -name "pos_0${i}_in.txt" | wc -l )
i=1
fail_pos_tests=0
while [[ $( find ./func_tests/data -name "pos_0${i}_in.txt" | wc -l ) == 1 && 
        $( find ./func_tests/data -name "pos_0${i}_out.txt" | wc -l ) == 1 ]]; do
    
    echo "pos_0${i}_in.txt"
    ./func_tests/scripts/pos_case.sh "./func_tests/data/pos_0${i}_in.txt" "./func_tests/data/pos_0${i}_out.txt"  "$use_valgrind"
    exit_test=$?
    if [ "$exit_test" == 0 ]; then
        echo "OK"
    else
        echo "ERROR"
        fail_pos_tests=$(( fail_pos_tests + 1 ))
    fi

    i=$(( i + 1 ))
done
while [[ $( find ./func_tests/data -name "pos_${i}_in.txt" | wc -l ) == 1 && 
        $( find ./func_tests/data -name "pos_${i}_out.txt" | wc -l ) == 1 ]]; do
    
    echo "pos_${i}_in.txt"
    ./func_tests/scripts/pos_case.sh "./func_tests/data/pos_${i}_in.txt" "./func_tests/data/pos_${i}_out.txt" "$use_valgrind"
    exit_test=$?
    if [ "$exit_test" == 0 ]; then
        echo "OK"
    else
        echo "ERROR"
        fail_pos_tests=$(( fail_pos_tests + 1 ))
    fi

    i=$(( i + 1 ))
done
count_pos_tests=$(( i - 1))

fail_neg_tests=0
i=1
while [[ $( find ./func_tests/data -name "neg_0${i}_in.txt" | wc -l ) == 1 ]]; do

    echo "neg_0${i}_in.txt"
    ./func_tests/scripts/neg_case.sh "./func_tests/data/neg_0${i}_in.txt" "$use_valgrind"
    exit_test=$?
    if [ "$exit_test" == 0 ]; then
        echo "OK"
    else
        echo "ERROR"
        fail_neg_tests=$((fail_neg_tests + 1))
    fi

    i=$(( i + 1 ))
done
count_neg_tests=$(( i - 1))

echo "Positive tests: correct $(( count_pos_tests - fail_pos_tests)) of $count_pos_tests"
echo "Negative tests: correct $(( count_neg_tests - fail_neg_tests)) of $count_neg_tests"


fail_tests=$(( fail_pos_tests +  fail_neg_tests ))
exit $fail_tests
