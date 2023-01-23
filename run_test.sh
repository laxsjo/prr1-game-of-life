#!/bin/bash

./build_test.sh $1
./test ${@: 2}