#!/bin/bash

if [ $# != 1 ]; then
  echo Usage: ./ubsan.sh file-name
  exit 1
fi

# gcc
clang -std=c99 -Wall -fsanitize=undefined -fno-omit-frame-pointer -g $1 -o test_ubsan
