#!/bin/bash


ex=lab_07_1_3
mkdir ../$ex
cd ../$ex
mkdir func_tests
cd ./func_tests
mkdir scripts
cd ..
ln -s ../testing_system_files/links_cmp_str.sh links.sh
../testing_system_files/links.sh

