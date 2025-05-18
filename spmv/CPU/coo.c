#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include "../lib.h"

//Benchmark

int main(int argc, char *args[])
{
    if (argc < 2)
    {
        printf("require filepath!");
        return 0;
    }
    if (argc < 3)
    {
        printf("insert 0 binary or 1 integer mtx\n");
        return 0;
    }
    if (argc < 4)
    {
        printf("insert 1 if you want all 1 vector, or the 1/p probabilty to generate a value\n");
        return 0;
    }
    if (argc < 5)
    {
        printf("tell the number of WARM-UP rounds");
        return 0;
    }
    if (argc < 6)
    {
        printf("tell the number of ITERATION rounds");
        return 0;
    }
    if (argc < 7)
    {
        printf("tell the matrix name");
        return 0;
    }

    char *file_path = args[1];
    int type = atoi(args[2]);
    int p = atoi(args[3]);
    int warm_up = atoi(args[4]);
    int iterations = atoi(args[5]);
    char *name = args[6];

    struct int_matrix mtx;
    if (type == 0){
        struct matrix tmp = import_matrix(file_path);
        mtx = convert_to_int_mtx(tmp); 
    }
    else if (type == 1)
        mtx = import_int_matrix(file_path); 
    else{
        printf("wrong import format!\n");
        return 0;
    }

    // printf("n: %d, x:%d, y:%d\n",mtx.n,mtx.x,mtx.y);

    int n = mtx.n;
    int *row = mtx.row;
    int *col = mtx.col;
    int *value = mtx.val;
    int *res = (int*)calloc(mtx.x, sizeof(int));
    int * arr = (int*)malloc(sizeof(int) * mtx.y);
    double * measures = (double*)malloc(sizeof(double) * iterations);

    for(int i = 0; i<mtx.y; i++){
        arr[i] = rand() % 1000000;//for not have to handle out of memory cases
    }

    struct timeval time1 = {0,0};
    struct timeval time2 = {0,0};
    double average;
    //initialize json
    printf("{\"name\":\"%s\",\"x\":%d,\n\"y\":%d,\"n\":%d,\"runs\":{",name,mtx.x,mtx.y,mtx.n);

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
    printf("{\"warmup\":%d,\"niter\":%d,\"avg\": %lf,\"std\": %lf}\n",warm_up,iterations,average,std(measures,average,iterations));
    
    printf("}}\n");
    free(arr);
    free(measures);
    free(res);
    return 0;
}
