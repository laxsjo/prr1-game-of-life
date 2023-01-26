#!/bin/bash

if [ "$1" = "-r" ]; then
    file="rasmus_test.c"
    # echo "rasmus"
# gcc -o gol main.c
elif [ "$1" = "-m" ]; then
    file="melker_test.c"
    # echo "melker"
else
    echo "please choose whoose tests you want to build";
    echo "usage:";
    echo "'./build_test.sh -r' (rasmus)";
    echo "'./build_test.sh -m' (melker)";
    exit 1
fi

if gcc -o test $file types.c rasmus/*.c melker/*.c; then
    echo "created executable 'test'"
fi