#!/bin/bash

#SBATCH --job-name=CudaRnd
#SBATCH --output=GPU_rnd_sparse_thread%j.out
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
p=2
binary=1

srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 32
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 128
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 256
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 512
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 1024
x=512
y=512
p=2
binary=1

srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 32
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 128
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 256
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 512
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 1024
x=1024
y=1024
p=2
binary=1

srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 32
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 128
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 256
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 512
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 1024
x=2048
y=2048
p=2
binary=1

srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 32
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 128
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 256
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 512
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 1024
x=5096
y=5096
p=2
binary=1

srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 32
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 128
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 256
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 512
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 1024
x=10000
y=10000
p=2
binary=1

srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 32
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 128
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 256
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 512
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 1024
x=256
y=256
p=100
binary=1

srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 32
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 128
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 256
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 512
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 1024
x=512
y=512
p=100
binary=1

srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 32
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 128
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 256
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 512
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 1024
x=1024
y=1024
p=100
binary=1

srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 32
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 128
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 256
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 512
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 1024
x=2048
y=2048
p=100
binary=1

srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 32
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 128
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 256
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 512
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 1024
x=5096
y=5096
p=100
binary=1

srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 32
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 128
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 256
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 512
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 1024
x=10000
y=10000
p=100
binary=1

srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 32
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 128
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 256
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 512
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 1024
x=50000
y=20000
p=100
binary=1

srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 32
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 128
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 256
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 512
srun coo_rnd ${x} ${y} ${p} ${binary} 10 100 1024

