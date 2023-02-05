#!/bin/bash

if ./build.sh; then
    ./gol "${@:2}"
else
    exitCode="$?"
    echo "build failed with code $exitCode"
    exit "$exitCode"
fi