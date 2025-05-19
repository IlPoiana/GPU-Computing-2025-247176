#!/bin/bash

#SBATCH --job-name=CudaBench
#SBATCH --output=GPU_benchmark_%j.out
#SBATCH --error=my_error_%j.err
#SBATCH --partition=edu-short
#SBATCH --nodes=1
#SBATCH --gres=gpu:1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
module load CUDA/12.1.1
make

filepath=../../mtx/ash85.mtx
type=0
p=1
warmup=10
iter=100

make 
srun coo ${filepath} ${type} ${p} ${warmup} ${iter} 1024
# FINISH