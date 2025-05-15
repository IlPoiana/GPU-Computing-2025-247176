#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
 * @brief DEPRECATED LIB
 * 
 */


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
        int row_ptr = 1;
        for(int i = row_ptr; mtx.row[i] == 0; i++){
            ++row_ptr;
        }

        //retrieve the data, n values and columns, r rows

        int j = 0;
        for(row_ptr; row_ptr <= mtx.x; row_ptr++){
            for(j; j < mtx.row[row_ptr];j++){
                printf("[%d,%d] = %d\n", row_ptr - 1, mtx.col[j], mtx.val[j]);
            }
            printf("-----\n");
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

double avg (double * arr, int nelem){
    double average = 0;
    printf("nelem: %d\n", nelem);
    for(int i = 0; i< nelem; i++){
        average = average + arr[i] / nelem;
    }
    return average;
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

struct int_matrix convert_COO_CSR(struct int_matrix mtx){
    int * row = (int*)calloc(mtx.x + 1, sizeof(int));
    int * col = (int*)malloc(sizeof(int) * mtx.n);
    int * val = (int*)malloc(sizeof(int) * mtx.n);
    struct int_matrix csr = {mtx.x,mtx.y,mtx.n,row,col,val};
    for(int j = 0; j< mtx.n; j++){
        col[j] = mtx.col[j];
        val[j] = mtx.val[j];
    }

    int j = 0;
    for(int i = 1; i<= mtx.x; i++){
        row[i] = row[i - 1];
        for(j; i - 1 == mtx.row[j] ;j++)
            if(mtx.val[j] != 0)
                ++row[i];
    }
    // PRINT_RESULT_ARRAY(row,"conversion row",mtx.x +1);
    return csr;
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
            // printf("change row, row count: %d - count: %d - i: %d\n", row_count, count, i);
            row[row_count] = count;
            // printf("row[%d] = %d\n --- \n", row_count, count);
            ++row_count;
        }
        
        v_buff = rand()%p;
        if(v_buff == 0){
            if(binary == 1){
                val[count] = 1;
            }
            else{
                val[count] = (rand() % binary) + 1; 
            }

            if(i >= y)
                col[count] = abs((y - i) % y);
            else
                col[count] = i;

            ++count;
            row[row_count] = count;
            // printf("gen value: i: %d - row[%d] = %d - col[%d] = %d\n", i,row_count, count,count - 1,col[count - 1]);
        }
        
        if(row[row_count] < row[row_count - 1]){
            row[row_count] = row[row_count - 1];
        }

    }
    int * fval = (int*)malloc(sizeof(int) * count);
    int * frow = (int*)malloc(sizeof(int) * (row_count + 1));
    int * fcol = (int*)malloc(sizeof(int) * count);
    
    for(int i = 0; i< count; i++){
        fval[i] = val[i];
        fcol[i] = col[i];
    }

    for(int i = 0; i<= row_count; i++){
        frow[i] = row[i];
    }
 

    struct int_matrix mtx = {x,y,count,frow,fcol,fval};

    return mtx;
}


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

/**
 * arr needs to be same size of mtx.y
 */
int * csr_multiplication(struct int_matrix mtx, int * arr){
    int * res = (int*)calloc(mtx.n, sizeof(int));
    int * row = mtx.row;
    int * col = mtx.col;
    int * value = mtx.val;
    int val_idx = 0;
    for(int row_idx = 1; row_idx <= mtx.x; row_idx++){
        if(row[row_idx] == row[row_idx - 1]){
            //skip
        }
        else{
            for(val_idx; val_idx < row[row_idx]; val_idx++){
                res[row_idx - 1] += value[val_idx] * arr[col[val_idx]];
            }
        }
    }
    return res;
}