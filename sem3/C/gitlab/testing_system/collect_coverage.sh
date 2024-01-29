#!/bin/bash

./build_debug_coverage.sh 
./func_tests/scripts/func_tests.sh 
echo ''

for i in $(find ./ -type f -regex '.*\.gcno')
do
	gcov $i
	echo ''
	echo ''
done

