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

struct int_extended_mtx{
        struct int_matrix mtx;
        int * arr;
};

// Std. implementation -> coalesced access and atomic add

// Row. implementation


// Reduction implementation
__global__ void row_spmv(int * val, int * arr, int * res,int start , int res_idx){
    int threads_num = gridDim.x * blockDim.x;
    int local_tid = blockIdx.x * blockDim.x + threadIdx.x; 
    int tid = local_tid + start;
    arr[tid] *= val[tid];
    //here start reduction
    if(threads_num == 1){
        res[res_idx] = arr[tid];
        return;
    }
    __syncthreads();
    //check if it's uneven
    if((threads_num & 1) == 1)
        if(tid == start)
            arr[tid] += arr[tid + threads_num - 1];

    for(int s = (threads_num/2); s > 0; s >>= 1 ){
        __syncthreads();
        if(s == 1 && local_tid == 0)
            res[res_idx] = arr[tid] + arr[tid + s];//saving one access to memory
        else if(local_tid < s)
            arr[tid] += arr[tid + s];
        
    }
    
    // res[res_idx] = arr[tid]; with shared is better this
}

// Std implementation + vector data structure + reduction

__global__ void COO_Unrolled(float* value, float* row, float* col, int res)
{
    
}

__global__ void COO_1(float* value, float* row, float* col, int res)
{
    
    
}
// Good idea but to develop further, further problems comes with the blocks that have to synchronize 
void host_row_spmv(int * d_val, int * d_arr, int * d_res,int * row, int n){
    int thread_n = 1; //number of threads to assign to each kernel
    int block_n = 1;
    for(int i = 1; i < n; i++){
        if(row[i] != row[i - 1]){
            printf("i: %d - row[i]: %d - thread_n: %d\n",i,row[i], thread_n);
            block_n = (thread_n / 256);
            if( block_n > 0){
                row_spmv<<<block_n,256>>>(d_val,d_arr,d_res,i - thread_n,row[i - 1]);
                thread_n -= block_n * 256;
            }
            if(thread_n > 0)
                row_spmv<<<1,thread_n>>>(d_val,d_arr,d_res,i - thread_n,row[i - 1]);
            thread_n = 1;//reset thread number
        }
        else{
            ++thread_n;
        }
    }
    //launch the last kernel
    printf("n: %d - row[n-1]: %d - thread_n: %d\n",n,row[n-1], thread_n);
    block_n += (thread_n / 256);
    if( block_n > 0){
        row_spmv<<<block_n,256>>>(d_val,d_arr,d_res,i - thread_n,row[i - 1]);
        thread_n -= block_n * 256;
    }
    if(thread_n > 0)
        row_spmv<<<1,thread_n>>>(d_val,d_arr,d_res,i - thread_n,row[i - 1]);
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
    //random initializer
    srand(time(NULL));


    int row_n = atoi(args[1]);
    int col_n = atoi(args[2]); 
    int max_v = row_n * col_n;
    int p = atoi(args[3]);
    int binary = atoi(args[4]);
    int warm_up = atoi(args[5]);
    int iterations = atoi(args[6]);
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
    double * measures = (double*)malloc(sizeof(double) * iterations);

    for(int i = 0; i<mtx.y; i++){
        arr[i] = 1;
        // arr[i] = rand() % 1000000;//for not have to handle out of memory cases
    }

    
    int * full_arr = (int*)malloc(sizeof(int) * mtx.n);
    for(int elem = 0; elem< mtx.n; elem++)
        full_arr[elem] = arr[mtx.col[elem]];       
        
    
    int *d_val, *d_arr, *d_res;
    cudaMalloc(&d_val, n * sizeof(int));
    cudaMalloc(&d_arr, n * sizeof(int));
    cudaMalloc(&d_res, mtx.y * sizeof(int));

    // Copy data to device
    cudaMemcpy(d_val, value, n * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_arr, full_arr, n * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_res, res, mtx.y * sizeof(int), cudaMemcpyHostToDevice);
    
    host_row_spmv(d_val,d_arr,d_res,row,n);

    // Copy results back to host
    cudaMemcpy(res, d_res, mtx.y * sizeof(int), cudaMemcpyDeviceToHost);

    // Print result
    printf("Result arr: ");
    for (int i = 0; i < mtx.y; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");

    // Free device memory
    cudaFree(d_val);
    cudaFree(d_arr);
    cudaFree(d_res);
    return 0;
}