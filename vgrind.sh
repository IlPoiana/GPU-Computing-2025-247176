#! /usr/bin/bash

# cmd=valgrind
target=./obj/toy_block_gemm
# echo "write the program name"
# read target
echo "matrix dimension"
read dim

valgrind --tool=cachegrind $target($dim) > output
valgrind --tool=cachegrind $target0($dim) > output0
valgrind --tool=cachegrind $target1($dim) > output1
valgrind --tool=cachegrind $target2($dim) > output2
valgrind --tool=cachegrind $target3($dim) > output3
 