#!/bin/bash

ex=lab_06_01_01
mkdir ../$ex
cd ../$ex
mkdir func_tests
cd ./func_tests
mkdir scripts
cd ..
ln -s ../testing_system/links_str.sh links_str.sh
../testing_system/links_str.sh


