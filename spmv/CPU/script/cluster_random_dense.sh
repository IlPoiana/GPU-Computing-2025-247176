#!/bin/bash

#SBATCH --job-name=firstCuda
#SBATCH --output=COO_CPU_dense%j.out
#SBATCH --error=my_error_%j.err
#SBATCH --partition=edu-short
#SBATCH --nodes=1
#SBATCH --gres=gpu:2
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=16
make COO_1flags
## TO DO

x=256
y=256
p=1
binary=1
# echo "${x} ${y} ${p} ${binary} - O3"
srun ./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 
x=512
y=512
p=1
binary=1
# echo "${x} ${y} ${p} ${binary} - O3"
srun ./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 
x=1024
y=1024
p=1
binary=1
# echo "${x} ${y} ${p} ${binary} - O3"
srun ./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 
x=2048
y=2048
p=1
binary=1
# echo "${x} ${y} ${p} ${binary} - O3"
srun ./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000
x=5096
y=5096
p=1
binary=1
# echo "${x} ${y} ${p} ${binary} - O3"
srun ./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000