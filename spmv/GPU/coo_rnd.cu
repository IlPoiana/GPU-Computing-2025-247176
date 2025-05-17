//COO for computing on random matrices

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Device code
__global__ void COO_k(float* value, float* row, float* col, int res)
{
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    
    if (i < N)
        {if(arr[col[i]] == 0)
            continue;
        res[row[i]] += value[i] * arr[col[i]];} 
}

__global__ resoid COO_1(float* value, float* row, float* col, int res)
{
    
    
}

__global__ void COO_Unrolled(float* value, float* row, float* col, int res)
{
    
}