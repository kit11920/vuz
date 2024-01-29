#!/bin/bash
gcc -std=c99 -Wall -Werror -Wpedantic -Wextra  -Wvla\
    -g3 -fsanitize=address -fno-omit-frame-pointer \
    -Wfloat-equal -Wfloat-conversion \
    -o app.exe ./*.c \
    -lm
