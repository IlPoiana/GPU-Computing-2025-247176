#include <stdio.h>
#include <stdlib.h>
// Deprecated ----
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

// ----------