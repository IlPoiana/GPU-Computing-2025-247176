#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

#define PRINT_RESULT_MATRIX(MAT, NAME, DIM) {    \
    printf("%2s matrix:\n\t", NAME);        \
    for (int i=0; i<DIM; i++) {               \
        for (int j=0; j<DIM; j++)             \
            printf("%4d ", MAT[i*DIM+j]);     \
        printf("\n\t");                     \
    }                                       \
    printf("\n");                           \
}


int main(int argc, char *args[]){
    int N = pow(2,atoi(args[1]));
    int *A = (int*)malloc(sizeof(int) * N * N);
    int *B = (int*)malloc(sizeof(int) * N * N);
    int *C = (int*)malloc(sizeof(int) * N * N);
    
    //time stuff
    struct timeval temp_1={0,0};
    struct timeval temp_2={0,0};
    printf("populating the matrices\n");
    gettimeofday(&temp_1, (struct timezone*)0);
    
    for(int i=0; i<N;i++){
        for(int j = 0; j<N; j++){
            A[i*N + j] = rand() % 3;
            B[i*N + j] = rand() % 3;
        }
    }
    if(argc>2 && atoi(args[2]) == 1){
        PRINT_RESULT_MATRIX(A,"A",N);
        PRINT_RESULT_MATRIX(B,"B",N);
    }
    gettimeofday(&temp_2, (struct timezone*)0);
    double time = ((temp_2.tv_sec-temp_1.tv_sec)*1.e6+(temp_2.tv_usec-temp_1.tv_usec));
    printf("time for initialize: %lf\n", time);
    
    //gemm - 2FLOP for N * N * N
    gettimeofday(&temp_1, (struct timezone*)0);
    for(int i=0; i<N;i++){ 
        for(int j = 0; j<N; j++){
            int res = 0;
            for(int q = 0; q < N; q++){
                res = res + A[i * N + q] * B[q*N + j];
            }
            C[i*N + j] = res;
        }
    }

    gettimeofday(&temp_2, (struct timezone*)0);
    time = ((temp_2.tv_sec-temp_1.tv_sec)*1.e6+(temp_2.tv_usec-temp_1.tv_usec));
    printf("gemm time: %lf\n", time);
    double FLOP = 2 * pow(N,3);
    if(time != 0)
        // printf("Elapsed time for computing and populate C: %lf", time);
        printf("FLOPs: %lf\n", FLOP / time);
    else
        printf("Matrix too small!\nFLOP: %lf\n", FLOP);

    if(argc>2 && atoi(args[2]) == 1){
        PRINT_RESULT_MATRIX(C,"C",N);
    }
}