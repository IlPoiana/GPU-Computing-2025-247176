#!/bin/bash

#SBATCH --job-name=firstCuda
#SBATCH --output=my_output_%j.out
#SBATCH --error=my_error_%j.err
#SBATCH --partition=edu5
#SBATCH --nodes=1
#SBATCH --gres=gpu:1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1

module load cuda

make all

srun ./obj/first