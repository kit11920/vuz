#!/bin/bash

args_file=$1
use_valgrind=$2

args=$(<"$args_file")

if [[ -n "$use_valgrind" ]]; then
    eval valgrind -q --leak-check=yes --undef-value-errors=yes --track-origins=yes --error-exitcode=111 ./app.exe "$args"
    rc=$?
else
    eval ./app.exe "$args"
    rc=$?
fi

if [ "$rc" == 0 ]; then
    exit 1
else
    exit 0
fi

