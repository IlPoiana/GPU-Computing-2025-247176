#!/bin/bash

#SBATCH --job-name=addition
#SBATCH --output=./out/my_output_%j.out
#SBATCH --error=./out/my_error_%j.err
#SBATCH --partition=edu-short
#SBATCH --nodes=1
#SBATCH --gres=gpu:1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1

module load CUDA/12.1.1

make all

# srun ./obj/test 2
# srun ./obj/test 257
srun ./obj/addition 1
srun ./obj/addition 200
srun ./obj/addition 256
srun ./obj/addition 257
srun ./obj/addition 511
srun ./obj/addition 512
srun ./obj/addition 1024
srun ./obj/addition 4096
srun ./obj/addition 10000
srun ./obj/addition 100000
srun ./obj/addition 1000000
srun ./obj/addition 10000000