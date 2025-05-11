#!/bin/bash

#SBATCH --job-name=heap_comaprison
#SBATCH --output=./out/my_output_%j.out
#SBATCH --error=./out/my_error_%j.err
#SBATCH --partition=edu-short
#SBATCH --nodes=1
#SBATCH --gres=gpu:0
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1

mkdir -p ./out/

x=100
y=100
p=10
binary=1

echo std case
valgrind --tool=cachegrind ./obj/comparison $x $y $p $binary > ./out/output0
echo O1 case
valgrind --tool=cachegrind ./obj/comparison1 $x $y $p $binary > ./out/output1
echo O2 case
valgrind --tool=cachegrind ./obj/comparison2 $x $y $p $binary > ./out/output2
echo O3 case
valgrind --tool=cachegrind ./obj/comparison $x $y $p $binary > ./out/output3
