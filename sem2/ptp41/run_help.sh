gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -g3 -Wfloat-equal -Wfloat-conversion \
                    -O0 -D LEN_ARR=10 -o ./app.exe main_1a_rse.c -lm
                    
./app.exe
