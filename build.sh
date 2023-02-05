#!/bin/bash

if gcc -o gol main.c types.c rasmus/*.c melker/*.c; then
    echo "created executable 'gol'"
else
    exit "$?"
fi