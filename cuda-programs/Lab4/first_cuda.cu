#include <stdio.h>
#include <stdlib.h>

__global__ void myKernel(){
}


int main(){
    printf("starting host execution\n");
    myKernel<<<1,1>>>();
    return 0;
}