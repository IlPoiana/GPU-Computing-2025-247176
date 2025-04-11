#include <stdio.h>
#include <stdlib.h>
#include <time.h>

__global__ void add_kernel(int * x1, int * x2, int * res, int n){
    for(int i = 0; i< n; i++){
        res[i] = x1[i] + x2[i];
    }
}

int main(){
    printf("starting host execution\n");

    int N = 5;
    srand(time(NULL));
    int * x1 = (int*)malloc(sizeof(int) * N);
    int * x2 = (int*)malloc(sizeof(int) * N);
    int * res = (int*)malloc(sizeof(int) * N);

    for(int i = 0; i<N; i++){
        x1[i] = rand() % 100;
        x2[i] = rand() % 100;
    }

    printf("x1\n");
    for(int i = 0; i < N; i++){
        printf(" %d ", x1[i]);
    }


    printf("x2\n");
    for(int i = 0; i < N; i++){
        printf(" %d ", x2[i]);
    }
    //Create the memory in the GPU
    cudaMallocManaged(&x1, sizeof(int) * N);
    cudaMallocManaged(&x2, sizeof(int) * N);
    cudaMallocManaged(&res, sizeof(int) * N);

    //Cuda event for kernel performance time measure
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);
    //code here
    int blockNumber = 1;
    int threadNumber = 256;
    add_kernel<<<threadNumber,blockNumber>>>(x1,x2,res,N);

    cudaEventRecord(stop);
    cudaEventSynchronize(stop); //float
    double milliseconds = 0;

    cudaEventElapsedTime(&milliseconds, start, stop);
    printf("Kernel Time: %2f ms\n", milliseconds);

    cudaEventDestroy(start);
    cudaEventDestroy(stop);

    cudaFree(x1);
    cudaFree(x2);
    cudaFree(res);
    return 0;
}