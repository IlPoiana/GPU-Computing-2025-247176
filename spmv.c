#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "lib.h"


/**
 * @brief 
 * 
 * @param argc 
 * @param args 
 * @return int 
 */
int main(int argc, char *args[]){
    if (argc < 2)
    {
        printf("not passed a file path to a .mtx file\n");
        return 0;
    }
    
    if(argc < 3){
        printf("not passed matrix type: 0 for binary 1 for integer\n");
        return 0;
    }

    char * str = args[1];
    int select = atoi(args[2]);
    

    if (select != 1){
        select = 0;
    }
    if(fopen(str, "r") == NULL){
        printf("file path not valid\n");
        return 0;
    }
    

    if(select == 0){
        
        struct matrix mtx = import_matrix(str);
        printf("running sparse matrix multiplication between a 1 vector and %s\n",str);
        
        printf("x: %d,y: %d,n: %d\n",mtx.x, mtx.y, mtx.n);
        if (mtx.x == 0 && mtx.y == 0){
            printf("matrix not loaded correctly\n");
            return 0;
        }
        int row_n = mtx.x;
        int col_n = mtx.y;
        int tot = mtx.n;
        int *row = mtx.row;
        int *col = mtx.col;
        int *res = (int*)calloc(col_n, sizeof(int));
        //not ordered matrix, spMV with a vector of all 1
        //all 1 vector len = col, remember that mtx starts from 1
        
        int r_idx = 0;
        printf("starting looping\n");
        
        for(int i = 0; i< tot; i++){
            
            // printf("row[%d]: %d - r_idx: %d\n", i,row[i], r_idx);

            if((row[i] - 1) > r_idx){
                r_idx = row[i] - 1;
            }
            res[r_idx] = res[r_idx] + 1; 

        }
        PRINT_RESULT_ARRAY(res, "res", col_n);

        return 0;
    } else if( select == 1){
        struct int_matrix mtx = import_int_matrix(str);
        printf("Running sparse matrix multiplication between a 1 vector and a integer value matrix %s\n",str);
        
        if (mtx.x == 0 && mtx.y == 0){
            printf("matrix not loaded correctly\n");
            return 0;
        }
        int row_n = mtx.x;
        int col_n = mtx.y;
        int tot = mtx.n;
        int *row = mtx.row;
        int *col = mtx.col;
        int *value = mtx.val;
        int *res = (int*)calloc(col_n, sizeof(int));
        //not ordered matrix, spMV with a vector of all 1
        //all 1 vector len = col, remember that mtx starts from 1
        
        int r_idx = 0;
        PRINT_INT_MTX(mtx);
        printf("start looping\n");
        for(int i = 0; i< tot; i++){
            
            // printf("row[%d]: %d - r_idx: %d\n", i,row[i], r_idx);

            if((row[i] - 1) > r_idx){
                r_idx = row[i] - 1;
            }
            res[r_idx] = res[r_idx] + value[i]; 

        }
        PRINT_RESULT_ARRAY(res, "res", col_n);

        return 0;
    }
    
}