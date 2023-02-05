#!/bin/bash

if ./build_test.sh $1; then
    ./test ${@: 2}
else
    exitCode="$?"
    echo "build failed with code $exitCode"
    exit "$exitCode"
fi