#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define COO 0
#define CSR 1

struct matrix{
    int x;
    int y;
    int n;
    int * row;
    int * col;
};

/**
 * @brief (x,y,n,row,col,val arrays)
 * 
 */
struct int_matrix {
    int x;
    int y;
    int n;
    int * row;
    int * col;
    int * val;
};


void PRINT_INT_MTX(struct int_matrix mtx, int FORMAT){
    printf("x: %d\ny: %d\nn: %d\n", mtx.x, mtx.y, mtx.n);
    if(FORMAT == COO){
        printf("format COO\n");
        int val = 0;
        for(int i = 0; i< mtx.n; i++){
            if(mtx.row[i] > val){
                val = mtx.row[i];
                printf("-----\n");
            }
            printf("[%d,%d] = %d\n",mtx.row[i],mtx.col[i], mtx.val[i]);
            
        }
    }
    else if(FORMAT == CSR){
        printf("format CSR\n");
        //skip to the first non zero value row
        int row_idx = 1;
        for(int i = 1; i<=mtx.x;i++){
            if(mtx.row[i] == 0){
                ++row_idx;
            }
            else{
                break;
            }

            printf("skip\n");
        }
        for (int i = 0; i < mtx.n; i++)
        {
            if(i == mtx.row[row_idx]){
                ++row_idx;
            } 
            printf("[%d,%d] = %d\n",row_idx - 1,mtx.col[i], mtx.val[i]);
        }
        
    }
    else{
        printf("not a valid format!\n");
    }

}

/**
 * @brief Supposing it's a square matrix
 * 
 */
#define PRINT_RESULT_MATRIX(MAT, NAME, DIM) {    \
    printf("%2s matrix:\n\t", NAME);        \
    for (int i=0; i<DIM; i++) {               \
        for (int j=0; j<DIM; j++)             \
            printf("%4d ", MAT[i*DIM+j]);     \
        printf("\n\t");                     \
    }                                       \
    printf("\n");                           \
}

void PRINT_RESULT_ARRAY(int * MAT, char * NAME, int DIM) {    
    printf("%2s array:\n\t", NAME);            
    for (int I=0; I<DIM; I++) {                   
        printf("%d ",MAT[I]);                   
        printf("\n\t");                      
    }                                                         
    printf("\n");                                          
} 

struct matrix import_matrix(char * file_path){
    FILE *file = fopen(file_path, "r");

    // Check if the file was opened successfully
    if (file == NULL) {
        perror("Error opening file");
        struct matrix err = {0,0,0,0,0};
        return err;
    }

    char myString[128] = "";
    int init = 1; //flag for initialize the number of elements
    
    int x; int y; int n;
    
    int *row; int *col;

    int index = 0;
    // Read the content and print it
    while(fgets(myString, 100, file)) {
        
        if(myString[0] == (char)37){}
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
        }
        else{
            int count = 2;
            char xelem[16] = "";char yelem[16] = "";char c;  
            for(int i = 0; (int)myString[i] != '\n'; i++){
                if((int)myString[i] != ' '){
                    char temp[2] = {myString[i],'\0'};
                    switch (count)
                    {
                    case 2:
                        strcat(xelem, temp);
                        break;
                    case 1:
                        strcat(yelem, temp);
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
            row[index] = atoi(xelem);col[index] = atoi(yelem);
            index = index + 1;
        }
    }

    // Close the file after finishing
    fclose(file);  
    //switch col and row
    struct matrix sm = {x,y,n,col, row};
    return sm;  
}

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

struct int_matrix gen_rnd_COO(int x, int y, int p, int binary){
    if(binary<1){
        printf("passed an invalid binary argument\n");
        struct int_matrix err = {0,0,0,0,0,0};
        return err;
    }

    int max_v = x * y;
    int * val = (int*)malloc(sizeof(int) * max_v);
    int * row = (int*)malloc(sizeof(int) * max_v);
    int * col = (int*)malloc(sizeof(int) * max_v);
    
    int count = 0;
    int v_buff = 0;

    for(int i = 0; i < max_v;i++){
        v_buff = rand()%p;
        if(v_buff == 0){
            if(binary == 1){
                val[count] = 1;
            }
            else{
                val[count] = (rand() % binary) + 1; 
            }
            row[count] = i / y; 
            col[count] = abs(y - i) % y;
            count = count + 1;
        }    
    }
    int * fval = (int*)malloc(sizeof(int) * count);
    int * frow = (int*)malloc(sizeof(int) * count);
    int * fcol = (int*)malloc(sizeof(int) * count);
    for( int i = 0; i< count; i++){
        fval[i] = val[i];
        frow[i] = row[i];
        fcol[i] = col[i];
    }

    struct int_matrix mtx = {x,y,count,frow,fcol,fval};
    return mtx;
}