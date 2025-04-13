#include <stdio.h>
#include <stdlib.h>
#include <time.h>

__global__ void add_kernel_naive(int * x1, int * x2, int * res, int n){
    for(int i = 0; i< n; i++){
        res[i] = x1[i] + x2[i];
    }
}

__global__ void add_kernel(int * x1, int * x2, int * res, int n){
    
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    
    // if (n % ((blockIdx.x + 1) * blockDim.x) != 0){//means that is the block with more cores than threads
    //     if (index < (n % blockDim.x))
    //     {
    //         res[index] = x1[index] + x2[index];
    //     }    
    // }
    // else{
    //     res[index] = x1[index] + x2[index];

    // }
    res[index] = x1[index] + x2[index];
    
}

__global__ void add_kernel_jump(int * x1, int * x2, int * res, int n){
    for(int i = 0; i< n; i++){
        res[i] = x1[i] + x2[i];
    }
}

__global__ void plus_one(int * x1, int n){
    for(int i = 0; i< n; i++){
        x1[i]++;
    }
}

void print_arr(int * arr, int n){
    for(int i = 0; i < n; i++){
        printf(" %d ", arr[i]);
    }
}

int main(int argc, char * args[]){
    printf("starting host execution\n");
    if(argc < 1){
        printf("no dimension passed\n");
        return 0;
    }
    int N = atoi(args[1]);

    srand(time(NULL));
    int * x1;
    int * x2;
    int * res;
    
    int blockSize = 256;
    int blockNumber = (N + blockSize -1) / blockSize;
    

    // Create the memory in the GPU
    cudaMallocManaged(&x1, sizeof(int) * N);
    cudaMallocManaged(&x2, sizeof(int) * N);
    cudaMallocManaged(&res, sizeof(int) * N);

    for(int i = 0; i<N; i++){
        x1[i] = rand() % 100;
        x2[i] = rand() % 100;
    }

    // printf("x1\n");
    // print_arr(x1, N);

    // printf("\nx2\n");
    // print_arr(x2, N);

    //Cuda event for kernel performance time measure
    cudaEvent_t start, stop;
    cudaEventCreateWithFlags(&start, cudaEventBlockingSync);
    cudaEventCreateWithFlags(&stop, cudaEventBlockingSync);
    
    cudaEventRecord(start);
    //code here
    add_kernel<<<blockNumber,blockSize>>>(x1,x2,res,N);
    // plus_one<<<blockNumber,threadNumber>>>(x1,N);

    cudaEventRecord(stop);
    cudaEventSynchronize(stop); //float
    
    float milliseconds = 0;
    
    cudaEventElapsedTime(&milliseconds, start, stop);
    printf("\nKernel Time: %f ms\n", milliseconds);
    
    // printf("res\n");
    // print_arr(res,N);

    cudaEventDestroy(start);
    cudaEventDestroy(stop);

    cudaFree(x1);
    cudaFree(x2);
    cudaFree(res);
    return 0;
}