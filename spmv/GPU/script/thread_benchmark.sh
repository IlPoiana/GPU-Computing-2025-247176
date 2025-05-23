#!/bin/bash

#SBATCH --job-name=CudaRnd
#SBATCH --output=GPU_thread%j.out
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
srun coo ${filepath} ${type} ${p} ${warmup} ${iter} 32
srun coo ${filepath} ${type} ${p} ${warmup} ${iter} 128
srun coo ${filepath} ${type} ${p} ${warmup} ${iter} 256
srun coo ${filepath} ${type} ${p} ${warmup} ${iter} 512
srun coo ${filepath} ${type} ${p} ${warmup} ${iter} 1024

# filepath=../../mtx/test_int3x3.mtx
# type=1
# ./obj/import_test ${filepath} ${type} ${p} 0 1

filepath=../../mtx/Stanford_bin.mtx
type=0
srun coo ${filepath} ${type} ${p} ${warmup} ${iter} 32
srun coo ${filepath} ${type} ${p} ${warmup} ${iter} 128
srun coo ${filepath} ${type} ${p} ${warmup} ${iter} 256
srun coo ${filepath} ${type} ${p} ${warmup} ${iter} 512
srun coo ${filepath} ${type} ${p} ${warmup} ${iter} 1024
filepath=../../mtx/delaunay_n24_bin.mtx
type=0
srun coo ${filepath} ${type} ${p} ${warmup} ${iter} 32
srun coo ${filepath} ${type} ${p} ${warmup} ${iter} 128
srun coo ${filepath} ${type} ${p} ${warmup} ${iter} 256
srun coo ${filepath} ${type} ${p} ${warmup} ${iter} 512
srun coo ${filepath} ${type} ${p} ${warmup} ${iter} 1024

type=1
filepath=../../mtx/oh2010_int.mtx
srun coo ${filepath} ${type} ${p} ${warmup} ${iter} 32
srun coo ${filepath} ${type} ${p} ${warmup} ${iter} 128
srun coo ${filepath} ${type} ${p} ${warmup} ${iter} 256
srun coo ${filepath} ${type} ${p} ${warmup} ${iter} 512
srun coo ${filepath} ${type} ${p} ${warmup} ${iter} 1024
type=1
filepath=../../mtx/mawi_201512020000_int.mtx
srun coo ${filepath} ${type} ${p} ${warmup} ${iter} 32
srun coo ${filepath} ${type} ${p} ${warmup} ${iter} 128
srun coo ${filepath} ${type} ${p} ${warmup} ${iter} 256
srun coo ${filepath} ${type} ${p} ${warmup} ${iter} 512
srun coo ${filepath} ${type} ${p} ${warmup} ${iter} 1024