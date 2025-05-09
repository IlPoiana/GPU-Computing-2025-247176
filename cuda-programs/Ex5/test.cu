#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Device code
__global__ void VecAdd(float* A, float* B, float* C, int N)
{
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if (i < N)
        C[i] = A[i] + B[i];
}

void print_arr(int * arr, int n){
    for(int i = 0; i < n; i++){
        printf(" %d ", arr[i]);
    }
}

// Host code
int main(int argc, char * args[])
{
    int N = atoi(args[1]);
    size_t size = N * sizeof(float);

    // Allocate input vectors h_A and h_B in host memory
    float* h_A = (float*)malloc(size);
    float* h_B = (float*)malloc(size);
    float* h_C = (float*)malloc(size);

    // Initialize input vectors
    srand(time(NULL));
    int * x1 = (int *)malloc(sizeof(int) * N);
    int * x2 = (int *)malloc(sizeof(int) * N);
    int * res = (int *)malloc(sizeof(int) * N);
    
    for(int i = 0; i<N; i++){
        x1[i] = rand() % 1 + 1;
        x2[i] = rand() % 1 + 1;
    }


    // Allocate vectors in device memory
    float* d_A;
    cudaMalloc(&d_A, size);
    float* d_B;
    cudaMalloc(&d_B, size);
    float* d_C;
    cudaMalloc(&d_C, size);

    // Copy vectors from host memory to device memory
    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    // Invoke kernel
    int threadsPerBlock = 256;
    int blocksPerGrid =
            (N + threadsPerBlock - 1) / threadsPerBlock;
    VecAdd<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);
    cudaDeviceSynchronize();
    // Copy result from device memory to host memory
    // h_C contains the result in host memory
    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);
    fflush(stdout);
    printf("res\n");
    print_arr(res,N);
    printf("\n");
    
    // Free device memory
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

}