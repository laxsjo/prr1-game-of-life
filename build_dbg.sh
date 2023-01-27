#!/bin/bash

if gcc -o gol main.c types.c rasmus/*.c melker/*.c -ggdb; then
    echo "created executable 'gol', with debug symbols"
fi