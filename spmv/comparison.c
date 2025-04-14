#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../lib.h"

/**
 * arr needs to be same size of mtx.y
 */
int * coo_multiplication(struct int_matrix mtx, int * arr){
    int * res = (int*)calloc(mtx.n, sizeof(int));
    int * row = mtx.row;
    int * col = mtx.col;
    int * value = mtx.val;
    int tot = mtx.n;
    for(int i = 0; i< tot; i++){
        res[row[i]] = res[row[i]] + value[i] * arr[col[i]]; 
    }
    return res;
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
    //random initializer
    srand(time(NULL));

    int row_n = atoi(args[1]);
    int col_n = atoi(args[2]); 
    int max_v = row_n * col_n;
    int p = atoi(args[3]);
    int binary = atoi(args[4]);
    printf("Passed arguments\nx: %d\ny: %d\np: %d\nbinary: %d\n\n",row_n,col_n,p,binary);
   

    struct int_matrix coo = gen_rnd_COO(row_n, col_n,p,binary);
    PRINT_INT_MTX(coo, COO);
    struct int_matrix csr = convert_COO_CSR(coo);
    PRINT_INT_MTX(csr, CSR);
    int * arr = (int*)malloc(sizeof(int) * coo.y);
    for(int i = 0; i<coo.y; i++){
        arr[i] = rand() % 5;
    }
    PRINT_RESULT_ARRAY(arr, "arr", coo.y);

    printf("Running sparse matrix multiplication between a 1 vector and a integer value matrix\n");

    int *res = (int*)calloc(col_n, sizeof(int));
    
    res = coo_multiplication(coo, arr);

    PRINT_RESULT_ARRAY(res, "res", row_n);

    free(res);
    return 0;

}