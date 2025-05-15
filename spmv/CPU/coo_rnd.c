#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include "../lib.h"


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
    if (argc < 8){
        printf("tell the density of the vector-> 1 == all");
        return 0;
    }
    //random initializer
    // srand(time(NULL));


    long row_n = atoi(args[1]);
    long col_n = atoi(args[2]); 
    long max_v = row_n * col_n;
    int p = atoi(args[3]);
    int binary = atoi(args[4]);
    int warm_up = atoi(args[5]);
    int iterations = atoi(args[6]);
    int d = atoi(args[7]);
    // printf("Passed arguments\nx: %d\ny: %d\np: %d\nbinary: %d\n\n",row_n,col_n,p,binary);
   
    struct long_matrix mtx = gen_rnd_COO(row_n, col_n,p,binary);
    // PRINT_INT_MTX(mtx, COO);
    // PRINT_LONG_MTX(mtx,COO);
    // printf("Running sparse matrix multiplication between a 1 vector and a integer value matrix\n");
    if (mtx.x == 0 && mtx.y == 0){
        printf("matrix not loaded correctly\n");
        return 0;
    }
    long tot = mtx.n;
    long *row = mtx.row;
    long *col = mtx.col;
    long *value = mtx.val;
    long *res = (long*)calloc(row_n, sizeof(long));
    long * arr = (long*)malloc(sizeof(long) * mtx.y);
    double * measures = (double*)malloc(sizeof(double) * iterations);
    
    long arr_sparsity = 0;
    for(long i = 0; i<mtx.y; i++){
        if(d == 1)
            arr[i] = 1;
        else{
            arr[i] = rand()%d == 0 ? binary : 0;
            if(arr[i] == 0){
                arr_sparsity+=1;
            }
        }
    }
    printf("non 0 elem: %ld - arr sparsity: %ld\n", mtx.n, arr_sparsity);
    //not ordered matrix, spMV with a vector of all 1
    //all 1 vector len = col, remember that mtx starts from 1
    struct timeval time1 = {0,0};
    struct timeval time2 = {0,0};

    for(int i = -warm_up; i< iterations; i++){
        if(i < 0 ){
            res = coo_multiplication_1(row,col,value,res,arr, tot);
        }
        else{
            START_CPU_TIMER(&time1);
            res = coo_multiplication_1(row,col,value,res,arr, tot);
            measures[i] = END_CPU_TIMER(&time1,&time2);
        }
        if(i != iterations - 1)
            reset_array(res, row_n);
    }
    double average = avg(measures, iterations);
    JSON_FORMAT_ITER(warm_up,iterations,average,std(measures,average,iterations));
    // PRINT_RESULT_ARRAY(res,"std",row_n);

    for(int i = -warm_up; i< iterations; i++){
        if(i < 0 ){
            res = coo_multiplication_1_OMP(row,col,value,res,arr, tot);
        }
        else{
            START_CPU_TIMER(&time1);
            res = coo_multiplication_1_OMP(row,col,value,res,arr, tot);
            measures[i] = END_CPU_TIMER(&time1,&time2);
        }
        if(i != iterations - 1)
            reset_array(res, row_n);
    }
    average = avg(measures, iterations);
    // printf("OpenMP\n");
    // printf("[");
    // for(int i = 0; i < iterations; i++){
    //     printf("%lf,",measures[i]);
    // }
    // printf("]\n");
    JSON_FORMAT_ITER(warm_up,iterations,average,std(measures,average,iterations));
    // PRINT_RESULT_ARRAY(res,"MP",row_n);

    for(int i = -warm_up; i< iterations; i++){
        if(i < 0){
            res = coo_multiplication_binary_unrolled(row,col,value,res,arr, tot);
        }
        else{
            START_CPU_TIMER(&time1);
            res = coo_multiplication_binary_unrolled(row,col,value,res,arr, tot);
            measures[i] = END_CPU_TIMER(&time1,&time2);
        }
        if(i != iterations - 1)
            reset_array(res, row_n);
    }
    average = avg(measures, iterations);
    printf("Unrolled\n");
    JSON_FORMAT_ITER(warm_up,iterations,average,std(measures,average,iterations));
    // PRINT_RESULT_ARRAY(res,"Unrolled",row_n);

    for(int i = -warm_up; i< iterations; i++){
        if(i < 0){
            res = coo_multiplication_b_u_OMP(row,col,value,res,arr, tot);
        }
        else{
            START_CPU_TIMER(&time1);
            res = coo_multiplication_b_u_OMP(row,col,value,res,arr, tot);
            measures[i] = END_CPU_TIMER(&time1,&time2);
        }
        if(i != iterations - 1)
            reset_array(res, row_n);
    }
    average = avg(measures, iterations);
    printf("Unrolled OpenMP\n");
    // printf("[");
    // for(int i = 0; i < iterations; i++){
    //     printf("%lf,",measures[i]);
    // }
    // printf("]\n");
    JSON_FORMAT_ITER(warm_up,iterations,average,std(measures,average,iterations));
    // PRINT_RESULT_ARRAY(res,"UnrolledMP",row_n);
    
    
    printf("---\n");
    free(arr);
    free(measures);
    free(res);
    return 0;

}