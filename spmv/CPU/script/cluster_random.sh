#!/bin/bash

#SBATCH --job-name=firstCuda
#SBATCH --output=COO_CPU%j.out
#SBATCH --error=my_error_%j.err
#SBATCH --partition=edu-short
#SBATCH --nodes=1
#SBATCH --gres=gpu:0
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=4
make COO_flags
## TO DO

x=256
y=256
p=1
binary=1
echo "${x} ${y} ${p} ${binary} - O3"
./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 1
./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 100
x=512
y=512
p=1
binary=1
echo "${x} ${y} ${p} ${binary} - O3"
./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 1
./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 100
x=1024
y=1024
p=1
binary=1
echo "${x} ${y} ${p} ${binary} - O3"
./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 1
./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 100
x=2048
y=2048
p=1
binary=1
echo "${x} ${y} ${p} ${binary} - O3"
./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 1
./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 100
x=5096
y=5096
p=1
binary=1
echo "${x} ${y} ${p} ${binary} - O3"
./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 1
./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 100