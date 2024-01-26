#!/bin/bash
gcc -I inc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla\
    -g3 -fsanitize=undefined -fno-omit-frame-pointer \
    -Wfloat-equal -Wfloat-conversion \
    -o app.exe src/*.c \
    -lm
