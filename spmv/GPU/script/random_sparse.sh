#!/bin/bash

#SBATCH --job-name=CudaRnd
#SBATCH --output=GPU_rnd_sparse%j.out
#SBATCH --error=my_error_%j.err
#SBATCH --partition=edu-short
#SBATCH --nodes=1
#SBATCH --gres=gpu:1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
module load CUDA/12.1.1
make

x=256
y=256
p=2
binary=1
# echo "${x} ${y} ${p} ${binary} - O3"
srun coo_rnd ${x} ${y} ${p} ${binary} 100 1000 
x=512
y=512
p=2
binary=1
# echo "${x} ${y} ${p} ${binary} - O3"
srun coo_rnd ${x} ${y} ${p} ${binary} 100 1000 
x=1024
y=1024
p=2
binary=1
# echo "${x} ${y} ${p} ${binary} - O3"
srun coo_rnd ${x} ${y} ${p} ${binary} 100 1000 
x=2048
y=2048
p=2
binary=1
# echo "${x} ${y} ${p} ${binary} - O3"
srun coo_rnd ${x} ${y} ${p} ${binary} 100 1000
x=5096
y=5096
p=2
binary=1
# echo "${x} ${y} ${p} ${binary} - O3"
srun coo_rnd ${x} ${y} ${p} ${binary} 100 1000
x=256
y=256
p=100
binary=1
# echo "${x} ${y} ${p} ${binary} - O3"
srun coo_rnd ${x} ${y} ${p} ${binary} 100 1000 
x=512
y=512
p=100
binary=1
# echo "${x} ${y} ${p} ${binary} - O3"
srun coo_rnd ${x} ${y} ${p} ${binary} 100 1000 
x=1024
y=1024
p=100
binary=1
# echo "${x} ${y} ${p} ${binary} - O3"
srun coo_rnd ${x} ${y} ${p} ${binary} 100 1000 
x=2048
y=2048
p=100
binary=1
# echo "${x} ${y} ${p} ${binary} - O3"
srun coo_rnd ${x} ${y} ${p} ${binary} 100 1000
x=5096
y=5096
p=100
binary=1
# echo "${x} ${y} ${p} ${binary} - O3"
srun coo_rnd ${x} ${y} ${p} ${binary} 100 1000

