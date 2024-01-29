#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wextra  -Wvla\
    -Wfloat-equal -Wfloat-conversion \
    -o app.exe ./*.c \
    -lm
