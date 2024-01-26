#!/bin/bash
clang -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla\
    -g3 -fsanitize=memory -fPIE -pie -fno-omit-frame-pointer \
    -Wfloat-equal -Wfloat-conversion \
    -o app.exe ./*.c \
    -lm
