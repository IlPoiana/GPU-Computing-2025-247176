#! /usr/bin/bash
mkdir -p ./out/

x=10000000
y=2
p=100000
binary=1

echo std case
valgrind --tool=cachegrind ./obj/comparison $x $y $p $binary > ./out/output0
echo O1 case
valgrind --tool=cachegrind ./obj/comparison1 $x $y $p $binary > ./out/output1
echo O2 case
valgrind --tool=cachegrind ./obj/comparison2 $x $y $p $binary > ./out/output2
echo O3 case
valgrind --tool=cachegrind ./obj/comparison $x $y $p $binary > ./out/output3
