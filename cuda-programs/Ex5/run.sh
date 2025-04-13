#!/bin/bash

#SBATCH --job-name=addition
#SBATCH --output=./out/my_output_%j.out
#SBATCH --error=./out/my_error_%j.err
#SBATCH --partition=edu5
#SBATCH --nodes=1
#SBATCH --gres=gpu:1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1

module load cuda

make all

srun ./obj/addition 10
srun ./obj/addition 256
srun ./obj/addition 512
srun ./obj/addition 1024
srun ./obj/addition 4096
srun ./obj/addition 10000
srun ./obj/addition 100000
srun ./obj/addition 1000000