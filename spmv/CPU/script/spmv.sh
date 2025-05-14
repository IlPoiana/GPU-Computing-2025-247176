#! /usr/bin/bash

x=1000
y=1000
p=1
binary=1

make COO_flags
echo "Finding the best iteration, O1"
./obj/coo1 ${x} ${y} ${p} ${binary} 500 5000 1
./obj/coo1 ${x} ${y} ${p} ${binary} 500 5000 100
echo "Finding the best iteration, O2"
./obj/coo2 ${x} ${y} ${p} ${binary} 500 5000 1
./obj/coo2 ${x} ${y} ${p} ${binary} 500 5000 100
echo "Finding the best iteration, O3"
./obj/coo3 ${x} ${y} ${p} ${binary} 500 5000 1
./obj/coo3 ${x} ${y} ${p} ${binary} 500 5000 100

x=10000
y=50000 
p=1000
binary=1

echo "Finding the best iteration, O1"
./obj/coo1 ${x} ${y} ${p} ${binary} 500 5000 2
./obj/coo1 ${x} ${y} ${p} ${binary} 500 5000 100
echo "Finding the best iteration, O2"
./obj/coo2 ${x} ${y} ${p} ${binary} 500 5000 2
./obj/coo2 ${x} ${y} ${p} ${binary} 500 5000 100
echo "Finding the best iteration, O3"
./obj/coo3 ${x} ${y} ${p} ${binary} 500 5000 2
./obj/coo3 ${x} ${y} ${p} ${binary} 500 5000 100

# make COO_1flags
# echo "Finding the best iteration, O1"
# ./obj/coo1 ${x} ${y} ${p} ${binary} 500 5000 1
# ./obj/coo1 ${x} ${y} ${p} ${binary} 500 5000 100
# echo "Finding the best iteration, O2"
# ./obj/coo2 ${x} ${y} ${p} ${binary} 500 5000 1
# ./obj/coo2 ${x} ${y} ${p} ${binary} 500 5000 100
# echo "Finding the best iteration, O3" 
# ./obj/coo3 ${x} ${y} ${p} ${binary} 500 5000 1
# ./obj/coo3 ${x} ${y} ${p} ${binary} 500 5000 100