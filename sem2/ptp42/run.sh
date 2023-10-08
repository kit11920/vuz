#!/bin/bash

gcc -std=gnu99 -Wall -Werror -g3 -O2 -D COLUMNS=3 -D ROWS=3 -o ./app.exe main_ch.c

./app.exe
