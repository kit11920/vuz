#!/usr/bin/bash
gcc -std=gnu99 -Wall -Werror -Wpedantic -Wextra -Wvla\
    -g3 \
    -Wfloat-equal -Wfloat-conversion \
    -o app.exe ./task1.c \
    -lm

./app.exe

