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


    int row_n = atoi(args[1]);
    int col_n = atoi(args[2]); 
    int max_v = row_n * col_n;
    int p = atoi(args[3]);
    int binary = atoi(args[4]);
    int warm_up = atoi(args[5]);
    int iterations = atoi(args[6]);
    int d = atoi(args[7]);
    // printf("Passed arguments\nx: %d\ny: %d\np: %d\nbinary: %d\n\n",row_n,col_n,p,binary);
   

    struct int_matrix mtx = gen_rnd_COO(row_n, col_n,p,binary);
    // PRINT_INT_MTX(mtx, COO);
    
    // printf("Running sparse matrix multiplication between a 1 vector and a integer value matrix\n");
    
    if (mtx.x == 0 && mtx.y == 0){
        printf("matrix not loaded correctly\n");
        return 0;
    }
    int tot = mtx.n;
    int *row = mtx.row;
    int *col = mtx.col;
    int *value = mtx.val;
    int *res = (int*)calloc(row_n, sizeof(int));
    int * arr = (int*)malloc(sizeof(int) * mtx.y);
    double * measures = (double*)malloc(sizeof(double) * iterations);
    
    int nonzero = 0;
    for(int i = 0; i<mtx.y; i++){
        if(d == 1)
            arr[i] = 1;
        else{
            arr[i] = rand()%d == 0 ? binary : 0;
        }
        // arr[i] = rand() % 10 == 0 ? 1 : 0;
        // if(arr[i] != 0) ++nonzero;
    }
    printf("%d",nonzero);
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
    }
    double average = avg(measures, iterations);
    printf("non 0 elem: %d\n", mtx.n);
    JSON_FORMAT_ITER(warm_up,iterations,average,std(measures,average,iterations));
    free(arr);
    free(measures);
    free(res);
    return 0;

}