#!/bin/bash

#SBATCH --job-name=firstCuda
#SBATCH --output=COO_CPU%j.out
#SBATCH --error=my_error_%j.err
#SBATCH --partition=edu-short
#SBATCH --nodes=1
#SBATCH --gres=gpu:0
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=32

x=100000
y=10000
p=100
binary=1

# remove the other flags

echo "${x} ${y} ${p} ${binary} - 1% - O3"
srun ./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 1
srun ./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 10
srun ./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 100

x=100000
y=10000
p=1000
binary=1

echo "${x} ${y} ${p} ${binary} - 0.1% - O3"
srun ./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 1
srun ./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 10
srun ./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 100

x=100000
y=100000
p=100
binary=1

echo "${x} ${y} ${p} ${binary} - 1% - O3"

srun ./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 1
srun ./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 10
srun ./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 100

x=100000
y=100000
p=1000
binary=1

echo "${x} ${y} ${p} ${binary} - 0.1% - O3"
srun ./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 1
srun ./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 10
srun ./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 100