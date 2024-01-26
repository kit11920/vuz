#!/bin/bash

if [ $# != 1 ]; then
  echo Usage: ./msan.sh file-name
  exit 1
fi

# gcc
clang -std=c99 -Wall -fsanitize=memory -fPIE -pie -fno-omit-frame-pointer -g $1 -o test_msan
