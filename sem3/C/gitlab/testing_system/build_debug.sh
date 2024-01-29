#!/usr/bin/bash
gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla\
    -g3 \
    -Wfloat-equal -Wfloat-conversion \
    -o app.exe ./*.c \
    -lm
