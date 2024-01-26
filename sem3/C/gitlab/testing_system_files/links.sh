#!/bin/bash

ln -s ../testing_system_files/build_release.sh build_release.sh 
ln -s ../testing_system_files/build_debug.sh build_debug.sh
ln -s ../testing_system_files/build_debug_asan.sh build_debug_asan.sh
ln -s ../testing_system_files/build_debug_msan.sh build_debug_msan.sh
ln -s ../testing_system_files/build_debug_ubsan.sh build_debug_ubsan.sh
ln -s ../testing_system_files/check_sanitizers.sh check_sanitizers.sh
ln -s ../testing_system_files/build_debug_coverage.sh build_debug_coverage.sh
ln -s ../testing_system_files/collect_coverage.sh collect_coverage.sh
ln -s ../testing_system_files/clean.sh clean.sh
ln -s ../testing_system_files/check_scripts.sh check_scripts.sh
mkdir ./func_tests/scripts
cd ./func_tests/scripts || exit
ln -s ../../../testing_system_files/func_tests/scripts/comparator.sh comparator.sh    
ln -s ../../../testing_system_files/func_tests/scripts/func_tests.sh func_tests.sh  
ln -s ../../../testing_system_files/func_tests/scripts/neg_case.sh neg_case.sh 
ln -s ../../../testing_system_files/func_tests/scripts/pos_case.sh pos_case.sh 
ln -s ../../../testing_system_files/func_tests/scripts/make_empty_test_files.sh make_empty_test_files.sh    

