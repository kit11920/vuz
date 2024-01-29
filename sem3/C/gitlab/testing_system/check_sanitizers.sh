#!/bin/bash
# Проверяет по всем санитайзерам

echo 'Without sanitizers'
./build_debug.sh
./func_tests/scripts/func_tests.sh
echo ''

echo 'Address sanitizer'
./build_debug_asan.sh
./func_tests/scripts/func_tests.sh
echo ''

echo 'Memory sanitizer'
./build_debug_msan.sh
./func_tests/scripts/func_tests.sh
echo ''

echo 'Undefined behavior sanitizer'
./build_debug_ubsan.sh
./func_tests/scripts/func_tests.sh
echo ''
