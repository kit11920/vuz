#!/bin/bash


./build_debug_coverage.sh 
./func_tests/scripts/func_tests.sh 
echo ''



while IFS= read -r -d '' i
do
  	gcov "$i"
	echo ''
	echo ''
done < <(find ./ -type f -regex '.*\.gcno' -print0)

rm -f ./*.gcda
rm -f ./*.gcno
rm -f ./*.c.gcov
