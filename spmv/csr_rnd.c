#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../lib.h"


struct int_matrix gen_rnd_CSR(int x, int y, int p, int binary){
    if(binary<1){
        printf("passed an invalid binary argument\n");
        struct int_matrix err = {0,0,0,0,0,0};
        return err;
    }

    int max_v = x * y;
    int * val = (int*)malloc(sizeof(int) * max_v);
    int * row = (int*)malloc(sizeof(int) * max_v);
    row[0] = 0; //initialize the first element
    int * col = (int*)malloc(sizeof(int) * max_v);
    
    int count = 0;
    int row_count = 1;
    int v_buff = 0;


    for(int i = 0; i < max_v;i++){
        if(i%y == 0 && i!=0){
            printf("change row, row count: %d - count: %d\n", row_count, count);
            row[row_count] = count;
            ++row_count;
        }

         //generate a value case
        v_buff = rand()%p;
        if(v_buff == 0){
            printf("gen value, row_count: %d - count: %d - i: %d\n", row_count, count, i);
            if(binary == 1){
                val[count] = 1;
            }
            else{
                val[count] = (rand() % binary) + 1; 
            }
            
            row[row_count] = count + 1; 
            
            col[count] = abs(y - i) % y;
            count = count + 1;
            printf("gen value, row_count: %d, count: %d\n", row_count, count);
        }
    }
    int * fval = (int*)malloc(sizeof(int) * count);
    int * frow = (int*)malloc(sizeof(int) * (row_count + 1));
    int * fcol = (int*)malloc(sizeof(int) * count);
    printf("row_count: %d\n", row_count);
    for( int i = 0; i < count | i <= x; i++){
        
        if(x > count){
            if(i > 0 && row[i] < row[i - 1]){
                frow[i] = frow[i - 1];
            }
            else{
                frow[i] = row[i];    
            }
        }
        else {
            if(i <= x)
                frow[i] = row[i];
            fval[i] = val[i];
            fcol[i] = col[i];
        }
    }

    struct int_matrix mtx = {x,y,count,frow,fcol,fval};
    return mtx;
}

void convert_COO_CSR(){}


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
    PRINT_RESULT_ARRAY(mtx.row,"x", mtx.x + 1);
    
    printf("Running sparse matrix multiplication between a 1 vector and a integer value matrix\n");
    
    if (mtx.x == 0 && mtx.y == 0){
        printf("matrix not loaded correctly\n");
        return 0;
    }
    int tot = mtx.n;
    int *row = mtx.row;
    int *col = mtx.col;
    int *value = mtx.val;
    int *res = (int*)calloc(col_n, sizeof(int));
    //not ordered matrix, spMV with a vector of all 1
    //all 1 vector len = col, remember that mtx starts from 1
    
    // int r_idx = 0;
    // for(int i = 0; i< tot; i++){
        
    //     printf("row[%d]: %d\n", i,row[i]);

    //     res[row[i]] = res[row[i]] + value[i]; 

    // }
    // PRINT_RESULT_ARRAY(res, "res", row_n);

    free(res);
    return 0;

}