#!/bin/bash

ln -s ../testing_system_files_make/check_valgrind_unit.sh check_valgrind_unit.sh
ln -s ../testing_system_files_make/collect_coverage.sh collect_coverage.sh
ln -s ../testing_system_files_make/clean.sh clean.sh
ln -s ../testing_system_files_make/check_scripts.sh check_scripts.sh
mkdir ./func_tests/scripts
cd ./func_tests/scripts || exit
ln -s ../../../testing_system_files_make/func_tests/scripts/comparator.sh comparator.sh    
ln -s ../../../testing_system_files_make/func_tests/scripts/func_tests.sh func_tests.sh  
ln -s ../../../testing_system_files_make/func_tests/scripts/neg_case.sh neg_case.sh 
ln -s ../../../testing_system_files_make/func_tests/scripts/pos_case.sh pos_case.sh 
ln -s ../../../testing_system_files_make/func_tests/scripts/make_empty_test_files.sh make_empty_test_files.sh    

