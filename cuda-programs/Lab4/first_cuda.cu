#include <stdio.h>
#include <stdlib.h>

__global__ void myKernel(int * x){
    *x = *x + 1; 
}

// KEY TAKEAWAY
/**
 * cudaMallocManaged() creates a "virtual shared memory" between GPU and CPU.
 * BUT!!! it overwrite the modifications to the variables in the host after the cudaMallocManaged call.
 */

int main(){
    printf("starting host execution\n");
    // int * x = (int*)malloc(sizeof(int)); // we don't need this
    int * x;
    // *x= 2; 
    
    //here, the global GPU memory doesn't see the modification done before this point.
    cudaMallocManaged(&x, sizeof(int));
    printf("x: %d --> 0\n", *x);
    
    //now it see the "shared" adress of memory
    *x = 2;
    printf("x: %d --> 2\n", *x);
    myKernel<<<1,1>>>(x);
    cudaDeviceSynchronize();

    printf("x: %d", *x);

    return 0;
}