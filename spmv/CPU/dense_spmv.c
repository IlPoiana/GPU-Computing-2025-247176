#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include "../lib.h"

void dense_spmv(int * mtx, int * arr,int * res, int row, int col){
    for(int i = 0;i < row; i++){
        for(int j = 0;j< col; j++){
            res[i] = res[i] + mtx[i*col + j] * arr[j];
        }
    }
}

int * convert_COO_dense(struct int_matrix coo){
    int row_n = coo.y;
    int col_n = coo.x;
    int * rarr = coo.row;
    int * carr = coo.col;
    // printf("%d, %d\n", row_n, col_n);
    int * mtx = (int *)calloc(row_n * col_n,sizeof(int));
    for(int v = 0; v < coo.n;v++){
        // printf("v:%d-> position: %d\n", v, row_n * rarr[v] + carr[v]);
        mtx[row_n * rarr[v] + carr[v]]= coo.val[v];
    } 
    return mtx;
}

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
    if (argc < 6){
        printf("tell the number of WARM-UP rounds");
        return 0;
    }
    if (argc < 7){
        printf("tell the number of ITERATION rounds");
        return 0;
    }
    //random initializer
    srand(time(NULL));


    int row_n = atoi(args[1]);
    int col_n = atoi(args[2]); 
    int max_v = row_n * col_n;
    int p = atoi(args[3]);
    int binary = atoi(args[4]);
    int warm_up = atoi(args[5]);
    int iterations = atoi(args[6]);
    // printf("Passed arguments\nx: %d\ny: %d\np: %d\nbinary: %d\n\n",row_n,col_n,p,binary);
   
    
    struct int_matrix mtx = gen_rnd_COO(row_n, col_n,p,binary);
    printf("non 0 elem: %d\n", mtx.n);
    // PRINT_INT_MTX(mtx, COO);
    int * dense = convert_COO_dense(mtx);
    
    // for(int i = 0;i < row_n; i++){
    //     for(int j = 0; j< col_n; j++){
    //         printf(" %d ",dense[i * row_n + j]);
    //     }
    //     printf("\n");
    // }
    int *res = (int*)calloc(row_n, sizeof(int));
    int * arr = (int*)malloc(sizeof(int) * col_n);
    double * measures = (double*)malloc(sizeof(double) * iterations);
    
    //All 1 vector
    for(int i = 0; i<col_n; i++){
        arr[i] = 1;
    }
    //not ordered matrix, spMV with a vector of all 1
    //all 1 vector len = col, remember that mtx starts from 1
    struct timeval time1 = {0,0};
    struct timeval time2 = {0,0};

    for(int i = -warm_up; i< iterations; i++){
        if(i < 0 ){

            dense_spmv(dense,arr,res,row_n,col_n);
        }
        else{
            START_CPU_TIMER(&time1);
            dense_spmv(dense,arr,res,row_n,col_n);
            measures[i] = END_CPU_TIMER(&time1,&time2);
        }
    }
    printf("all 1\n");
    // PRINT_RESULT_ARRAY(arr,"arr",col_n);
    double average = avg(measures, iterations);
    JSON_FORMAT_ITER(warm_up,iterations,average,std(measures,average,iterations));
    

    //Random SpMV
    for(int i = 0; i<mtx.y; i++){
        arr[i] = rand()%100;
    }

    for(int i = -warm_up; i< iterations; i++){
        if(i < 0 ){
            dense_spmv(dense,arr,res,row_n,col_n);
        }
        else{
            START_CPU_TIMER(&time1);
            dense_spmv(dense,arr,res,row_n,col_n);
            measures[i] = END_CPU_TIMER(&time1,&time2);
        }
    }
    printf("random numbers\n");
    // PRINT_RESULT_ARRAY(arr,"arr",col_n);
    average = avg(measures, iterations);
    JSON_FORMAT_ITER(warm_up,iterations,average,std(measures,average,iterations));
    

      //Random SpMV
    for(int i = 0; i<mtx.y; i++){
        arr[i] = rand()%2;
    }

    for(int i = -warm_up; i< iterations; i++){
        if(i < 0 ){
            dense_spmv(dense,arr,res,row_n,col_n);
        }
        else{
            START_CPU_TIMER(&time1);
            dense_spmv(dense,arr,res,row_n,col_n);
            measures[i] = END_CPU_TIMER(&time1,&time2);
        }
    }
    printf("random numbers and 0\n");
    // PRINT_RESULT_ARRAY(arr,"arr",col_n);
    average = avg(measures, iterations);
    JSON_FORMAT_ITER(warm_up,iterations,average,std(measures,average,iterations));
    

    free(arr);
    free(measures);
    free(res);
    return 0;

}