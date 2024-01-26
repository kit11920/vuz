#!/bin/bash

gcc -I inc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla\
    -g3 \
    -Wfloat-equal -Wfloat-conversion \
    -o app.exe src/*.c \
    -lm
