#!/bin/bash

#SBATCH --job-name=firstCuda
#SBATCH --output=COO_CPU%j.out
#SBATCH --error=my_error_%j.err
#SBATCH --partition=edu-short
#SBATCH --nodes=1
#SBATCH --gres=gpu:0
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=4

module load CUDA/12.5.0

make COO_flags

x=1000
y=1000
p=1
binary=1

make COO_flags
echo "Optimization flags - 4 treads"
echo "1000 1000 1 1 - 100% - O1"
srun ./obj/coo1 ${x} ${y} ${p} ${binary} 100 1000 1
srun ./obj/coo1 ${x} ${y} ${p} ${binary} 100 1000 10
echo "O2"
srun ./obj/coo2 ${x} ${y} ${p} ${binary} 100 1000 1
srun ./obj/coo2 ${x} ${y} ${p} ${binary} 100 1000 10
echo "O3"
srun ./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 1
srun ./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 10

x=1000
y=1000
p=100
binary=1

make COO_flags
echo "Optimization flags - 4 treads"
echo "1000 1000 1 1 - 1% - O1"
srun ./obj/coo1 ${x} ${y} ${p} ${binary} 100 1000 1
srun ./obj/coo1 ${x} ${y} ${p} ${binary} 100 1000 10
echo "O2"
srun ./obj/coo2 ${x} ${y} ${p} ${binary} 100 1000 1
srun ./obj/coo2 ${x} ${y} ${p} ${binary} 100 1000 10
echo "O3"
srun ./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 1
srun ./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 10

x=10000
y=10000 
p=20
binary=1

echo "${x} ${y} ${p} ${binary} - 5% - O1"
srun ./obj/coo1 ${x} ${y} ${p} ${binary} 100 1000 1
srun ./obj/coo1 ${x} ${y} ${p} ${binary} 100 1000 10
echo "O2"
srun ./obj/coo2 ${x} ${y} ${p} ${binary} 100 1000 1
srun ./obj/coo2 ${x} ${y} ${p} ${binary} 100 1000 10
echo "O3"
srun ./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 1
srun ./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 10

x=10000
y=10000 
p=100
binary=1

echo "${x} ${y} ${p} ${binary} - 1% - O1"
srun ./obj/coo1 ${x} ${y} ${p} ${binary} 100 1000 1
srun ./obj/coo1 ${x} ${y} ${p} ${binary} 100 1000 10
srun ./obj/coo1 ${x} ${y} ${p} ${binary} 100 1000 100
echo "O2"
srun ./obj/coo2 ${x} ${y} ${p} ${binary} 100 1000 1
srun ./obj/coo2 ${x} ${y} ${p} ${binary} 100 1000 10
srun ./obj/coo2 ${x} ${y} ${p} ${binary} 100 1000 100
echo "O3"
srun ./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 1
srun ./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 10
srun ./obj/coo3 ${x} ${y} ${p} ${binary} 100 1000 100