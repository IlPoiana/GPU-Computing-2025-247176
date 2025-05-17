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
    // PRINT_INT_MTX(mtx, COO);
    // printf("Running sparse matrix multiplication between a 1 vector and a integer value matrix\n");
    if (mtx.x == 0 && mtx.y == 0){
        printf("matrix not loaded correctly\n");
        return 0;
    }
    int n = mtx.n;
    int *row = mtx.row;
    int *col = mtx.col;
    int *value = mtx.val;
    int *res = (int*)calloc(row_n, sizeof(int));
    int * arr = (int*)malloc(sizeof(int) * mtx.y);
    double * measures = (double*)malloc(sizeof(double) * iterations);

    for(int i = 0; i<mtx.y; i++){
        arr[i] = rand() % 1000000;//for not have to handle out of memory cases
    }

    struct timeval time1 = {0,0};
    struct timeval time2 = {0,0};
    double average;
    printf("non 0 elem: %d\n", mtx.n);
    //initialize json
    printf("{\"x\":%d,\n\"y\":%d,\"n\":%d,\"runs\":{",mtx.x,mtx.y,mtx.n);

    for(int i = -warm_up; i< iterations; i++){
        if(i < 0 ){
            coo_multiplication(row,col,value,res,arr, n);
        }
        else{
            START_CPU_TIMER(&time1);
            coo_multiplication(row,col,value,res,arr, n);
            measures[i] = END_CPU_TIMER(&time1,&time2);
        }
    }
    average = avg(measures, iterations);
    printf("\"std\":");
    JSON_FORMAT_ITER(warm_up,iterations,average,std(measures,average,iterations));
    
    for(int i = -warm_up; i< iterations; i++){
        if(i < 0 ){
            coo_multiplication_OMP(row,col,value,res,arr, n);
        }
        else{
            START_CPU_TIMER(&time1);
            coo_multiplication_OMP(row,col,value,res,arr, n);
            measures[i] = END_CPU_TIMER(&time1,&time2);
        }
    }
    average = avg(measures, iterations);
    printf("\"std_OMP\":");
    JSON_FORMAT_ITER(warm_up,iterations,average,std(measures,average,iterations));
    

    for(int i = -warm_up; i< iterations; i++){
        if(i < 0 ){
            coo_multiplication_1(row,col,value,res,arr, n);
        }
        else{
            START_CPU_TIMER(&time1);
            coo_multiplication_1(row,col,value,res,arr, n);
            measures[i] = END_CPU_TIMER(&time1,&time2);
        }
    }
    average = avg(measures, iterations);
    printf("\"zero_skip\":");
    JSON_FORMAT_ITER(warm_up,iterations,average,std(measures,average,iterations));
    
    // PRINT_RESULT_ARRAY(res,"res", mtx.x);
    
    for(int i = -warm_up; i< iterations; i++){
        if(i < 0 ){
            coo_multiplication_1_OMP(row,col,value,res,arr, n);
        }
        else{
            START_CPU_TIMER(&time1);
            coo_multiplication_1_OMP(row,col,value,res,arr, n);
            measures[i] = END_CPU_TIMER(&time1,&time2);
        }
    }
    average = avg(measures, iterations);
    printf("\"zero_skip_OMP\":");
    JSON_FORMAT_ITER(warm_up,iterations,average,std(measures,average,iterations));
    

    for(int i = -warm_up; i< iterations; i++){
        if(i < 0 ){
            coo_multiplication_binary_unrolled(row,col,value,res,arr, n);
        }
        else{
            START_CPU_TIMER(&time1);
            coo_multiplication_binary_unrolled(row,col,value,res,arr, n);
            measures[i] = END_CPU_TIMER(&time1,&time2);
        }
    }
    average = avg(measures, iterations);
    printf("\"unroll\":");
    JSON_FORMAT_ITER(warm_up,iterations,average,std(measures,average,iterations));
    
    for(int i = -warm_up; i< iterations; i++){
        if(i < 0 ){
            coo_multiplication_b_u_OMP(row,col,value,res,arr, n);
        }
        else{
            START_CPU_TIMER(&time1);
            coo_multiplication_b_u_OMP(row,col,value,res,arr, n);
            measures[i] = END_CPU_TIMER(&time1,&time2);
        }
    }
    average = avg(measures, iterations);
    printf("\"unroll_OMP\":");
    JSON_FORMAT_ITER(warm_up,iterations,average,std(measures,average,iterations));
    

    for(int i = -warm_up; i< iterations; i++){
        if(i < 0 ){
            coo_multiplication_row_OMP(row,col,value,res,arr, n, mtx.x);
        }
        else{
            START_CPU_TIMER(&time1);
            coo_multiplication_row_OMP(row,col,value,res,arr, n,mtx.x);
            measures[i] = END_CPU_TIMER(&time1,&time2);
        }
    }
    average = avg(measures, iterations);
    printf("\"row_OMP\":");
    printf("{\"warmup\":%d,\"niter\":%d,\"avg\": %lf,\"std\": %lf}\n",warm_up,iterations,average,std(measures,average,iterations));
    
    printf("}}\n");
    free(arr);
    free(measures);
    free(res);
    return 0;

}