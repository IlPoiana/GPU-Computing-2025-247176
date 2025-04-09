#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct matrix{
    int x;
    int y;
    int n;
    int * row;
    int * col;
};

/**
 * @brief Supposing it's a sqare matrix
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