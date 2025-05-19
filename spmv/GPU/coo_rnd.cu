//COO for computing on random matrices

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct int_matrix {
    int x;
    int y;
    int n;
    int * row;
    int * col;
    int * val;
};

void reset_array(int * arr, int dim){
    for(int i=0; i<dim;i++){
        arr[i] = 0;
    }
}

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

// Row. implementation -> one kernel with one block for each row: < thread num. case //TO DO
// __global__ void spmv_coo_block_reduction(int *val, int row_idx, int * full_arr, int *res, int start) {
//     int tid = threadIdx.x + start;  // Thread index 0..thread_n  
//     full_arr[tid] += val[tid] * full_arr[tid];  
//     __syncthreads(); 
//     parallel_reduction()
//     res[row_idx] = full_arr //store to the result, only thread of block 0 
    
// }

// Row. implementation -> one kernel with one block for each row: < thread num. case
// __global__ void spmv_coo_big_block_reduction(int *val, int row_idx, int * full_arr, int *res, int start, int row_length) {
//     int computation_n;
//     if(row_length % blockDim.x == 0)
//         computation_n = row_length / blockDim.x;
//     else
//         computation_n = row_length / blockDim.x + 1; // 11/10 = 2, 19/10 = 2, 20/10 = 2, 23/10 = 3;
//     int active_threads_n = row_length / computation_n;
//     int remaining_computation = row_length % (active_threads_n * computation_n); 
    
//     //11 10-> computation_n = 2 act = 5 rem = 11 % 10 = 1
//     // 19 10 -> computation_n = 2 act = 9 rem = 19 % 18 = 1
//     // 20 10 -> computation_n = 2 act = 10 rem 20%20 = 0
//     //134 -> comp_n = 14 act = 9 rem = 134 % 126 = 8

//     int local_idx = threadIdx.x * computation_n;
//     int tid = local_idx + start;

//     if(threadIdx.x > active_threads_n){
//         return; //don't compute 
//     }
    
//     int f_value = val[tid] * full_arr[tid]; //0 -> 0; 1 -> 2; 2 -> 4
    
//     if(threadIdx.x < active_threads_n)
//         for(int s = 1; s < computation_n; s++)
//                 f_value += val[tid + s] * full_arr[tid + s];
//     else
//         for(int s = 1; s < remaining_computation; s++)
//             f_value += val[tid + s] * full_arr[tid + s];
//     full_arr[tid] = f_value;
        
//     __syncthreads()
//     //now i have less than num threads reduction to do
//     //i have to move by computation_n
//     // for (int stride = (computation_n* active_threads_n / 2); stride > 0; stride >>= 1) {
//     //     __syncthreads();

//     //     if (local_idx < stride && (local_idx + stride + computation_n) < row_length) {
//     //         data[tid] += data[tid + stride + computation_n];
//     //     }
//     // }
    
//     if(threadIdx.x == 0){
//         for(int offset = computation_n; offset< row_length; offset += offset)//iterate over all the others values
//             f_value += full_arr[tid + offset]; 
//         res[tid] = f_value;//update res
//     }
        
// }

// Good idea but to develop further, further problems comes with the blocks that have to synchronize 
// void host_row_spmv(int * d_val, int * d_arr, int * d_res,int * row, int n){
//     int thread_n = 1; //number of threads to assign to each kernel
//     int block_n = 1;
//     for(int i = 1; i < n; i++){
//         if(row[i] != row[i - 1]){
//             printf("i: %d - row[i]: %d - thread_n: %d\n",i,row[i], thread_n);
//             block_n = (thread_n / 256);
//             if( block_n > 0){
//                 row_spmv<<<block_n,256>>>(d_val,d_arr,d_res,i - thread_n,row[i - 1]);
//                 thread_n -= block_n * 256;
//             }
//             if(thread_n > 0)
//                 row_spmv<<<1,thread_n>>>(d_val,d_arr,d_res,i - thread_n,row[i - 1]);
//             thread_n = 1;//reset thread number
//         }
//         else{
//             ++thread_n;
//         }
//     }
//     //launch the last kernel
//     printf("n: %d - row[n-1]: %d - thread_n: %d\n",n,row[n-1], thread_n);
//     block_n += (thread_n / 256);
//     if( block_n > 0){
//         row_spmv<<<block_n,256>>>(d_val,d_arr,d_res,i - thread_n,row[i - 1]);
//         thread_n -= block_n * 256;
//     }
//     if(thread_n > 0)
//         row_spmv<<<1,thread_n>>>(d_val,d_arr,d_res,i - thread_n,row[i - 1]);
// }

struct int_matrix gen_rnd_COO(int x, int y, int p, int binary){
    if(binary<1){
        printf("passed an invalid binary argument\n");
        struct int_matrix err = {0,0,0,0,0,0};
        return err;
    }

    long max_v = x * y;
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
    if (argc < 8){
        printf("tell the number of threads");
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
    int iterations = atoi(args[6]);
    int thread_n = atoi(args[7]);
    // printf("Passed arguments\nx: %d\ny: %d\np: %d\nbinary: %d\n\n",row_n,col_n,p,binary);
   
    
    struct int_matrix mtx = gen_rnd_COO(row_n, col_n,p,binary);
    // PRINT_INT_MTX(mtx, COO);
    // printf("Running sparse matrix multiplication between a 1 vector and a integer value matrix\n");
    if (mtx.x == 0 && mtx.y == 0){
        printf("matrix not loaded correctly\n");
        return 0;
    }
    int n = mtx.n;
    int *row = mtx.row;
    int *col = mtx.col;
    int *value = mtx.val;
    int *res = (int*)calloc(row_n, sizeof(int));
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

    //initialize json
    printf("{\"x\":%d,\n\"y\":%d,\"n\":%d,\"threads_n\":%d,\"runs\":{",mtx.x,mtx.y,mtx.n,thread_n);

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