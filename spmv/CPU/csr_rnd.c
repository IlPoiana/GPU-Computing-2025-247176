#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../lib.h"


//DEPRECATED (int -> long)



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
        printf("tell if the random COO should be binary or not (>1)\n");
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

    struct int_matrix mtx = gen_rnd_CSR(row_n, col_n,p,binary);
    
    PRINT_INT_MTX(mtx,CSR);
    
    // PRINT_RESULT_ARRAY(mtx.row,"row", mtx.x + 1);
    // PRINT_RESULT_ARRAY(mtx.col,"col", mtx.n);

    printf("Running sparse matrix multiplication between a 1 vector and a integer value matrix\n");
    
    if (mtx.x == 0 && mtx.y == 0){
        printf("matrix not loaded correctly\n");
        return 0;
    }
    int *row = mtx.row;
    int *value = mtx.val;
    int *res = (int*)calloc(col_n, sizeof(int));
    
    
    int val_idx = 0;
    for(int row_idx = 1; row_idx <= mtx.x; row_idx++){
        if(row[row_idx] == row[row_idx - 1]){
            //skip
        }
        else{
            for(val_idx; val_idx < row[row_idx]; val_idx++){
                res[row_idx - 1] += value[val_idx];
            }
        }
    }

    PRINT_RESULT_ARRAY(res, "res", row_n);

    free(res);
    return 0;

}