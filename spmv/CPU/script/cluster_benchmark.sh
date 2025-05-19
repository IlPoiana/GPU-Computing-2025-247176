#!/bin/bash

#SBATCH --job-name=CPU
#SBATCH --output=CPU_benchmark%j.out
#SBATCH --error=my_error_%j.err
#SBATCH --partition=edu-short
#SBATCH --nodes=1
#SBATCH --gres=gpu:3
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=16

filepath=../../mtx/ash85.mtx
type=0
p=1
warmup=10
iter=100

make COO
srun ./obj/coo ${filepath} ${type} ${p} ${warmup} ${iter} Ash85
# filepath=../../mtx/test_int3x3.mtx
# type=1
# ./obj/coo ${filepath} ${type} ${p} 0 1

filepath=../../mtx/Stanford_bin.mtx
type=0
srun ./obj/coo ${filepath} ${type} ${p} ${warmup} ${iter} Stanford
filepath=../../mtx/delaunay_n24_bin.mtx
type=0
srun ./obj/coo ${filepath} ${type} ${p} ${warmup} ${iter} Delaunay

type=1
filepath=../../mtx/oh2010_int.mtx
srun ./obj/coo ${filepath} ${type} ${p} ${warmup} ${iter} Oh2010
type=1
filepath=../../mtx/mawi_201512020000_int.mtx
srun ./obj/coo ${filepath} ${type} ${p} ${warmup} ${iter} Mawi
