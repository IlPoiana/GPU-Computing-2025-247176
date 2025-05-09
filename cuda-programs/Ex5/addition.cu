#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef TYPE
#define TYPE double
#endif

//Correct
__global__ void add_kernel(TYPE * x1, TYPE * x2, TYPE * res, int n){
    
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    
    if(index < n)
        res[index] = x1[index] + x2[index];
    
}

//Works only for `int` types
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
    TYPE * x1 = (TYPE *)malloc(sizeof(TYPE) * N);
    TYPE * x2 = (TYPE *)malloc(sizeof(TYPE) * N);
    TYPE * res = (TYPE *)malloc(sizeof(TYPE) * N);
    
    int blockSize = 256;
    int blockNumber = (N + blockSize -1) / blockSize;
    

    // Create the memory in the GPU
    cudaMallocManaged(&x1, sizeof(TYPE) * N);
    cudaMallocManaged(&x2, sizeof(TYPE) * N);
    cudaMallocManaged(&res, sizeof(TYPE) * N);

    for(int i = 0; i<N; i++){
        x1[i] = rand() % 1 + 1;
        x2[i] = rand() % 1 + 1;
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

    
    cudaEventRecord(stop);
    cudaEventSynchronize(stop); //float
    
    float milliseconds = 0;
    
    cudaEventElapsedTime(&milliseconds, start, stop);
    

    // printf("res\n");
    // print_arr(res,N);

    if(sizeof(TYPE) == sizeof(int))
        printf("\niteration %d -- result checking: %d = 2\n", N, res[N - 1]);
    else if(sizeof(TYPE) == sizeof(float))
        printf("\niteration %d -- result checking: %f = 2\n", N, res[N - 1]);
    else if(sizeof(TYPE) == sizeof(double))
        printf("\niteration %d -- result checking: %2f = 2\n", N, res[N - 1]);
    printf("\nKernel Time: %f ms\n", milliseconds);

    cudaEventDestroy(start);
    cudaEventDestroy(stop);

    cudaFree(x1);
    cudaFree(x2);
    cudaFree(res);
    return 0;
}