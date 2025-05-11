#! /usr/bin/bash

x=1000
y=1000
p=100
binary=1

make COO_flags
echo "Finding the best warm-up, baseline"
./obj/coo ${x} ${y} ${p} ${binary} 256 1000
./obj/coo ${x} ${y} ${p} ${binary} 1000 1000
./obj/coo ${x} ${y} ${p} ${binary} 5000 1000
./obj/coo ${x} ${y} ${p} ${binary} 10000 1000
./obj/coo ${x} ${y} ${p} ${binary} 100000 1000
echo "Finding the best warm-up, O1"
./obj/coo1 ${x} ${y} ${p} ${binary} 256 1000
./obj/coo1 ${x} ${y} ${p} ${binary} 1000 1000
./obj/coo1 ${x} ${y} ${p} ${binary} 5000 1000
./obj/coo1 ${x} ${y} ${p} ${binary} 10000 1000
./obj/coo1 ${x} ${y} ${p} ${binary} 100000 1000
echo "Finding the best warm-up, O2"
./obj/coo2 ${x} ${y} ${p} ${binary} 256 1000
./obj/coo2 ${x} ${y} ${p} ${binary} 1000 1000
./obj/coo2 ${x} ${y} ${p} ${binary} 5000 1000
./obj/coo2 ${x} ${y} ${p} ${binary} 10000 1000
./obj/coo2 ${x} ${y} ${p} ${binary} 100000 1000
echo "Finding the best warm-up, O3"
./obj/coo3 ${x} ${y} ${p} ${binary} 256 1000
./obj/coo3 ${x} ${y} ${p} ${binary} 1000 1000
./obj/coo3 ${x} ${y} ${p} ${binary} 5000 1000
./obj/coo3 ${x} ${y} ${p} ${binary} 10000 1000
./obj/coo3 ${x} ${y} ${p} ${binary} 100000 1000
echo "Finding the best iteration, O0"
./obj/coo ${x} ${y} ${p} ${binary} 500 100
./obj/coo ${x} ${y} ${p} ${binary} 500 250
./obj/coo ${x} ${y} ${p} ${binary} 500 1000
./obj/coo ${x} ${y} ${p} ${binary} 500 2000
./obj/coo ${x} ${y} ${p} ${binary} 500 4000
./obj/coo ${x} ${y} ${p} ${binary} 500 8000
./obj/coo ${x} ${y} ${p} ${binary} 500 16000
./obj/coo ${x} ${y} ${p} ${binary} 500 64000
echo "Finding the best iteration, O1"
./obj/coo1 ${x} ${y} ${p} ${binary} 500 100
./obj/coo1 ${x} ${y} ${p} ${binary} 500 250
./obj/coo1 ${x} ${y} ${p} ${binary} 500 1000
./obj/coo1 ${x} ${y} ${p} ${binary} 500 2000
./obj/coo1 ${x} ${y} ${p} ${binary} 500 4000
./obj/coo1 ${x} ${y} ${p} ${binary} 500 8000
./obj/coo1 ${x} ${y} ${p} ${binary} 500 16000
./obj/coo1 ${x} ${y} ${p} ${binary} 500 64000
echo "Finding the best iteration, O2"
./obj/coo2 ${x} ${y} ${p} ${binary} 500 100
./obj/coo2 ${x} ${y} ${p} ${binary} 500 250
./obj/coo2 ${x} ${y} ${p} ${binary} 500 1000
./obj/coo2 ${x} ${y} ${p} ${binary} 500 2000
./obj/coo2 ${x} ${y} ${p} ${binary} 500 4000
./obj/coo2 ${x} ${y} ${p} ${binary} 500 8000
./obj/coo2 ${x} ${y} ${p} ${binary} 500 16000
./obj/coo2 ${x} ${y} ${p} ${binary} 500 64000
echo "Finding the best iteration, O3"
./obj/coo3 ${x} ${y} ${p} ${binary} 500 100
./obj/coo3 ${x} ${y} ${p} ${binary} 500 250
./obj/coo3 ${x} ${y} ${p} ${binary} 500 1000
./obj/coo3 ${x} ${y} ${p} ${binary} 500 2000
./obj/coo3 ${x} ${y} ${p} ${binary} 500 4000
./obj/coo3 ${x} ${y} ${p} ${binary} 500 8000
./obj/coo3 ${x} ${y} ${p} ${binary} 500 16000
./obj/coo3 ${x} ${y} ${p} ${binary} 500 64000