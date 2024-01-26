#!/bin/bash

if [ $# != 1 ]; then
  echo Usage: ./cc_1.sh file-name
  exit 1
fi

# gcc
../../../../.local/bin/CodeChecker check --build "clang -std=c99 -Wall $1" --output ./reports --clean --enable sensitive

