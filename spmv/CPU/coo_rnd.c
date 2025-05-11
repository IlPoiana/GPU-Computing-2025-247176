#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    int iteration = atoi(args[6]);
    printf("Passed arguments\nx: %d\ny: %d\np: %d\nbinary: %d\n\n",row_n,col_n,p,binary);
   

    struct int_matrix mtx = gen_rnd_COO(row_n, col_n,p,binary);
    PRINT_INT_MTX(mtx, COO);
    
    printf("Running sparse matrix multiplication between a 1 vector and a integer value matrix\n");
    
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
    for(int i = 0; i<mtx.y; i++){
        arr[i] = 1; // FIX IT??
    }
    //not ordered matrix, spMV with a vector of all 1
    //all 1 vector len = col, remember that mtx starts from 1
    
    for(int i = -warm_up; i< iteration; i++){
        res = coo_multiplication(mtx,arr)
        printf("CHECK 1, is the multiplication correct?\n");
        PRINT_RESULT_ARRAY(res,'res',mtx.y);
        return 0;
        if(i <= warm_up ){
        }
        else{
            
        }
    }

    free(res);
    return 0;

}