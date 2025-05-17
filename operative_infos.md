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

## 1 - CPU part
1. **Dense SpMV implementation** (both binary and real) (done)
2. **COO implementation sorted by row** and not by columns Naive Product (done)
3. More Optimized implementation(0 skip, sequential access and loop unrolling)
   1. 0 Skip
   2. Sequential Access Analysis
   3. Loop Unrolling
   4. OpenMP One Thread for multiple rows, load balanced
   5. Valgrind on the unrolled and the std one to see the branching factor and the cache behavior. **Cache** doesn't change it's behavior but it requires less instruction (probably the jumps in the loops). The unrolled is better by a slightly amount but subject to more branching due to the more checks, so it suffer more from context switching of the CPU routine

4. Comparison between real and binary/integer numbers in performance(read things)  
5. comparison with optimization flags

- Debate why COO and why CSR

- Evaluate stack vs heap:
- optimization flags of compiler -> see iterations.json
- cache usage vs no cache usage
    - and what factors influences cache hit and misses
- (plus) Use non std. implementations: *"(ILP, OpenMP is a plus)"*

0. Parameters fine tuning:
    1. CPU comparison: how many warm up rounds and how many iterations? Binary vs not binary
1. how does it scale? **TIME**,**FLOPs** and **BANDWIDTH**

## 2 - GPU part
"Side note, nel caso di GPU invece consideri solo le read e write da e per global memory, r/w su registri può ignorarle in quanto ordini di grandezza più veloci di quelle in global."

1. One Thread for each row (not coalesced access but no race conditions)
2. 

## Test implementations:
Matrix
-Dense 100%
-Sparse 50% - 10% - 1% - 0.1%
-Extremely sparse <1% (0.1-0.01-0.001%) 

Array:
-Dense 100%
-Half 50%
-Sparse 10% 1% or less

### Dense test
256 - 512 - 1024 - 2048 - 5096 x and y 
### COO - Std. vs 0 vs loop-un
256 - 512 - 1024 - 2048 - 5096
### Std vs Multithread
256 - 512 - 1024 - 2048 - 5096
### Bandwidth considerations:
"in generale conti sempre gli accessi indotti dal codice, ignorando le ottimizzazioni black-box fatte dal compilatore."
"Se la performance dipende dall'input, si considera il worst case

## PLOTTING
1. 3 plots for each implementations: **TIME**,**FLOPs** and **BANDWIDTH** -> 6 plots
2. Matrix for the iterations and plots
3. Histograms for comparing different implementations
