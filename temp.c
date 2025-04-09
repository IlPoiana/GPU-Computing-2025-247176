#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "lib.h"

struct int_matrix {
    int x;
    int y;
    int n;
    int * row;
    int * col;
    int * val;
};

struct int_matrix import_int_matrix(char * file_path){
    FILE *file = fopen(file_path, "r");

    // Check if the file was opened successfully
    if (file == NULL) {
        perror("Error opening file");
        struct int_matrix err = {0,0,0,0,0};
        return err;
    }

    char myString[128] = "";
    int init = 1; //flag for initialize the number of elements
    
    int x; int y; int n;
    
    int *row; int *col;int *val;

    int index = 0;
    // Read the content and print it
    while(fgets(myString, 100, file)) {
        
        if(myString[0] == (char)37){}
        //if for populating the dimensions(x,y,n) of the matrix
        else if (init == 1){
            char dimx[16] = ""; char dimy[16] = "";char nelem[16] = "";
            int count = 3;
            for(int i = 0; (int)myString[i] != '\n'; i++){
                if((int)myString[i] != ' '){
                    char temp[2] = {myString[i],'\0'};
                    switch (count)
                    {
                    case 3:
                        strcat(dimx, temp);
                        break;
                    case 2:
                        strcat(dimy, temp); 
                        break;
                    case 1:
                        strcat(nelem, temp);
                        break;
                    default:
                        printf("why are you here!\n");
                        break;
                    }
                }
                else{
                    count = count - 1;
                }
                 
            }
                init = 0;
                x = atoi(dimx);y = atoi(dimy);n = atoi(nelem);
                fflush(stdout);
                row = (int*)malloc(sizeof(int) * n);
                col = (int*)malloc(sizeof(int) * n);
                val = (int*)malloc(sizeof(int) * n);
        }
        else{
            int count = 3;
            char xelem[16] = "";char yelem[16] = "";char valelem[16] = ""; 
            for(int i = 0; (int)myString[i] != '\n'; i++){
                if((int)myString[i] != ' '){
                    char temp[2] = {myString[i],'\0'};
                    switch (count)
                    {
                    case 3:
                        strcat(xelem, temp);
                        break;
                    case 2:
                        strcat(yelem, temp);
                        break;
                    case 1:
                        strcat(valelem,temp);
                        break;
                    default:
                        printf("why are you here!\n");
                        break;
                    }
                }
                else{
                    count = count - 1;
                }
            }
            row[index] = atoi(xelem);col[index] = atoi(yelem);val[index] = atoi(valelem);
            index = index + 1;
        }
    }

    // Close the file after finishing
    fclose(file);  
    //switch col and row
    struct int_matrix sm = {x,y,n,col, row, val};
    return sm;  
}

void PRINT_INT_MTX(struct int_matrix mtx){
    printf("x: %d\ny: %d\nn: %d\n", mtx.x, mtx.y, mtx.n);
    int val = 1;
    for(int i = 0; i< mtx.n; i++){
        if(mtx.row[i] > val){
            val = mtx.row[i];
            printf("-----\n");
        }
        printf("[%d,%d] = %d\n",mtx.row[i],mtx.col[i], mtx.val[i]);
        
    }

}

int main(int argc, char *args[]){

    char *str = "./mtx/test_int3x3.mtx";
    struct int_matrix mtx = import_int_matrix(str);
    PRINT_INT_MTX(mtx);

}