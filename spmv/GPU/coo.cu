// COO for running imported matrices

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct matrix{
    int x;
    int y;
    int n;
    int * row;
    int * col;
};

struct int_matrix {
    int x;
    int y;
    int n;
    int * row;
    int * col;
    int * val;
};

float avg (float * arr, int nelem){
    float average = 0;
    // printf("nelem: %d\n", nelem);
    for(int i = 0; i< nelem; i++){
        average = average + arr[i] / nelem;
    }
    return average;
}

float std_dev(const float *data, float avg,int n) {
    float sum_sq = 0.0;
    for (int i = 0; i < n; i++) {
        float d = data[i] - avg;
        sum_sq += d * d;
    }
    
    return sqrt(
        sum_sq / n
    );
}

void convert_to_microseconds(float * measures, int dim){
    for(int i = 0; i < dim; i++){
        measures[i] *= 1000.0f;
    }
}

void JSON_FORMAT_ITER(int warm, int iter, float avg, float std){
    printf("{\"warmup\":%d,\"niter\":%d,\"avg\": %f,\"std\": %f},\n",warm,iter,avg,std);
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

struct int_matrix import_int_matrix(char *file_path) {
    FILE *file = fopen(file_path, "r");

    if (file == NULL) {
        perror("Error opening file");
        struct int_matrix err = {0, 0, 0, NULL, NULL, NULL};
        return err;
    }

    char line[128];
    int x = 0, y = 0, n = 0;
    int *row = NULL, *col = NULL, *val = NULL;

    // Read until you get dimensions
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '%') continue; // comment line
        if (sscanf(line, "%d %d %d", &x, &y, &n) == 3) {
            // allocate memory now
            row = (int*)malloc(n * sizeof(int));
            col = (int*)malloc(n * sizeof(int));
            val = (int*)malloc(n * sizeof(int));
            if (!row || !col || !val) {
                perror("Memory allocation failed");
                fclose(file);
                struct int_matrix err = {0, 0, 0, NULL, NULL, NULL};
                return err;
            }
            break;
        } else {
            fprintf(stderr, "Invalid matrix dimension line format\n");
            fclose(file);
            struct int_matrix err = {0, 0, 0, NULL, NULL, NULL};
            return err;
        }
    }

    int index = 0;
    while (index < n && fgets(line, sizeof(line), file)) {
        if (line[0] == '%') continue; // skip comments

        int r, c, v;
        if (sscanf(line, "%d %d %d", &r, &c, &v) == 3) {
            row[index] = r;
            col[index] = c;
            val[index] = v;
            index++;
        } else {
            fprintf(stderr, "Invalid matrix element line format at index %d\n", index);
            // Handle error or skip line, here we abort:
            free(row);
            free(col);
            free(val);
            fclose(file);
            struct int_matrix err = {0, 0, 0, NULL, NULL, NULL};
            return err;
        }
    }

    fclose(file);

    struct int_matrix sm = {x, y, n, row, col,val}; // note: original swaps col and row here, preserve that if needed
    return sm;
}

struct int_matrix convert_to_int_mtx(struct matrix tmp){
    struct int_matrix mtx = {tmp.x,tmp.y,tmp.n,tmp.row,tmp.col,NULL};
    int * val = (int*)malloc(tmp.n * sizeof(int));
    for(int i = 0; i < tmp.n; i++){
        val[i] = 1;
    }
    mtx.val = val;
    return mtx;
}

// Std. implementation -> atomic add
__global__ void spmv_coo(int *val, int *row, int *col, int *arr, int *res, int n) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;  // Thread index
    if (tid < n) { 
        int row_idx = row[tid];  // Row index of the current non-zero element
        int vector_v = arr[col[tid]];  // Column index of the current non-zero element
        int product = val[tid] * vector_v;

        // Perform SpMV operation for this element
        atomicAdd(&res[row_idx], product);  
    }
}

// Std. implementation -> coalesced access and atomic add
__global__ void spmv_coo_coalesced(int *val, int *row, int * full_arr, int *res, int n) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;  // Thread index
    if (tid < n) { 
        int row_idx = row[tid];  
        int product = val[tid] * full_arr[tid];   

        // Perform SpMV operation for this element
        atomicAdd(&res[row_idx], product); 
    }
}



int main(int argc, char *args[]){
    if (argc < 2)
    {
        printf("require filepath!");
        return 0;
    }
    if (argc < 3)
    {
        printf("insert 0 binary or 1 integer mtx\n");
        return 0;
    }
    if (argc < 4)
    {
        printf("insert 1 if you want all 1 vector, or the 1/p probabilty to generate a value\n");
        return 0;
    }
    if (argc < 5)
    {
        printf("tell the number of WARM-UP rounds");
        return 0;
    }
    if (argc < 6)
    {
        printf("tell the number of ITERATION rounds");
        return 0;
    }
    if (argc < 7)
    {
        printf("tell the number of threads per block");
        return 0;
    }
    //random initializer
    srand(time(NULL));


    char *file_path = args[1];
    int type = atoi(args[2]);
    int p = atoi(args[3]);
    int warm_up = atoi(args[4]);
    int iterations = atoi(args[5]);
    int thread_n = atoi(args[6]);

    struct int_matrix mtx;
    if (type == 0){
        struct matrix tmp = import_matrix(file_path);
        mtx = convert_to_int_mtx(tmp); 
    }
    else if (type == 1)
        mtx = import_int_matrix(file_path); 
    else{
        printf("wrong import format!\n");
        return 0;
    }

    int n = mtx.n;
    int *row = mtx.row;
    int *col = mtx.col;
    int *value = mtx.val;
    int *res = (int*)calloc(mtx.x, sizeof(int));
    int * arr = (int*)malloc(sizeof(int) * mtx.y);
    float * measures = (float*)malloc(sizeof(float) * iterations);
    float average = 0;

    for(int i = 0; i<mtx.y; i++){
        // arr[i] = 1;
        arr[i] = rand() % 1000000;//for not have to handle out of memory cases
    }

    
    int * full_arr = (int*)malloc(sizeof(int) * mtx.n);
    for(int elem = 0; elem< mtx.n; elem++)
        full_arr[elem] = arr[mtx.col[elem]];       
        
    float milliseconds;
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    int *d_val, * d_row,*d_col,*d_short_arr,*d_arr, *d_res;
    cudaMalloc(&d_val, n * sizeof(int));
    cudaMalloc(&d_arr, n * sizeof(int));
    cudaMalloc(&d_short_arr, mtx.y * sizeof(int));
    cudaMalloc(&d_col, n * sizeof(int));
    cudaMalloc(&d_row, n * sizeof(int));
    cudaMalloc(&d_res, mtx.x * sizeof(int));

    // Copy data to device
    cudaMemcpy(d_val, value, n * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_short_arr, arr, mtx.y * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_arr, full_arr, n * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_res, res, mtx.x * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_row, row, n * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_col, col, n * sizeof(int), cudaMemcpyHostToDevice);
    
    int block_n = (n / thread_n) + 1;

    printf("non 0 elem: %d\n", mtx.n);
    //initialize json
    printf("{\"x\":%d,\n\"y\":%d,\"n\":%d,\"runs\":{",mtx.x,mtx.y,mtx.n);

    for(int i = -warm_up; i< iterations; i++){
        if(i < 0 ){
            spmv_coo<<<block_n,thread_n>>>(d_val, d_row, d_col,d_short_arr, d_res,n);
            cudaMemcpy(d_res, res, mtx.x * sizeof(int), cudaMemcpyHostToDevice);//zeroing the memory      
        }
        else{
            cudaEventRecord(start);
            spmv_coo<<<block_n,thread_n>>>(d_val, d_row, d_col,d_short_arr, d_res,n);
            cudaEventRecord(stop);
            cudaEventSynchronize(stop);
            cudaEventElapsedTime(&measures[i], start, stop);
            cudaMemcpy(d_res, res, mtx.x * sizeof(int), cudaMemcpyHostToDevice);
        }
    }
    convert_to_microseconds(measures, iterations);
    average = avg(measures, iterations);
    printf("\"std.\":");
    JSON_FORMAT_ITER(warm_up,iterations,average,std_dev(measures,average,iterations));
    
    // printf("Result arr: ");
    // for (int i = 0; i < mtx.x; i++) {
    //     printf("%d ", res[i]);
    // }
    // printf("\n");

    for(int i = -warm_up; i< iterations; i++){
        if(i < 0 ){
            spmv_coo_coalesced<<<block_n,thread_n>>>(d_val, d_row,d_arr, d_res,n);
            cudaMemcpy(d_res, res, mtx.x * sizeof(int), cudaMemcpyHostToDevice);//zeroing the memory      
        }
        else{
            cudaEventRecord(start);
            spmv_coo_coalesced<<<block_n,thread_n>>>(d_val, d_row,d_arr, d_res,n);
            cudaEventRecord(stop);
            cudaEventSynchronize(stop);
            cudaEventElapsedTime(&measures[i], start, stop);
            cudaMemcpy(d_res, res, mtx.x * sizeof(int), cudaMemcpyHostToDevice);
        }
    }
    convert_to_microseconds(measures, iterations);
    average = avg(measures, iterations);
    printf("\"std. coalesced\":");
    printf("{\"warmup\":%d,\"niter\":%d,\"avg\": %f,\"std\": %f}\n",warm_up,iterations,average,std_dev(measures,average,iterations));
    
    printf("}}\n");
    // Free device memory
    cudaFree(d_val);
    cudaFree(d_short_arr);
    cudaFree(d_arr);
    cudaFree(d_res);
    cudaFree(d_row);
    cudaFree(d_col);
    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    return 0;
}