#!/usr/bin/bash
gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla\
    -g3 \
    -Wfloat-equal -Wfloat-conversion \
    -fprofile-arcs -ftest-coverage \
    -o app.exe ./*.c \
    -lm
