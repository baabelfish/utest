#!/bin/bash
TESTS='tests'
TESTBIN='.tests'
FLAGS='-g -std=c++11 -I./include'
CC='g++'

################################################################################
[[ ! -d "$TESTBIN" ]] && mkdir "$TESTBIN"
TESTS=($(find $TESTS -type f -name '*.cpp'|grep -v 'tests/utest/examples'))
NUMBER=1

for i in ${TESTS[@]}; do
    $CC $FLAGS -o $TESTBIN/test$NUMBER $i
    NUMBER=$((NUMBER+1))
done

for (( i = 1; i < $NUMBER; i++ )); do
    $TESTBIN/test$i
    echo ""
    rm -f $TESTBIN/test$i
done
