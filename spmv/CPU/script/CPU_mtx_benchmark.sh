#! /usr/bin/bash

filepath=../../mtx/ash85.mtx
type=0
p=1
warmup=10
iter=100

make import_test
./obj/import_test ${filepath} ${type} ${p} ${warmup} ${iter}
# filepath=../../mtx/test_int3x3.mtx
# type=1
# ./obj/import_test ${filepath} ${type} ${p} 0 1

filepath=../../mtx/Stanford_bin.mtx
type=0
./obj/import_test ${filepath} ${type} ${p} ${warmup} ${iter}
filepath=../../mtx/delaunay_n24_bin.mtx
type=0
./obj/import_test ${filepath} ${type} ${p} ${warmup} ${iter}

type=1
filepath=../../mtx/oh2010_int.mtx
./obj/import_test ${filepath} ${type} ${p} ${warmup} ${iter}
type=1
filepath=../../mtx/mawi_201512020000_int.mtx
./obj/import_test ${filepath} ${type} ${p} ${warmup} ${iter}
