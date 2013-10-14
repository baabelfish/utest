#!/bin/bash
TESTS='tests'
TESTBIN='tests/.test'
FLAGS='-g -std=c++11 -I./include'
CC='g++'

################################################################################
TESTS=($(find $TESTS -type f -name '*.cpp'|grep -v 'tests/utest/examples'))
NUMBER=1

clear

for i in ${TESTS[@]}; do
    $CC $FLAGS -o $TESTBIN $i $(grep '// UTESTINC: ' $i|cut -f2 -d ':')
    $1 $TESTBIN
    echo ""
done
