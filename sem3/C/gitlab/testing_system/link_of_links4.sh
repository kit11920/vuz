#!/bin/bash


ex=lab_04_01
mkdir ../$ex
cd ../$ex
mkdir func_tests
cd ./func_tests
mkdir scripts
cd ..
ln -s ../testing_system/links.sh links.sh
../testing_system/links.sh

ex=lab_04_02_03
mkdir ../$ex
cd ../$ex
mkdir func_tests
cd ./func_tests
mkdir scripts
cd ..
ln -s ../testing_system/links_str_result.sh links_str_result.sh
../testing_system/links_str_result.sh

ex=lab_04_03_01
mkdir ../$ex
cd ../$ex
mkdir func_tests
cd ./func_tests
mkdir scripts
cd ..
ln -s ../testing_system/links_str_result.sh links_str_result.sh
../testing_system/links_str_result.sh

ex=lab_04_04_03
mkdir ../$ex
cd ../$ex
mkdir func_tests
cd ./func_tests
mkdir scripts
cd ..
ln -s ../testing_system/links_str.sh links_str.sh
../testing_system/links_str.sh


