#!/bin/bash

echo 'Valgrind unit_tests.exe'
if [ ! -f ./unit_tests.exe ]; then
	echo 'ERROR: Создайте сначала ./unit_tests.exe' >&2
	exit 1
else
	valgrind -q --leak-check=yes --undef-value-errors=yes --track-origins=yes ./unit_tests.exe ./func_tests/data/pos_01_in.txt out/tmp.txt
	rc=$?
	if [ "$rc" == 0 ]; then
	    echo "OK"
	else
	    echo "ERROR"
	fi
fi

