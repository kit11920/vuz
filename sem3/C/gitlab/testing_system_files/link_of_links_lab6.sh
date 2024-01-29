#!/bin/bash


ex=lab_06_01_01
mkdir ../$ex
cd ../$ex
mkdir func_tests
cd ./func_tests
mkdir scripts
cd ..
ln -s ../testing_system_files/links_cmp_str.sh links_cmp_str.sh
../testing_system_files/links_cmp_str.sh

