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

/*
* params:
    - `A`,`B`: matrices you want to multiply in the form A*B (square matrix assumption)
    - `C`: matrix where to store the result of the matrix multiplication, `block_dim` size
    - `start0`: index of the `A` matrix block, sorted as a 1d array with stride equal to block dim
        - ex. 4x4 matrix divided in block of 2x2, I have indexes [0,1,2,3]
    - `start1`: same of start0 but for matrix `B`
    - `block_dim`: block dimension (square matrix assumption)
    - `total_dim`: dimension of A & B, a multiple of block_dim
*/
void matrix_multiplication(int* A,int* B,int* C,int start0, int start1, int block_dim, int total_dim){
    int ratio = total_dim / block_dim;
    //skip number of rows equal to total dimension * block_dimension for start / ratio
    for(int i=0; i< block_dim;i++){ 
        for(int j = 0; j< block_dim; j++){
            int res = 0;

            for(int q = 0; q < block_dim; q++){
                // printf("A [i = %d , q = %d] = %d\n",i,q,A[((start0 / ratio)  * total_dim * block_dim) + ((start0 % ratio) * block_dim) + i * total_dim + q]);
                // printf("B [q = %d , j = %d] = %d\n",q,j,B[((start1 / ratio)  * total_dim * block_dim) + ((start1 % ratio) * block_dim) + q * total_dim + j]);
                res = res + 
                A[((start0 / ratio)  * total_dim * block_dim) + ((start0 % ratio) * block_dim) + i * total_dim + q] * 
                B[((start1 / ratio)  * total_dim * block_dim) + ((start1 % ratio) * block_dim) + q * total_dim + j]; 
            }
            // printf("---\nres: %d\n", res);
            C[i*block_dim + j] = res;
        }
    }

}

/*
Assuming SUBM square
*/
void sub_matrix_sum(int* C, int* SUBM, int start, int block_dim, int total_dim){
    int ratio = total_dim / block_dim;
    for(int i = 0; i < block_dim; i++ )
        for(int j = 0; j < block_dim; j++){
            C[((start / ratio)  * total_dim * block_dim) + ((start % ratio) * block_dim) + i * total_dim + j ] = 
            C[((start / ratio)  * total_dim * block_dim) + ((start % ratio) * block_dim) + i * total_dim + j ] + 
            SUBM[i * block_dim + j];
        }
}




struct block_time
{
    int block_size;
    double time;
};



int main(int argc, char *args[]){
    int N;

    if(argc < 2){
        printf("no matrix dimension specified! Assuming 10");
        N = 1024;
    }
    else{
        N = pow(2,atoi(args[1]));
    }

    
    int *A = (int*)malloc(sizeof(int) * N * N);
    int *B = (int*)malloc(sizeof(int) * N * N);
    //time stuff
    struct timeval temp_1={0,0};
    struct timeval temp_2={0,0};
    printf("populating the matrices\n");
    gettimeofday(&temp_1, (struct timezone*)0);
    
    for(int i=0; i<N;i++){
        for(int j = 0; j<N; j++){
            A[i*N + j] = rand() % 2;
            B[i*N + j] = rand() % 2;
        }
    }
    if(argc>2 && atoi(args[2]) == 1){
        PRINT_RESULT_MATRIX(A,"A",N);
        PRINT_RESULT_MATRIX(B,"B",N);
    }
    gettimeofday(&temp_2, (struct timezone*)0);
    double time = ((temp_2.tv_sec-temp_1.tv_sec)*1.e6+(temp_2.tv_usec-temp_1.tv_usec));
    
    printf("time for initialize: %lf\n", time);
    // int block_dim = 4;
    // int *Ctemp = (int*)malloc(sizeof(int) * block_dim * block_dim);
    // matrix_multiplication(A,B,Ctemp,0,1,block_dim,N);
    // PRINT_RESULT_MATRIX(Ctemp,"Ctemp",block_dim);
    // return 0;
    // //gemm - 2FLOP for N * N * N
    // gettimeofday(&temp_1, (struct timezone*)0);
    // for(int i=0; i<N;i++){ 
    //     for(int j = 0; j<N; j++){
    //         int res = 0;
    //         for(int q = 0; q < N; q++){
    //             res = res + A[i * N + q] * B[q*N + j];
    //         }
    //         C[i*N + j] = res;
    //     }
    // }

    // gettimeofday(&temp_2, (struct timezone*)0);
    // time = ((temp_2.tv_sec-temp_1.tv_sec)*1.e6+(temp_2.tv_usec-temp_1.tv_usec));
    // printf("gemm time: %lf\n", time);
    // double FLOP = 2 * pow(N,3);
    // if(time != 0)
    //     // printf("Elapsed time for computing and populate C: %lf", time);
    //     printf("FLOPs: %lf\n", FLOP / time);
    // else
    //     printf("Matrix too small!\nFLOP: %lf\n", FLOP);


    // do a for loop, that tries every multiple of matrix size, store them in a array and print them at terminal
    int m = 2;
    int n = 1;
    
    int len = atoi(args[1]) - 1;
    struct block_time btimes[len];
    printf("starting blocks computations\n");
    fflush(stdout);
    for(m = 2; m < N; m = pow(2,n)){
        printf("block %d\n",m);
        int *C = (int*)calloc(N * N ,sizeof(int));
        // printf("here!");
        // fflush(stdout);
        //iterate for every block of size m, so k =  N/m times    
        gettimeofday(&temp_1, (struct timezone*)0);
        
        // define the N/m ^ 2 sub C matrices blocks
        int *Ctemp = (int*)malloc(sizeof(int) * m * m);
        //k control the block row of C
        for(int k = 0; k < N/m; k++){
            //j control the column block row of C, for every full j loop, i go through the entire B
            for(int j = 0; j < N/m; j++){
                for(int q = 0;q < N/m; q++){
                    //matrix multiplication between blocks
                    // printf("k = %d, j = %d, q = %d | %d - %d\n", k, j, q, (k * m)+ j, q + (j * m));
                    //matrix multiplication correct!
                    matrix_multiplication(A,B,Ctemp, (k * N/m)+ j, q + (j * N/ m), m, N);   
                    // PRINT_RESULT_MATRIX(Ctemp,"Ctemp", m);
                    sub_matrix_sum(C, Ctemp,k * N/m + q, m, N);
                    // printf("C stored, %d\n",q + k * N/m);
                }
                    
            }

        }
        // printf("block dimension: %d\n", m);
        // PRINT_RESULT_MATRIX(C,"C",N);
        
        gettimeofday(&temp_2, (struct timezone*)0);
        
        free(Ctemp);
        free(C);

        time = ((temp_2.tv_sec-temp_1.tv_sec)*1.e6+(temp_2.tv_usec-temp_1.tv_usec));
        
        // save the result
        // printf("saving in %d\n", n-1);
        btimes[n-1].block_size = m;
        btimes[n-1].time = time;
        n = n + 1;
    }

    double min = __FLT64_MAX__;
    int nblock = 0;
    for(int i = 0;i< len; i++){
        printf("Matrix block %d | Elapsed time %lf\n", btimes[i].block_size, btimes[i].time);
        if(btimes[i].time < min){
            min = btimes[i].time;
            nblock = btimes[i].block_size;
        }
    }

    printf("best Block: %d, best time: %lf", nblock, min);

    free(A);free(B);
    return 0;
}