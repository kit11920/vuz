#!/bin/bash
gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla\
    -g3 -fsanitize=undefined -fno-omit-frame-pointer \
    -Wfloat-equal -Wfloat-conversion \
    -o app.exe ./*.c \
    -lm
