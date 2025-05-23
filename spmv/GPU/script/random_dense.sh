#!/bin/bash

#SBATCH --job-name=CudaRnd
#SBATCH --output=GPU_rnd_dense%j.out
#SBATCH --error=my_error_%j.err
#SBATCH --partition=edu-short
#SBATCH --nodes=1
#SBATCH --gres=gpu:1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
module load CUDA/12.1.1
make
#Done
x=256
y=256
p=1
binary=1

srun coo_rnd ${x} ${y} ${p} ${binary} 100 1000 256
x=512
y=512
p=1
binary=1

srun coo_rnd ${x} ${y} ${p} ${binary} 100 1000 256
x=1024
y=1024
p=1
binary=1

srun coo_rnd ${x} ${y} ${p} ${binary} 100 1000 256
x=2048
y=2048
p=1
binary=1

srun coo_rnd ${x} ${y} ${p} ${binary} 100 1000 256
x=5096
y=5096
p=1
binary=1
srun coo_rnd ${x} ${y} ${p} ${binary} 100 1000 256
