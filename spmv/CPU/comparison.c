#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include "../lib.h"

#define WARM_UP 20
#define N_ITER 100

int main(int argc, char *args[]){
    if (argc < 2 | argc < 3)
    {
        printf("require row and col number\n");
        return 0;
    }
    if (argc < 4){
        printf("insert the x: 1/ x probabilty to generate a value\n");
        return 0;
    }
    if (argc < 5){
        printf("tell if the random COO should be binary or not (>1)");
        return 0;
    }
    //random initializer
    srand(time(NULL));

    int row_n = atoi(args[1]);
    int col_n = atoi(args[2]); 
    int max_v = row_n * col_n;
    int p = atoi(args[3]);
    int binary = atoi(args[4]);
    printf("Passed arguments\nx: %d\ny: %d\np: %d\nbinary: %d\n\n",row_n,col_n,p,binary);
   
    double * measures = (double *)malloc(sizeof(double) * N_ITER); 
    struct timeval temp_1={0,0};
    struct timeval temp_2={0,0};
    double time;

    struct int_matrix coo = gen_rnd_COO(row_n, col_n,p,binary);
    // PRINT_INT_MTX(coo, COO);
    struct int_matrix csr = convert_COO_CSR(coo);
    // PRINT_INT_MTX(csr, CSR);
    int * arr = (int*)malloc(sizeof(int) * coo.y);
    for(int i = 0; i<coo.y; i++){
        arr[i] = rand() % 5;
    }
    // PRINT_RESULT_ARRAY(arr, "arr", coo.y);

    printf("Running sparse matrix multiplication between a 1 vector and a integer value matrix\n");

    printf("COO\n");
    int * res = (int*)calloc(coo.n, sizeof(int));
    int * row = coo.row;
    int * col = coo.col;
    int * value = coo.val;
    int tot = coo.n;

    
    for(int j = 0;j < WARM_UP + N_ITER; j++){
        gettimeofday(&temp_1, (struct timezone*)0);
        for(int i = 0; i< tot; i++){
            res[row[i]] = res[row[i]] + value[i] * arr[col[i]]; 
        }
        gettimeofday(&temp_2, (struct timezone*)0);
        time = ((temp_2.tv_sec-temp_1.tv_sec)*1.e6+(temp_2.tv_usec-temp_1.tv_usec));
        if(j>=WARM_UP)
            measures[j - WARM_UP] = time;
    }
    printf("average time for COO: %lf\n", avg(measures, N_ITER));

    
    
    printf("CSR\n");
    res = (int*)calloc(csr.n, sizeof(int));

    row = csr.row;
    col = csr.col;
    value = csr.val;
    int val_idx = 0;
    

    for(int j = 0;j < WARM_UP + N_ITER; j++){
        gettimeofday(&temp_1, (struct timezone*)0);
        for(int row_idx = 1; row_idx <= csr.x; row_idx++){
            if(row[row_idx] == row[row_idx - 1]){
                //skip
            }
            else{
                for(val_idx; val_idx < row[row_idx]; val_idx++){
                    res[row_idx - 1] += value[val_idx] * arr[col[val_idx]];
                }
            }
        }
        gettimeofday(&temp_2, (struct timezone*)0);
        time = ((temp_2.tv_sec-temp_1.tv_sec)*1.e6+(temp_2.tv_usec-temp_1.tv_usec));
        if(j>=WARM_UP)
            measures[j - WARM_UP] = time;
    }
    printf("average time for CSR: %lf\n", avg(measures, N_ITER));

    free(res);
    return 0;

}