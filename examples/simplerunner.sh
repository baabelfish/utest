#!/bin/bash
FLAGS='-g -std=c++11 -I./include'
CC='g++'

################################################################################
T_UNITS=($(find *_test.cpp))
T_CI=($(find *_CI.cpp))
NUMBER=1

clear
for i in $T_UNITS; do $CC $FLAGS -o runner $i && ./runner; done
for i in $T_CI; do $CC $FLAGS -o runner $i && ./runner; done
rm -f runner
