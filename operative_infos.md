## Cuda kernel usage

*citing the textbook: Programming Massively Parallel Processors*

*The readers should ask where the other two levels of outer loops go. The answer is that the outer two loop levels are now replaced with the grid of threads. The entire grid forms the equivalent of the two-level loop. **Each thread in the grid corresponds to one of the iterations of the original two-level loop**. The original loop variables i and j are now replaced with threadIdx.x and threadIdx.y. Instead of having the loop increment the values of i and j for use in each loop iteration, the CUDA threading hardware generates all of the threadIdx.x and threadIdx.y values for each thread.*

```
__global__ void MatMul(...){
    int tx = threadIdx.x;
    int ty = threadIdx.y;
    ...
    for(k=0;k< Width; ++k){

    }
}

// this is equivalent to 
for(i){
    for(j){
        for(k=0;k< Width; ++k){

        }
    }
}
```

## Valgrind usage
Tipical workflow:
1. Compile using `-g` flag option
2. Execute `valgrind --tool=cachegrind <program>` for getting the cache analysis
3. run `cg_annotate --auto=yes <cachegrind.out>` to get a detailed row by row execution analysis of the program


*citing from the official website*

- I cache reads (`Ir`, which equals the number of instructions executed), I1 cache read misses (`I1mr`) and LL cache instruction read misses (`ILmr`).

- D cache reads (`Dr`, which equals the number of memory reads), D1 cache read misses (`D1mr`), and LL cache data read misses (`DLmr`).

- D cache writes (`Dw`, which equals the number of memory writes), D1 cache write misses (`D1mw`), and LL cache data write misses (`DLmw`).

**Note that D1 total accesses is given by D1mr + D1mw, and that LL total accesses is given by ILmr + DLmr + DLmw.**

When simulating the branch predictor, with --branch-sim=yes, Cachegrind gathers the following statistics:

-   Conditional branches executed (`Bc`) and conditional branches mispredicted (`Bcm`).

-   Indirect branches executed (`Bi`) and indirect branches mispredicted (`Bim`).

## CPU part
- Debate why COO and why CSR

- Evaluate stack vs heap:
- optimization flags of compiler
- cache usage vs no cache usage
    - and what factors influences cache hit and misses


0. Parameters fine tuning:
    1. CPU comparison: how many warm up rounds and how many iterations? Binary vs not binary
1. how does it scale? **FLOPs** and **BANDWIDTH**

Test implementations:
-Dense 100% - 90% - 80%
-Sparse 50% - 25% - 10% - 1%
-Extremely sparse <1% (0.1-0.01-0.001%) 
