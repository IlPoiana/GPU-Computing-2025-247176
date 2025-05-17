#!/bin/bash

#SBATCH --job-name=CudaTest
#SBATCH --output=GPU_test%j.out
#SBATCH --error=my_error_%j.err
#SBATCH --partition=edu-short
#SBATCH --nodes=1
#SBATCH --gres=gpu:1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
module load CUDA/12.1.1
make

srun ./coo_rnd 2 2 1 1 0 1
srun ./coo_rnd 3 1001 1 1 0 1

